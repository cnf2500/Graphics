//Name: Christopher Forte
//Date: 21/08/2023
//Email: cnf2500@gmail.com

#include "WeatherManager.h"
#include "EngineUtils.h"
#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"
#include "LocationHandler.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include <cmath>

AWeatherManager::AWeatherManager()
{
    PrimaryActorTick.bCanEverTick = true;
    LocationHandler = CreateDefaultSubobject<ULocationHandler>(TEXT("LocationHandlerInstance"));

    FString apiKey;
    if (GConfig->GetString(TEXT("WeatherAPI"), TEXT("APIKey"), apiKey, GEngineIni))
    {
        WeatherAPIInstance = new WeatherApi(TCHAR_TO_UTF8(*apiKey));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to Fetch API Key From ini File!"));
    }
    
    bHasTimeZoneOffset = false;
}

AWeatherManager::~AWeatherManager()
{
    if (WeatherAPIInstance)
    {
        delete WeatherAPIInstance;
        WeatherAPIInstance = nullptr;
    }
}

void AWeatherManager::FetchWeatherData(double latitude, double longitude)
{
    try
    {
        FString weatherData = WeatherAPIInstance->getByGeoLocation(latitude, longitude).c_str();
        TimeZoneOffset = WeatherAPIInstance->GetTimeZoneOffset(TCHAR_TO_UTF8(*weatherData));
        bHasTimeZoneOffset = true;
        
        // Logging the extracted timezone offset
        //UE_LOG(LogTemp, Warning, TEXT("Extracted Timezone Offset: %d"), TimeZoneOffset);
        UE_LOG(LogTemp, Warning, TEXT("Weather Data: %s"), *weatherData);
    }
    catch (const std::exception& e)
    {
        UE_LOG(LogTemp, Error, TEXT("Error Fetching Weather Data: %s"), *FString(e.what()));
    }
}

void AWeatherManager::BeginPlay()
{
    Super::BeginPlay();
    
    for (TActorIterator<ADirectionalLight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        DirectionalLightReference = *ActorItr;
    }

    if(LocationHandler)
    {
        LocationHandler->StartLocationUpdates();

        // Delay weather data fetching to give LocationHandler time to get accurate location.
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AWeatherManager::FetchUserLocationAndWeather, 5.0f, false);
    }
    else
    {
        FetchDefaultLocationWeather();
    }
}

void AWeatherManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!LocationHandler || LocationHandler->GetLatestLocation().IsZero())
    {
        //UE_LOG(LogTemp, Warning, TEXT("Invalid location received."));
        return;
    }

    if (bHasTimeZoneOffset)
    {
        // Extract and adjust for local time
        FDateTime UtcTime = FDateTime::UtcNow();
        FDateTime CurrentLocalTime = UtcTime + FTimespan::FromSeconds(TimeZoneOffset);
               
        // Logging the times for verification
        //UE_LOG(LogTemp, Warning, TEXT("UTC Time: %s"), *UtcTime.ToString());
        UE_LOG(LogTemp, Warning, TEXT("Adjusted Local Time: %s"), *CurrentLocalTime.ToString());
            
        double latitude = LocationHandler->GetLatestLocation().X;
        double longitude = LocationHandler->GetLatestLocation().Y;

        UE_LOG(LogTemp, Warning, TEXT("Latitude: %f"), latitude);
        UE_LOG(LogTemp, Warning, TEXT("Longitude: %f"), longitude);
        
        double dayOfYear = CalculateDayOfYear(CurrentLocalTime);
        UE_LOG(LogTemp, Warning, TEXT("Day of Year: %f"), dayOfYear);
            
        double declination = CalculateDeclination(dayOfYear);
        UE_LOG(LogTemp, Warning, TEXT("Declination: %f"), declination);
            
        double timeCorrection = CalculateTimeCorrectionFactor(dayOfYear);
        UE_LOG(LogTemp, Warning, TEXT("Time Correction Factor: %f"), timeCorrection);
            
        double solarNoon = CalculateSolarNoon(longitude, timeCorrection);
        UE_LOG(LogTemp, Warning, TEXT("Solar Noon: %f"), solarNoon);
            
        double time = CalculateTimeInHours(CurrentLocalTime);
        UE_LOG(LogTemp, Warning, TEXT("Time in Hours: %f"), time);
            
        double hourAngle = CalculateSolarHourAngle(time, solarNoon);
        UE_LOG(LogTemp, Warning, TEXT("Solar Hour Angle: %f"), hourAngle);
            
        double currentAzimuth, currentZenith;
        CalculateSunPosition(latitude, declination, hourAngle, currentAzimuth, currentZenith);
        UE_LOG(LogTemp, Warning, TEXT("Solar Azimuth: %f, Solar Zenith: %f"), currentAzimuth, currentZenith);

        SolarPitch = FMath::Lerp(-185.0f, 4.0f, currentZenith / 90.0f);
        //SolarPitch = FMath::Lerp(90.0f, -90.0f, currentZenith / 90.0f);
        SolarYaw = currentAzimuth;

        if (DirectionalLightReference)
        {
            DirectionalLightReference->SetActorRotation(FRotator(SolarPitch, SolarYaw, 0));
        }
    }
}

