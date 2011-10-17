import graph
import Queue

def minSpanTree(g):
	# kruskal's algorithm
	
	# store mst
	mst = graph.getgraph(len(g))
	cnt = 0

	# vertex sets
	vertices = map(lambda x: [x], range(0, len(g)))

	# get sorted edges
	q = Queue.PriorityQueue()
	for x in range(0, len(g)):
		for y in g[x]:
			q.put( (g[x][y], x, y) )
	
	# we need exactly n-1 edges
	while len(vertices) > 1:
		(w, x, y) = q.get()
		xid = None
		yid = None
		for i in range(0, len(vertices)):
			if x in vertices[i]:
				xid = i
		if y in vertices[xid]:
			continue
			
		for i in range(0, len(vertices)):
			if y in vertices[i]:
				yid = i
		
		mst[x][y] = w
		vertices[xid] = vertices[xid] + vertices[yid]
		vertices.pop(yid)
		
	return mst

