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

#include "QueueHistory.h"
#include "Graph.h"

using namespace std;

#define KKK (1024)
#define K10 (KKK * 10)
#define K1000 (KKK * 1000)

#include "ListCollection.h"
#include "afxwin.h"


#define COLOR_WHITE RGB(255,255,255)
#define COLOR_BLACK RGB(0,0,0)
#define COLOR_RED   RGB(255,0,0)
#define COLOR_GREEN     RGB(0, 255, 255)
#define COLOR_BLUE      RGB(0, 0, 255)

// CurveEx

class CurveEx : public CWnd
{
	DECLARE_DYNAMIC(CurveEx)

public:
	CurveEx();
	virtual ~CurveEx();

protected:
	DECLARE_MESSAGE_MAP()
private:
    CDC *m_pMemDC;
    CBitmap *m_pMemBitmap;
    RECT m_cavasArea;
    Graph * m_baseGraph;
public:
    int createCavas(CDC * pDC, int bitMapID, RECT &bitMapSize);
    int updateCavas(int reserved);
    CDC *m_pDC;
    int generateRouteTrace(CDC * pMemDC, CBitmap * pMemBitMap);
	inline Graph* GetGraph() const { return m_baseGraph; }

private:
    ListCollection *m_pLC;
    forward_list <dotpix> m_fl;
    forward_list <dotpix> m_fl2;
    // array<array<int, 2>, 3 > myarray2D;
    int m_img[1920][1080];

public:
    CBitmap *m_pOldBitMap;
    int updateTrace(void);
    int m_bitMapID;
    CBrush m_pOldBrush;
    dotpix m_point;
    // Get the first start point when we do the initial scan to the image
    int getFirstPoint(dotpix & point);
    // Create a simgle-pix trace of the line
    int buildTrace(void);
    map<dotpix, int> m_dotmap;
    map<string, int> m_dotmapstr;
    queue<dotpix> m_pixHistory;
    QueueHistory    m_qh;

    int demoLinkTable(int src, int tar);
};


