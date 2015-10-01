// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultMenuOrder.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            namespace Swallow
            {
                class SwallowSearchResultMenuOrder : public ISearchResultMenuOrder
                {
                public:
                    bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b);
                };
            }
        }
    }
}