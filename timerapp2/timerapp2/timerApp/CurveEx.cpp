// CurveEx.cpp : implementation file
//

#include "stdafx.h"
// #include "mfcApp.h"
#include "CurveEx.h"

// CurveEx

IMPLEMENT_DYNAMIC(CurveEx, CWnd)

CurveEx::CurveEx()
: m_pMemDC(NULL)
, m_pMemBitmap(NULL)
, m_pDC(NULL)
, m_pLC(NULL)
, m_pOldBitMap(NULL)
, m_bitMapID(0)

{
    m_pMemDC = new CDC();
    m_pMemBitmap = new CBitmap();
    m_cavasArea.bottom = 0;
    m_cavasArea.left = 0;
    m_cavasArea.right = 0;
    m_cavasArea.top = 0;

    m_pLC = new ListCollection();
    memset(&m_img[0][0], COLOR_WHITE, 1920 * 1080);
    m_baseGraph = new Graph();
    list<Vertex>::iterator v;
    // v.vertexNo = 3;
    // list<list<Vertex> >::iterator l = m_baseGraph->findAdjunctList(v);
#if 0
    if (l->size())
    {
        TRACE("Found something\n");
    }
    else {
        TRACE("Found nothing\n");
    }
#endif
}

CurveEx::~CurveEx()
{
    if (m_pOldBitMap) m_pMemDC->SelectObject(m_pOldBitMap);
    if (m_pMemDC) delete m_pMemDC;
    if (m_pMemBitmap) delete m_pMemBitmap;

    if (m_pLC) delete m_pLC;
    if (m_baseGraph) delete m_baseGraph;
}


BEGIN_MESSAGE_MAP(CurveEx, CWnd)
END_MESSAGE_MAP()



// CurveEx message handlers




int CurveEx::createCavas(CDC * pDC, int bitMapID, RECT &bitMapSize)
{
    BITMAP bitmap;

    if (NULL == m_pDC)
    {
        m_pDC = pDC;
        m_bitMapID = bitMapID;
        m_cavasArea.right = bitMapSize.right;
        m_cavasArea.bottom = bitMapSize.bottom;

        m_pMemDC->CreateCompatibleDC(m_pDC);
        m_pMemBitmap->LoadBitmapW(m_bitMapID);
        m_pMemBitmap->GetBitmap(&bitmap);

        m_cavasArea.right = bitmap.bmWidth;
        m_cavasArea.bottom = bitmap.bmHeight;

        m_pOldBitMap = m_pMemDC->SelectObject(m_pMemBitmap);
        generateRouteTrace(m_pMemDC, m_pMemBitmap);
    }
    return 0;
}


int CurveEx::updateCavas(int reserved)
{
    if (m_pDC)
    {
        m_pDC->BitBlt(0, 0, m_cavasArea.right, m_cavasArea.bottom, m_pMemDC, 0, 0, SRCCOPY);
    }
    return 0;
}


int CurveEx::generateRouteTrace(CDC * pMemDC, CBitmap * pMemBitMap)
{
    COLORREF color = 0;

    dotpix dp;
    wstring str;
    int num = 0;
    wchar_t buffer[128];

    dp.x = 0;
    dp.y = 0;
    dp.color=RGB(255,0,0);
    dp.valid = true;


    SetCursor(LoadCursor(NULL,IDC_WAIT));
    for (int xx = 0; xx < m_cavasArea.right; xx ++)
    {
        for (int yy = 0; yy < m_cavasArea.bottom; yy ++)
        {
            dotpix ddp;
            color = pMemDC->GetPixel(xx, yy);
            ddp.x = xx; ddp.y = yy;
            // m_dotmap[ddp] = color;
            // m_dotmapstr["hello"] = 3;
            m_img[xx][yy] = color;
            if (COLOR_WHITE != color)
            {
                dp.x = xx;
                dp.y = yy;
                dp.valid = true;
                dp.color = color;
                m_fl.emplace_front(dp);
            }
        }
    }
    SetCursor(LoadCursor(NULL,IDC_ARROW));
    
    num = std::distance(begin(m_fl), end(m_fl));
    wsprintf (buffer, L"%d", num);
    TRACE1("Total number of pix is: %d\n", num);
    // SetTimer(1, 100, NULL);


    return 0;
}

#define RADIUS  (14)
#define DELTAR  (RADIUS/2)

int CurveEx::updateTrace(void)
{
    m_pOldBitMap = m_pMemDC->SelectObject(m_pOldBitMap);
    m_pMemBitmap->DeleteObject();
    m_pMemBitmap->LoadBitmapW(m_bitMapID);
    m_pOldBitMap = m_pMemDC->SelectObject(m_pMemBitmap);
    CBrush brush(RGB(0,0,0));
    m_pMemDC->SelectObject(&brush);

    RECT rect;

    static forward_list<dotpix>::iterator fwListIterator = m_fl.begin();

    if(fwListIterator != m_fl.end())
    {
        m_point.x = fwListIterator->x;
        m_point.y = fwListIterator->y;

        rect.left = fwListIterator->x-DELTAR;
        rect.right = fwListIterator->x + DELTAR;
        rect.top = fwListIterator->y-DELTAR;
        rect.bottom = fwListIterator->y + DELTAR;
        m_pMemDC->Ellipse(&rect);
        ++fwListIterator;
        updateCavas(0);
    }


    return 0;
}


