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
    void UpdateLocation(float Latitude, float Longitude); // Made public for flexibility, but use with caution.

private:
    FMacLocationManager* NativeLocationManager;
    FVector2D LatestLocation;
};
