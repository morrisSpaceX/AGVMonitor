#include "stdafx.h"
#include "Graph.h"

static int no = 0;

Graph::Graph()
    : m_startVertex(0)
{
    VET_BEGIN;  

#include "Header.h"        

    // SETUP_GRAPH;
    // UnweightedGraph(&te, &te);
}


Graph::~Graph()
{
}


int Graph::UnweightedGraph(Vertex * start)
{
    // We find out the shortest path inside m_baseGraph from start point 'start'
    UnweightedGraph(start, start);
    return 0;
}


int Graph::UnweightedGraph(Vertex * start, Vertex * end)
{
    // We find out the shortest path inside m_baseGraph from start point 'start' to 'end' point
    int CurrDist = 0;
    list<Vertex>::iterator V, W;
    
    TRACE("Enter UnweightedGraph\n");
    // MessageBox(NULL, L"Hello", L"World", MB_OK);
    setStartVertex(start);
    TRACE("Start vertex is(%d)\n", start->vertexNo);

    for (CurrDist = 0; CurrDist < NumVertext; CurrDist++)
    {
        TRACE("CurrDist=(%4d)\n", CurrDist);
        for (list<Vertex>::iterator r = m_vertex.begin(); r != m_vertex.end(); r ++)
        // for (list<list<Vertex> >::iterator r = m_baseGraph.begin(); r != m_baseGraph.end(); r++)
        {
            {
                // V = r->begin();
                V = r;
                TRACE("Link Table Head(%d)Known(%s)Dist(%d=>%d)Path(%d)\n", (V->vertexNo), (V->Known==Known)?"Known":"Unknown", V->Dist, CurrDist, V->Path);
                if (V->Known == Unknown && V->Dist == CurrDist)
                {
                    TRACE("We got V(%d)Dist(%d)\n", V->vertexNo, V->Dist);
                    V->Known = Known;
                    list<list<Vertex> >::iterator adjunctList = findAdjunctList(V);
                    for (list<Vertex>::iterator adj = adjunctList->begin(); adj != adjunctList->end(); adj ++)
                    {
                        list<Vertex>::iterator v = findV2(adj);
                        W = v;
                        if (W->Dist == VERT_DISTANCE)
                        {
                            Vertex vv;
                            vv.Dist = CurrDist + 1;
                            vv.Path = V->vertexNo;
                            vv.vertexNo = W->vertexNo;
                            // W->Dist = CurrDist + 1;
                            // W->Path = V->vertexNo;
                            // TRACE("adj->Vertex(%d)Dist(%d)path(%d)\n", adj->vertexNo, adj->Dist, adj->Path);
                            setDist2(&vv);
                            TRACE("We set adjunction V(%d):W(%d) with Dist(%d)Path(%d)\n", V->vertexNo, W->vertexNo, W->Dist, V->vertexNo);
                        }
                    }
                }
            }
        }
    }


    return 0;
}


int Graph::setStartVertex(Vertex * startVertex)
{
    Vertex V;

    for (list<Vertex>::iterator r = m_vertex.begin(); r != m_vertex.end(); r++)
    {
        // list<Vertex>::iterator s = r;
        list<Vertex>::iterator it = r;
        // for (list<Vertex>::iterator vit = s.begin(); vit != s.end(); vit++)
        {
            if (startVertex->vertexNo == it->vertexNo)
            {
                V.Dist = 0;
                V.Known = Unknown;
                it->Dist = 0;
                it->Known = Unknown;
                m_startVertex = it->vertexNo;
                return 0;
            }
        }
    }

    return 0;
}


int Graph::findAdjunctList(Vertex * V)
{
    return 0;
}


list <list<Vertex> >::iterator Graph::findAdjunctList(list<Vertex>::iterator V)
{
    for (list<list<Vertex> >::iterator r = m_baseGraph.begin(); r != m_baseGraph.end(); r++)
    {
        list<Vertex>::iterator startVertex = r->begin();
        if (startVertex->vertexNo == V->vertexNo)
        {
            return r;
        }
    }

    // list<Vertex> l;
    // list <list<Vertex> >::iterator ll = find(m_baseGraph.begin(), m_baseGraph.end(), l);

    return list <list<Vertex> >::iterator();
}


