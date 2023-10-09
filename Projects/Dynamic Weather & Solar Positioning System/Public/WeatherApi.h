#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include "CoreMinimal.h"
#include <string>

class WeatherApi {
public:
    WeatherApi(const std::string& apiKey);
    std::string getByCityName(const std::string& city);
    std::string getByCityNameAndCountry(const std::string& city, const std::string& country);
    std::string getByCityNameStateAndCountry(const std::string& city, const std::string& state, const std::string& country);
    std::string getByCityID(const std::string& cityID);
    std::string getByZIPCode(const std::string& zip, const std::string& country = "us");
    std::string getByGeoLocation(double latitude, double longitude);
    int32 GetTimeZoneOffset(const std::string& jsonResponse);
    void setOutputMode(const std::string& newMode);
    void setUnits(const std::string& newUnits);

private:
    std::string apiKey;
    std::string mode;
    std::string units;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    std::string makeRequest(const std::string& url);
};

#endif
