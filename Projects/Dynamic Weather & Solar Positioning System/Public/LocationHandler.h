//Name: Christopher Forte
//Date: 21/08/2023
//Email: cnf2500@gmail.com

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LocationHandler.generated.h"

class FMacLocationManager;

UCLASS()
class FIRSTLAUREL_API ULocationHandler : public UObject
{
    GENERATED_BODY()

public:
    ULocationHandler();
    virtual ~ULocationHandler();

    void StartLocationUpdates();
    FVector2D GetLatestLocation() const;
    void UpdateLocation(float Latitude, float Longitude);

private:
    FMacLocationManager* NativeLocationManager;
    FVector2D LatestLocation;
};
