// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "MenuView.h"
#include "ISearchWidgetView.h"
#include "MyTestSearchProvider.h"
#include "IMenuView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetView : public SearchMenu::View::ISearchWidgetView
            {
            private:
                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;

            public:
                SearchWidgetView(AndroidNativeState& nativeState,
                                 SearchProviders::MyTestSearchProvider& searchProvider);
                void UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged);

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
            };

        }
    }
}
