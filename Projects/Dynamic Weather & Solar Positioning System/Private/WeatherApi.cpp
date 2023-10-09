//Name: Christopher Forte
//Date: 21/08/2023
//Email: cnf2500@gmail.com

#include "WeatherApi.h"
#include "Json.h"
#include "JsonUtilities.h"
#include <curl/curl.h>
#include <sstream>

WeatherApi::WeatherApi(const std::string& apiKey) : apiKey(apiKey), mode("json"), units("standard") {}

size_t WeatherApi::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string WeatherApi::makeRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return readBuffer;
}

std::string WeatherApi::getByGeoLocation(double latitude, double longitude) {
    std::stringstream url;
    url << "https://api.openweathermap.org/data/2.5/weather?lat=" << latitude << "&lon=" << longitude << "&appid=" << apiKey;
    return makeRequest(url.str());
}

void WeatherApi::setOutputMode(const std::string& newMode) {
    this->mode = newMode;
}

void WeatherApi::setUnits(const std::string& newUnits) {
    this->units = newUnits;
}

int32 WeatherApi::GetTimeZoneOffset(const std::string& jsonResponse) {
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(jsonResponse.c_str());

    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid()) {
        if(JsonObject->HasField("timezone")) {
            return JsonObject->GetNumberField("timezone");
        }
    }
    return 0; // Default to 0 if parsing fails
}
