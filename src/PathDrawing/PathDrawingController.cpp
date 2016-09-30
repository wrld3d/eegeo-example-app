// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingController.h"
#include "RouteBuilder.h"
#include "RouteStyle.h"
#include "WayPointsRepository.h"
#include "WayPointType.h"
#include "LatLongAltitude.h"
#include "IMenuSectionViewModel.h"
#include "IMenuModel.h"
#include "SearchResultItemModel.h"

using namespace Eegeo;
using namespace Eegeo::Routes;

namespace ExampleApp
{
    namespace PathDrawing
    {
        

        PathDrawingController::PathDrawingController(Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                     Eegeo::Routes::RouteService& routeService

                                                     , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                     , PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository
                                                     , ExampleAppMessaging::TMessageBus& messageBus)
        : m_routeService(routeService)
        , m_cameraWrapper(cameraWrapper)
        , m_pWayPointsRepository(wayPointsRepository)
        , m_createdRoutes(false)
        , m_messageBus(messageBus)
        , m_searchSectionViewModel(searchSectionViewModel)
        , m_directionResultReceivedHandler(this, &PathDrawingController::OnSearchQueryResponseReceivedMessage)
        , m_directionsMenuStateChangedCallback(this, &PathDrawingController::OnDirectionsMenuStateChanged)
        , m_onDirectionItemAddedCallback(this, &PathDrawingController::OnSearchItemAdded)
        , m_onDirectionItemRemovedCallback(this, &PathDrawingController::OnSearchItemRemoved)
        {
            m_pPathDrawingSettings = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingOptionsModel)();
            m_routeThicknessPolicy.SetScaleFactor(1.0f);
            
            m_messageBus.SubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            
            Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
            searchSectionMenuModel.InsertItemAddedCallback(m_onDirectionItemAddedCallback);
            searchSectionMenuModel.InsertItemRemovedCallback(m_onDirectionItemRemovedCallback);
            
            
        }
        
