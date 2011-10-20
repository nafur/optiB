#include "dijkstra.h"

#include <queue>
#include <set>
#include <limits>

struct vert
{
	vertex v;
	edge::weight_type dist;
	
	bool operator<(const vert& v) const
	{
		return this->dist < v.dist;
	}
	vert(vertex v, edge::weight_type dist): v(v), dist(dist) {}
	vert(const vert& v): v(v.v), dist(v.dist) {}
};

void dijkstra(graph& g, const vertex source, map<vertex::vertex_id, edge::weight_type> weights, map<vertex::vertex_id, vertex::vertex_id> pred)
{
	
	priority_queue<vert> todo;
	set<vertex::vertex_id> done;
	vert src(source, 0);	
	todo.push(src);
	done.insert(source.id);
	pred[source.id] = 0;
	
	typedef map<vertex::vertex_id, edge::weight_type>::iterator vertit;
	for (vertit it = weights.begin(); it != weights.end(); it++)
	{
		it->second = numeric_limits<edge::weight_type>::max();
	}
	
	while (! todo.empty())
	{
		vert cur = todo.top();
		todo.pop();
		vertex::vertex_id curid = cur.v.id;
		edge::weight_type dst = weights[curid];
		
		typedef map<vertex::vertex_id, edge>::iterator mapit;
		for (mapit it = g.edges[curid].begin(); it != g.edges[curid].end(); it++)
		{
			if (dst + it->second < weigths[it->first])
			{
				weights[it->first] = dst + it->second;
				pred[it->first] = it->second;
				if (! done.contains(it->first))
				{
					vert next(it->first, weights[it->first]):
					todo.push(next);
				}
			}
		}
		done.insert(curid);
	}
}
