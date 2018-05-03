// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"
#include "INavWidgetView.h"
#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetView : public INavWidgetView, Eegeo::NonCopyable
            {
            private:
                AndroidNativeState& m_nativeState;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;

                jclass m_uiViewClass;
                jobject m_uiView;

            public:
                NavWidgetView(AndroidNativeState& nativeState);

                ~NavWidgetView();

                void Show();

                void Hide();

                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel);

                void ClearStartLocation();

                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel);

                void ClearEndLocation();

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleCloseClicked();

            private:
                void SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation);

                void CallVoidMethod(const std::string& methodName);

                jclass CreateJavaClass(const std::string& viewClass);

                jobject CreateJavaObject(jclass uiViewClass);

                jobjectArray CreateJavaArray(const std::vector<std::string>& stringVector);
            };
        }
    }
}
