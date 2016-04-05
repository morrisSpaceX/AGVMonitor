#include "stdafx.h"
#include "QueueHistory.h"


QueueHistory::QueueHistory()
{
}


QueueHistory::~QueueHistory()
{
}


int QueueHistory::insertPix(dotpix& dot)
{
    if (m_traceHistoryV.size() >= HISTORY_DEP)
    {
        m_traceHistoryV.pop_back();
    }
    // m_traceHistory.push(dot);
    vector<dotpix>::iterator theIterator = m_traceHistoryV.begin();
    m_traceHistoryV.insert(theIterator, dot);

    return 0;
}


int QueueHistory::checkHistory(dotpix& dot)
{
    vector<dotpix>::iterator result = find(m_traceHistoryV.begin(), m_traceHistoryV.end(), dot);

    if (result == m_traceHistoryV.end())
        return 0;
    else
        return 1;
}
