#pragma once

#include "TableEntry.h"

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

#define VERT_DISTANCE   (0x0fffffff)
using namespace std;

#define VET_BEGIN   \
    list <Vertex> lst;  \
    Vertex te;  \
    memset(&te, 0, sizeof(Vertex)); \

#define VET_HEAD(nom)  {   \
    memset(&te, 0, sizeof(Vertex)); \
    lst.clear();    \
    te.Dist = VERT_DISTANCE; \
    te.Known = Unknown; \
    te.Path = Unpath;   \
    te.vertexNo = nom; \
    te.isAdjunct = false;    \
    lst.push_front(te);  \
    m_vertex.push_front(te);    \
}


#define VET_ADJ(nom)  {   \
    memset(&te, 0, sizeof(Vertex)); \
    te.Dist = VERT_DISTANCE; \
    te.Known = Unknown; \
    te.Path = Unpath;   \
    te.vertexNo = nom; \
    te.isAdjunct = true;    \
    lst.push_back(te);  \
}

#define VET_END {   \
    m_baseGraph.push_front(lst);    \
}


//// 重载的operator< m_sideNo使用
//struct SideNoCmp : public binary_function<SIDE, SIDE, bool>
//{
//	bool operator()(const SIDE& p1, const SIDE& p2) {
//		if (p1.first < p2.first)
//			return true;
//		else if(p1.second < p2.second)
//			return true;
//		else return false;
//	}
//};

class Graph
{
public:
    Graph();
    ~Graph();
private:
    list <list<Vertex> > m_baseGraph;

public:
    int UnweightedGraph(Vertex * start);
    int UnweightedGraph(Vertex * start, Vertex * end);
    int setStartVertex(Vertex * startVertex);
    int findAdjunctList(Vertex * V);
    list <list<Vertex> >::iterator findAdjunctList(list<Vertex>::iterator V);
    int setDist(Vertex * vertex);
    list<list<Vertex> >::iterator findV(list<Vertex>::iterator W);
    int printPath(list<Vertex>::iterator vertex);
    int printPath(Vertex * vertex);
	// 生成段的编号
	int generateSideNo();
	inline vector<int>& GetRoute() { return m_vecRoute; }
	inline map<SIDE, unsigned>& GetSideNoMap() { return m_sideNo; }
	// 重置关系，解决只能2-3，不能3-2的问题
	void ResetVertex();

private:
    int m_startVertex;
    list<Vertex> m_vertex;
	// 保存段的编号
	map<SIDE, unsigned> m_sideNo;
	// 行走路线
	vector<int>		m_vecRoute;
public:
    list<Vertex>::iterator findV2(list<Vertex>::iterator W);
    int setDist2(Vertex * vertex);
    int copyNewList(list<Vertex> & newList);

};