void AWeatherManager::ApplyWeatherEffects()
{
    // Implementation of weather effects based on API data will go here
}

void AWeatherManager::FetchUserLocationAndWeather()
{
    FVector2D UserLocation = LocationHandler->GetLatestLocation();
    FetchWeatherData(UserLocation.X, UserLocation.Y);
}

void AWeatherManager::FetchDefaultLocationWeather()
{
    UE_LOG(LogTemp, Warning, TEXT("LocationHandler Not Set. Using Default Location."));
    double testLatitude = 40.730610;
    double testLongitude = -73.935242;
    FetchWeatherData(testLatitude, testLongitude);
}

double AWeatherManager::CalculateTimeInHours(FDateTime time)
{
    return time.GetHour() + time.GetMinute() / 60.0 + time.GetSecond() / 3600.0;
}

double AWeatherManager::CalculateDayOfYear(FDateTime date)
{
    return date.GetDayOfYear();
}

double AWeatherManager::CalculateDeclination(int dayOfYear)
{
    return 23.45 * sin(360.0 / 365.0 * (dayOfYear - 81) * (UE_PI / 180));
}

double AWeatherManager::CalculateTimeCorrectionFactor(int dayOfYear)
{
    return 229.18 * (0.000075 + 0.001868 * cos(360.0 / 365.0 * dayOfYear * (UE_PI / 180)) - 0.032077 * sin(360.0 / 365.0 * dayOfYear * (UE_PI / 180)) - 0.014615 * cos(2 * 360.0 / 365.0 * dayOfYear * (UE_PI / 180)) - 0.040849 * sin(2 * 360.0 / 365.0 * dayOfYear * (UE_PI / 180)));
}

double AWeatherManager::CalculateSolarNoon(double longitude, double timeCorrection)
{
    // Determine standard meridian for the given longitude
    double standardMeridian = FMath::RoundToFloat(longitude / 15.0) * 15;
    return 12.0 - ((standardMeridian - longitude) * 4 + timeCorrection) / 60.0;
}

double AWeatherManager::CalculateSolarHourAngle(double time, double solarNoon)
{
    double hourAngle = 15.0 * (time - solarNoon);
    
    // Adjust to make sure it's between -180 and 180
    if (hourAngle > 180.0)
        hourAngle -= 360.0;
    else if (hourAngle < -180.0)
        hourAngle += 360.0;

    return hourAngle;
}

void AWeatherManager::CalculateSunPosition(double latitude, double declination, double hourAngle, double& outAzimuth, double& outZenith)
{
    // Convert degrees to radians
    double latitudeRad = latitude * (UE_PI / 180);
    double declinationRad = declination * (UE_PI / 180);
    double hourAngleRad = hourAngle * (UE_PI / 180);

    // Solar Zenith Calculation
    double cosZenith = sin(latitudeRad) * sin(declinationRad) + cos(latitudeRad) * cos(declinationRad) * cos(hourAngleRad);
    
    double zenithRad = acos(cosZenith);
    double zenithDeg = zenithRad * (180.0 / UE_PI);

    // Solar Azimuth Calculation (as before)
    double numerator = sin(hourAngleRad);
    double denominator = (cos(hourAngleRad) * sin(latitudeRad)) - (tan(declinationRad) * cos(latitudeRad));
    double azimuthRad = atan2(numerator, denominator);
    double azimuthDeg = azimuthRad * (180.0 / UE_PI);
    if (azimuthDeg < 0.0)
    {
        azimuthDeg += 360.0;
    }

    // Assign to the out parameters
    outAzimuth = azimuthDeg;
    outZenith = zenithDeg;
}
