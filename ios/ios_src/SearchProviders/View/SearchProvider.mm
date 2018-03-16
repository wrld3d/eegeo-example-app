// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchProvider.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
        SearchProvider::SearchProvider()
        {
        }

        SearchProvider::~SearchProvider()
        {
        }

        void SearchProvider::InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_autocompleteSuggestionsCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_autocompleteSuggestionsCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::OnSearchResponseReceived(const TSearchResults& searchResults)
        {
            UpdateResults(searchResults, m_pCurrentRequest);
        }

        void SearchProvider::OnAutocompleteSuggestionsResponseReceived(const TSearchResults& searchResults)
        {
            UpdateResults(searchResults, m_pCurrentSuggestion);
        }

        void SearchProvider::UpdateResults(const TSearchResults& searchResults, WRLDSearchRequest* searchRequest)
        {
            WRLDMutableSearchResultsCollection* widgetSearchResults = [[WRLDMutableSearchResultsCollection alloc] init];
            
            for(TSearchResults::const_iterator it = searchResults.begin(); it != searchResults.end(); ++it)
            {
                WRLDBasicSearchResultModel* widgetSearchResult = [[WRLDBasicSearchResultModel alloc] init];
                
                widgetSearchResult.title = [NSString stringWithUTF8String:it->GetName().c_str()];
                widgetSearchResult.subTitle = [NSString stringWithUTF8String:it->GetDescription().c_str()];
                widgetSearchResult.iconKey = [NSString stringWithUTF8String:it->GetIconName().c_str()];
                
                [widgetSearchResults addObject: widgetSearchResult];
            }
            
            [searchRequest didComplete:YES withResults:widgetSearchResults];
        }

        void SearchProvider::PeformSearch(WRLDSearchRequest* searchRequest)
        {
            m_pCurrentRequest = searchRequest;
            std::string searchQuery = [m_pCurrentRequest.queryString cStringUsingEncoding: NSUTF8StringEncoding];
            m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
        }

        void SearchProvider::PeformAutocompleteSuggestions(WRLDSearchRequest* searchRequest)
        {
            m_pCurrentSuggestion = searchRequest;
            std::string searchQuery = [m_pCurrentSuggestion.queryString cStringUsingEncoding: NSUTF8StringEncoding];
            m_autocompleteSuggestionsCallbacks.ExecuteCallbacks(searchQuery);
        }
    }
}