int Graph::setDist(Vertex * vertex)
{
    for (list<list<Vertex> >::iterator r = m_baseGraph.begin(); r != m_baseGraph.end(); r++)
    {
        // list<Vertex>::iterator s = r;
        list<Vertex>::iterator it = r->begin();
        // for (list<Vertex>::iterator vit = s.begin(); vit != s.end(); vit++)
        {
            if (vertex->vertexNo == it->vertexNo)
            {
                it->Dist = vertex->Dist;
                it->Path = vertex->Path;
                // it->Known = Unknown;
                return 0;
            }
        }
    }
    return 0;
}


list<list<Vertex> >::iterator Graph::findV(list<Vertex>::iterator W)
{
    for (list<list<Vertex> >::iterator r = m_baseGraph.begin(); r != m_baseGraph.end(); r++)
    {
        list<Vertex>::iterator startVertex = r->begin();
        if (startVertex->vertexNo == W->vertexNo)
        {
            return r;
        }
    }
    return list<list<Vertex> >::iterator();
}


int Graph::printPath(list<Vertex>::iterator vertex)
{
    if (vertex->Path != Unpath)
    {
        list<list<Vertex> >::iterator v = findV(vertex);
        printPath(v->begin());
    }
    return 0;
}


int Graph::printPath(Vertex * vertex)
{
    list<Vertex>::iterator r;
    list<Vertex>::iterator it;
    Vertex vv;


    for (r = m_vertex.begin(); r != m_vertex.end(); r++)
    {
        it = r;
        if (vertex->vertexNo == it->vertexNo)
        {
            // TRACE("(%d)\n", it->vertexNo);
            break;
        }
    }

    if (it->vertexNo == m_startVertex)
    {
        TRACE("Source(%d)\n", m_startVertex);
        return 0;
    }


    memset(&vv, 0, sizeof(Vertex));
    vv.vertexNo = it->Path;
    vv.Path = it->Path;
    if (vv.Path != Unknown)
    {
        // TRACE("to(%d)\n", it->Path);
        printPath(&vv);
        // TRACE(" to");
    }
    TRACE("(%d)\n", vv.vertexNo);

    return 0;
}


list<Vertex>::iterator Graph::findV2(list<Vertex>::iterator W)
{
    for (list<Vertex>::iterator r = m_vertex.begin(); r != m_vertex.end(); r++)
    {
        list<Vertex>::iterator startVertex = r;
        if (startVertex->vertexNo == W->vertexNo)
        {
            return r;
        }
    }
    return list<Vertex>::iterator();
}


int Graph::setDist2(Vertex * vertex)
{
    for (list<Vertex>::iterator r = m_vertex.begin(); r != m_vertex.end(); r++)
    {
        // list<Vertex>::iterator s = r;
        list<Vertex>::iterator it = r;
        // for (list<Vertex>::iterator vit = s.begin(); vit != s.end(); vit++)
        {
            if (vertex->vertexNo == it->vertexNo)
            {
                it->Dist = vertex->Dist;
                it->Path = vertex->Path;
                // it->Known = Unknown;
                return 0;
            }
        }
    }
    return 0;
}


int Graph::copyNewList(list<Vertex> & newList)
{
    std::copy(m_vertex.begin(), m_vertex.end(), std::back_inserter(newList));

    return 0;
}



int Graph::generateSideNo()
{
	static unsigned SIDE_NO = 1;
	// �������ж���
	for (auto verIter = m_vertex.begin(); verIter != m_vertex.end(); ++verIter)
	{
		int vertexNo = (*verIter).vertexNo;
		// �ҵ��ھӱ�
		auto& adjList = *findAdjunctList(verIter);

		// ����ÿ���ھӣ����α�Ų�����
		auto adjIter = adjList.begin();
		std::advance(adjIter, 1); // ��������
		for (; adjIter != adjList.end(); ++adjIter)
		{
			int sideNo = (*adjIter).vertexNo;
			// �Ȳ�����û������Σ���1��2���ͣ�2��1����ͬ
			auto findIter = m_sideNo.find(make_pair(sideNo, vertexNo));
			if (m_sideNo.end() == findIter)
			{ // û���ҵ�
				auto sidePair = make_pair(vertexNo, sideNo);
				m_sideNo.insert(make_pair(sidePair, SIDE_NO++));
			}
			else
			{
				auto sidePair = make_pair(vertexNo, sideNo);
				m_sideNo.insert(make_pair(sidePair, findIter->second));
			}
		}
	}
	return(0);
}