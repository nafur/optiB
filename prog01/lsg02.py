import sys
import graph

def SSSP(g, u):
	# do dijkstra...
	
	todo = [u]
	res = {u: 0}
	paths = {u: None}
	while len(todo) > 0:
		cur = todo.pop()
		dist = res[cur]
		
		for (node, weight) in g[cur].iteritems():
			if node in res:
				if res[node] > dist + weight:
					res[node] = dist + weight
					paths[node] = cur
			else:
				res[node] = dist + weight
				paths[node] = cur
				todo.append(node)

	return (res, paths)
