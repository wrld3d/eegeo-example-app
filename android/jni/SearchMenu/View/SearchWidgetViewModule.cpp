// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetViewModule.h"
#include "SearchWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchWidgetViewModule::SearchWidgetViewModule(
				AndroidNativeState& nativeState,
				ExampleAppMessaging::TMessageBus& messageBus
			)
			{
				ASSERT_UI_THREAD

				m_pMyTestSearchProvider = Eegeo_NEW(SearchProviders::MyTestSearchProvider)(
						nativeState);
				m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(
						*m_pMyTestSearchProvider,
						messageBus);

				m_pSearchWidgetView = Eegeo_NEW(SearchWidgetView)(
						nativeState,
						*m_pMyTestSearchProvider);
				m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(
						*m_pSearchWidgetView,
						messageBus
				);
			}

			SearchWidgetViewModule::~SearchWidgetViewModule()
			{
				ASSERT_UI_THREAD

				Eegeo_DELETE m_pSearchWidgetView;
				Eegeo_DELETE m_pSearchServices;
				Eegeo_DELETE m_pMyTestSearchProvider;
			}
		}

    }
}
