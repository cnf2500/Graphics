#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherApi.h"
#include "LocationHandler.h"
#include "Engine/DirectionalLight.h"
#include "WeatherManager.generated.h"

class ULocationHandler;

UCLASS()
class FIRSTLAUREL_API AWeatherManager : public AActor
{
    GENERATED_BODY()

public:
    AWeatherManager();
    virtual ~AWeatherManager();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void FetchWeatherData(double latitude, double longitude);
    void ApplyWeatherEffects();
    void FetchUserLocationAndWeather();
    void FetchDefaultLocationWeather();
    
    double CalculateTimeInHours(FDateTime time);
    double CalculateDayOfYear(FDateTime date);
    double CalculateDeclination(int dayOfYear);
    double CalculateTimeCorrectionFactor(int dayOfYear);
    double CalculateSolarNoon(double longitude, double timeCorrection);
    double CalculateSolarHourAngle(double time, double solarNoon);
    void CalculateSunPosition(double latitude, double declination, double hourAngle, double& outAzimuth, double& outZenith);
    
    bool bHasTimeZoneOffset;
    
    WeatherApi* WeatherAPIInstance;
    int32 TimeZoneOffset;

    UPROPERTY(EditDefaultsOnly, Category = "Location")
    ULocationHandler* LocationHandler;
    
    UPROPERTY(BlueprintReadOnly, Category = "Solar")
    float SolarPitch;

    UPROPERTY(BlueprintReadOnly, Category = "Solar")
    float SolarYaw;
    
    UPROPERTY()
    ADirectionalLight* DirectionalLightReference;
};

