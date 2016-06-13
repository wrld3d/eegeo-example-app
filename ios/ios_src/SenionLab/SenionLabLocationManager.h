// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "IndoorLocation.h"
#include "Interiors.h"

@interface SenionLabLocationManager : NSObject
-(instancetype)initWithAvtarModule:(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *)deviceModel senionMapKey:(NSString*)mapKey senionCustomerID:(NSString*)customerID builidingID:(Eegeo::Resources::Interiors::InteriorId)bulidingID;
-(instancetype)initWithAvtarModule:(ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel *)deviceModel buildingMapKeyList:(NSMutableArray*)buildingMapList;

@end