// Get the first start point when we do the initial scan to the image
int CurveEx::getFirstPoint(dotpix & point)
{
    COLORREF color = 0;

    // dotpix dp;
    wstring str;
    int num = 0;
//    wchar_t buffer[128];
    int xx = 0;

    for (xx = 0; xx < m_cavasArea.right; xx ++)
    {
        for (int yy = 0; yy < m_cavasArea.bottom; yy ++)
        {
            // color = m_pMemDC->GetPixel(xx, yy);
            color = m_img[xx][yy];
            if (COLOR_WHITE != color)
            {
                point.x = xx;
                point.y = yy;
                return 0;
            }
        }
    }
    return 0;
}

typedef enum _dotx {
    upLeft = 0,
    upCenter,
    upRight,
    rightCenter,
    rightBottom,
    bottomCenter,
    bottomLeft,
    leftCenter,
}dotx;

#define UPLEFT  xx-1, yy-1
#define UPCENTER xx, yy-1
#define UPRIGHT xx+1, yy-1
#define RIGHTCENTER  xx+1, yy
#define RIGHTBOTTOM xx+1, yy+1
#define BOTTOMCENTER xx, yy+1
#define BOTTOMLEFT xx-1, yy+1
#define LEFTCENTER xx-1, yy

// Create a simgle-pix trace of the line
int CurveEx::buildTrace(void)
{

    m_pOldBitMap = m_pMemDC->SelectObject(m_pOldBitMap);
    m_pMemBitmap->DeleteObject();
    m_pMemBitmap->LoadBitmapW(m_bitMapID);
    m_pOldBitMap = m_pMemDC->SelectObject(m_pMemBitmap);
    CBrush brush(RGB(0,0,0));
    m_pMemDC->SelectObject(&brush);

    RECT rect;
    dotpix point, pointOld;
    // POINT p[8];
    // COLORREF color;

    getFirstPoint(point);
    m_qh.insertPix(point);
    m_point = point;
    static int xx = point.x;
    static int yy = point.y;
    static int old_xx=xx, old_yy=yy;
    pointOld.x = old_xx; pointOld.y = old_yy;
    static int direction = rightCenter;
    int c = 0;

    // while (1)
    {
        int black_cnt = 0;
        black_cnt = 0;

        // color = m_pMemDC->GetPixel(7,257);
        if (COLOR_WHITE != (c = m_img[xx][yy + 1])) // 6
        {
            dotpix next;
            next.x = (xx);
            next.y = yy + 1;
            if (!(m_qh.checkHistory(next)))
                // if (old_xx != (xx) || old_yy != (yy + 1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx;
                yy++;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c=m_img[xx + 1][yy])) // 4
        {
            dotpix next;
            next.x = (xx + 1);
            next.y = yy;
            if (!(m_qh.checkHistory(next)))
            // if (old_xx != (xx + 1) || old_yy != (yy))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);

                xx++;
                yy;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c = m_img[xx][yy - 1])) // 2
        {
            dotpix next;
            next.x = (xx);
            next.y = yy - 1;
            if (!(m_qh.checkHistory(next)))
                // if (old_xx != (xx) || old_yy != (yy - 1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx;
                yy--;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c = m_img[xx - 1][yy])) // 8
        {
            dotpix next;
            next.x = (xx - 1);
            next.y = yy;
            if (!(m_qh.checkHistory(next)))
                // if (old_xx != (xx-1) || old_yy != (yy))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx--;
                yy;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c=m_img[xx - 1][yy - 1])) // 1
        {
            dotpix next;
            next.x = (xx - 1);
            next.y = yy - 1;
            if (!(m_qh.checkHistory(next)))
            // if (old_xx != (xx - 1) || old_yy != (yy - 1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx--;
                yy--;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c=m_img[xx+1][yy - 1])) // 3
        {
            dotpix next;
            next.x = (xx + 1);
            next.y = yy - 1;
            if (!(m_qh.checkHistory(next)))
            // if (old_xx != (xx+1) || old_yy != (yy - 1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx++;
                yy--;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c=m_img[xx+1][yy +1])) // 5
        {
            dotpix next;
            next.x = (xx + 1);
            next.y = yy+1;
            if (!(m_qh.checkHistory(next)))
            // if (old_xx != (xx+1) || old_yy != (yy+1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx++;
                yy++;
                goto sigh;
            }
        }
        if (COLOR_WHITE != (c=m_img[xx-1][yy + 1])) // 7
        {
            dotpix next;
            next.x = (xx - 1);
            next.y = yy+1;
            if (!(m_qh.checkHistory(next)))
            // if (old_xx != (xx-1) || old_yy != (yy + 1))
            {
                old_xx = xx; old_yy = yy;
                pointOld.x = xx;
                pointOld.y = yy;
                m_qh.insertPix(pointOld);
                xx--;
                yy++;
                goto sigh;
            }
        }
    }
    sigh:
#if 1
    m_point.x = xx;
    m_point.y = yy;
    rect.left = xx - DELTAR;
    rect.right = xx + DELTAR;
    rect.top = yy - DELTAR;
    rect.bottom = yy + DELTAR;
#endif
    m_pMemDC->Ellipse(&rect);

    updateCavas(0);

    return 0;
}

#define TARGET_VERTEX   (17)
int CurveEx::demoLinkTable(int src, int tar)
{

	Vertex te;
	list<Vertex> newList;

	// 生成段号
	static bool bGen = true;
	if (bGen) {
		m_baseGraph->generateSideNo();
		bGen = false;
	}

	te.vertexNo = src;
	m_baseGraph->UnweightedGraph(&te);

    memset(&te, 0, sizeof(Vertex));
    te.vertexNo = tar;
    m_baseGraph->printPath(&te);
    TRACE("Target(%d)\n", TARGET_VERTEX);
	m_baseGraph->GetRoute().push_back(tar);
	m_baseGraph->ResetVertex(); // 重置关系，解决只能2-3，不能3-2的问题

    // m_baseGraph->copyNewList(newList);
    return 0;
}
