#pragma once
#include <list>
#include <forward_list>
#include <vector>
#include <array>
#include <deque>
#include <map>
#include <unordered_map>
// #include <hash_map>
#include <unordered_set>
#include <set>
#include <bitset>
#include <queue>

using namespace std;


/* Vertices are numbered from 0*/
#define NotAVertex  (-1)
#define NumVertex   (1000)
typedef struct Vertex Table[NumVertex];


typedef struct dotpix {
    int x;
    int y;
    int color;
    int valid;
    bool operator==(const dotpix& g)const
    {
        if (x == g.x && y == g.y)
            return true;
        else
            return false;
    }


    bool operator<(const dotpix& g)const
    {
        if (y < g.y)
        {
            return true;
        }
        else if (y == g.y && x < g.x)
        {
            return true;
        }
        return false;
    }
}dotpix;


#define HISTORY_DEP (10)
class QueueHistory
{
public:
    QueueHistory();
    ~QueueHistory();
private:
    queue <dotpix> m_traceHistory;
    vector <dotpix> m_traceHistoryV;
public:
    int insertPix(dotpix& dot);
    int checkHistory(dotpix& dot);
};

