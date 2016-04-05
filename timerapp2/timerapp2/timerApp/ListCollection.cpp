// ListCollection.cpp : implementation file
//

#include "stdafx.h"
// #include "mfcApp.h"
#include "ListCollection.h"

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

using namespace std;

#define KKK (1024)
#define K10 (KKK * 10)
#define K1000 (KKK * 1000)



// ListCollection

ListCollection::ListCollection()
{
    createCList(K10);
}

ListCollection::~ListCollection()
{
}


// ListCollection member functions

typedef struct _dotpix {
    int x;
    int y;
    int color;
    int valid;
}dotpix;

int ListCollection::createCList(int num)
{
    forward_list <dotpix> fl;
    dotpix dp;

    dp.x = 0;
    dp.y = 0;
    dp.color=RGB(255,0,0);
    dp.valid = true;

    for (int i = 0; i < num; i ++)
    {
        fl.emplace_front(dp);
    }

    return 0;
}