        PathDrawingController::~PathDrawingController()
        {
            Eegeo_DELETE m_pPathDrawingSettings;
            m_messageBus.UnsubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);

        }
        
        void PathDrawingController::OnSearchItemAdded(Menu::View::MenuItemModel& item)
        {
            ExampleApp::SearchResultSection::View::SearchResultItemModel &searchItem = (ExampleApp::SearchResultSection::View::SearchResultItemModel&)item.MenuOption();

            Eegeo::Space::LatLong latLongStart = Eegeo::Space::LatLong::FromECEF(searchItem.GetLocationEcef());
            WayPointModel* point = Eegeo_NEW(ExampleApp::PathDrawing::WayPointModel)(searchItem.GetItemIndex()
                                                                         , ExampleApp::PathDrawing::WayPointType::CheckPoint
                                                                         , latLongStart
                                                                         , "");
            m_pWayPointsRepository.AddItem(point);
        }
        
        void PathDrawingController::OnSearchItemRemoved(Menu::View::MenuItemModel& item)
        {

        }

        
        void PathDrawingController::Update(float dt)
        {
            
            if(m_createdRoutes)
            {
                float altitude = m_cameraWrapper.GetRenderCamera().GetAltitude();
                m_routeThicknessPolicy.SetAltitude(altitude);
            }
            
        }
        
        void PathDrawingController::OnSearchQueryResponseReceivedMessage(const DirectionResultSection::DirectionQueryResponseReceivedMessage& message)
        {
            
            if(!m_createdRoutes)
            {
                CreateRoutePlan();
            }
        }
        
        void PathDrawingController::CreateRoutePlan()
        {
            
            
            const float altitudeMeters = m_pPathDrawingSettings->GetRouteAltitudeMeter();;
            
            Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
            
            RouteBuilder builder;
            
            std::vector<RouteVertex> points = builder.Start(m_pPathDrawingSettings->GetRoutePrimaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road)
            .AddPoint(56.459676, -2.977240, altitudeMeters)
            .AddPoint(56.459178, -2.975524, altitudeMeters)
            .AddPoint(56.458467, -2.973764, altitudeMeters)
            .AddPoint(56.457827, -2.972691, altitudeMeters)
            .AddPoint(56.457779, -2.971833, altitudeMeters)
            .AddPoint(56.457771, -2.971389, altitudeMeters)
            .AddPoint(56.457860, -2.970793, altitudeMeters)
            .AddPoint(56.458822, -2.968892, altitudeMeters)
            .AddPoint(56.461725, -2.964054, altitudeMeters)
            .AddPoint(56.461547, -2.963546, altitudeMeters)
            .AddPoint(56.461427, -2.963596, altitudeMeters)
            .AddPoint(56.461369, -2.963540, altitudeMeters)
            .AddPoint(56.460882, -2.962729, altitudeMeters)
            .FinishRoute();
            
            m_routes.push_back(m_routeService.CreateRoute(points, routeStyle, false));
            
            std::vector<RouteVertex> otherPoints = builder.Start(m_pPathDrawingSettings->GetRouteSecondaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road)
            .AddPoint(56.459892, -2.977749,altitudeMeters)
            .AddPoint(56.460158, -2.977831,altitudeMeters)
            .AddPoint(56.460606, -2.977981,altitudeMeters)
            .AddPoint(56.462455, -2.978974,altitudeMeters)
            .AddPoint(56.463196, -2.979505,altitudeMeters)
            .AddPoint(56.463535, -2.979869,altitudeMeters)
            .AddPoint(56.463681, -2.980184,altitudeMeters)
            .AddPoint(56.463768, -2.980262,altitudeMeters)
            .AddPoint(56.463861, -2.980238,altitudeMeters)
            .AddPoint(56.463928, -2.980107,altitudeMeters)
            .AddPoint(56.463976, -2.979909,altitudeMeters)
            .AddPoint(56.463928, -2.979225,altitudeMeters)
            .AddPoint(56.463931, -2.978906,altitudeMeters)
            .AddPoint(56.463882, -2.978477,altitudeMeters)
            .AddPoint(56.463823, -2.978093,altitudeMeters)
            .AddPoint(56.463796, -2.978014,altitudeMeters)
            .AddPoint(56.463773, -2.977828,altitudeMeters)
            .AddPoint(56.463683, -2.977304,altitudeMeters)
            .AddPoint(56.463655, -2.977026,altitudeMeters)
            .AddPoint(56.463634, -2.976777,altitudeMeters)
            .AddPoint(56.463636, -2.976409,altitudeMeters)
            .AddPoint(56.463683, -2.976041,altitudeMeters)
            .AddPoint(56.463817, -2.975528,altitudeMeters)
            .AddPoint(56.464249, -2.974152,altitudeMeters)
            .AddPoint(56.464311, -2.973874,altitudeMeters)
            .AddPoint(56.464367, -2.973519,altitudeMeters)
            .AddPoint(56.464432, -2.973333,altitudeMeters)
            .AddPoint(56.464513, -2.973320,altitudeMeters)
            .AddPoint(56.464578, -2.973192,altitudeMeters)
            .AddPoint(56.464598, -2.973014,altitudeMeters)
            .AddPoint(56.464649, -2.972897,altitudeMeters)
            .AddPoint(56.464935, -2.971895,altitudeMeters)
            .AddPoint(56.465076, -2.971219,altitudeMeters)
            .AddPoint(56.465143, -2.970771,altitudeMeters)
            .AddPoint(56.465186, -2.970261,altitudeMeters)
            .AddPoint(56.465184, -2.969797,altitudeMeters)
            .AddPoint(56.465160, -2.969224,altitudeMeters)
            .AddPoint(56.465152, -2.968634,altitudeMeters)
            .AddPoint(56.465128, -2.968031,altitudeMeters)
            .AddPoint(56.465097, -2.967573,altitudeMeters)
            .AddPoint(56.465056, -2.967259,altitudeMeters)
            .AddPoint(56.464967, -2.966765,altitudeMeters)
            .AddPoint(56.464806, -2.966072,altitudeMeters)
            .AddPoint(56.464308, -2.964426,altitudeMeters)
            .AddPoint(56.464328, -2.964205,altitudeMeters)
            .AddPoint(56.464246, -2.963995,altitudeMeters)
            .AddPoint(56.464118, -2.963946,altitudeMeters)
            .AddPoint(56.464010, -2.964042,altitudeMeters)
            .AddPoint(56.463774, -2.963951,altitudeMeters)
            .AddPoint(56.463556, -2.963799,altitudeMeters)
            .AddPoint(56.462876, -2.962969,altitudeMeters)
            .AddPoint(56.462710, -2.962603,altitudeMeters)
            .AddPoint(56.462633, -2.962464,altitudeMeters)
            .AddPoint(56.462521, -2.962678,altitudeMeters)
            .AddPoint(56.462229, -2.963078,altitudeMeters)
            .AddPoint(56.461981, -2.963456,altitudeMeters)
            .AddPoint(56.461686, -2.963953,altitudeMeters)
            .AddPoint(56.461524, -2.963569,altitudeMeters)
            .AddPoint(56.461441, -2.963602,altitudeMeters)
            .AddPoint(56.461363, -2.963558,altitudeMeters)
            .AddPoint(56.460882, -2.962729,altitudeMeters)
            .FinishRoute();
            
            m_routes.push_back(m_routeService.CreateRoute(otherPoints, routeStyle, false));
        
            m_createdRoutes = true;
        }
        
        void PathDrawingController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
        {
            if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
            {
                RemoveRoutePlan();
            }
        }
        
        
        void PathDrawingController::RemoveRoutePlan()
        {
            for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
            {
                m_routeService.DestroyRoute(*i);
            }
            
            m_routes.clear();
            
            while (m_pWayPointsRepository.GetItemCount() != 0)
            {
                WayPointModel* waypoint = m_pWayPointsRepository.GetItemAtIndex(0);
                m_pWayPointsRepository.RemoveItem(waypoint);
                Eegeo_DELETE waypoint;
            }
           m_createdRoutes = false;
        }
    }
}

