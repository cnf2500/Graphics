#include "LocationHandler.h"
#import <CoreLocation/CoreLocation.h>

@interface FMacLocationManagerObjC : NSObject<CLLocationManagerDelegate>
{
    CLLocationManager *locationManager;
    void (^UpdateCallback)(float, float);
}
- (id)initWithUpdateCallback:(void(^)(float, float))callback;
- (void)stop;
@end

@implementation FMacLocationManagerObjC

- (id)initWithUpdateCallback:(void(^)(float, float))callback {
    self = [super init];
    if(self) {
        UpdateCallback = [callback copy];
        locationManager = [[CLLocationManager alloc] init];
        locationManager.delegate = self;
    }
    return self;
}

- (void)start {
    [locationManager startUpdatingLocation];
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    CLLocation *location = [locations lastObject];
    UpdateCallback(location.coordinate.latitude, location.coordinate.longitude);
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    NSLog(@"Location Manager Error: %@", [error localizedDescription]);
}

- (void)stop {
    [locationManager stopUpdatingLocation];
}

@end

class FMacLocationManager {
public:
    FMacLocationManagerObjC* ObjCInstance;

    FMacLocationManager(ULocationHandler* InHandler) {
        ObjCInstance = [[FMacLocationManagerObjC alloc] initWithUpdateCallback:^(float Latitude, float Longitude) {
            InHandler->UpdateLocation(Latitude, Longitude);
        }];
    }

    ~FMacLocationManager() {
        [ObjCInstance stop];
    }

    void Start() {
        [ObjCInstance start];
    }
};

ULocationHandler::ULocationHandler() {
    NativeLocationManager = new FMacLocationManager(this);
}

ULocationHandler::~ULocationHandler() {
    delete NativeLocationManager;
}

void ULocationHandler::StartLocationUpdates() {
    NativeLocationManager->Start();
}

FVector2D ULocationHandler::GetLatestLocation() const {
    return LatestLocation;
}

void ULocationHandler::UpdateLocation(float Latitude, float Longitude) {
    LatestLocation = FVector2D(Latitude, Longitude);
}
