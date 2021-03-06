// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMenuOption.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"
#include "MyPinSelectedMessage.h"
#include "IMenuViewModel.h"
#include "MyPinModel.h"
#include "LatLongAltitude.h"
#include "InteriorId.h"
#include <string>
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinMenuOption : public Menu::View::IMenuOption
            {
            public:
                MyPinMenuOption(SdkModel::MyPinModel::TPinIdType pinId,
                                const Eegeo::Space::LatLong& pinLocation,
                                const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                int targetFloor,
                                Menu::View::IMenuViewModel& menuViewModel,
                                ExampleAppMessaging::TMessageBus& messageBus,
                                const Menu::View::IMenuReactionModel& menuReaction)
                    : m_pinId(pinId)
                    , m_pinLocation(pinLocation)
                    , m_interiorId(interiorId)
                    , m_targetFloor(targetFloor)
                    , m_menuViewModel(menuViewModel)
                    , m_messageBus(messageBus)
                    , m_menuReaction(menuReaction)
                {

                }

                void Select()
                {
                    if (m_menuReaction.GetShouldCloseMenu())
                    {
                        m_menuViewModel.Close();
                    }

                    m_messageBus.Publish(MyPinSelectedMessage(m_pinId, m_pinLocation, m_interiorId, m_targetFloor));
                }

            private:
                SdkModel::MyPinModel::TPinIdType m_pinId;
                Eegeo::Space::LatLong m_pinLocation;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_targetFloor;
                
                Menu::View::IMenuViewModel& m_menuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const Menu::View::IMenuReactionModel& m_menuReaction;
            };
        }
    }
}
