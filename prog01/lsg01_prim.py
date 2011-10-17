import graph

def minSpanTree(g):
	# prim's algorithm
	
	# store mst
	mst = graph.getgraph(len(g))
	cnt = 0

	# store visited vertices
	vertices = [True] + [False] * (len(mst) - 1)

	# get sorted edges
	a = graph.edgeAscGenerator(g)

	# we need exactly n-1 edges
	while cnt < len(g) - 1:
		new = []
		found = False
		id = 0
		# for all edges
		for (w,x,y) in a:
			id += 1
			if vertices[x] and vertices[y]:
				# would close a circle: drop
				continue
			elif vertices[x] or vertices[y]:
				# can take this -> take it
				vertices[x] = True
				vertices[y] = True
				mst[x][y] = g[x][y]
				cnt += 1
				if cnt == len(g):
					break
				new.extend(a[id:]) # skip the rest
				found = True
				break
			else: # not usable yet -> skip for this round
				new.append((w,x,y))
		a = new
	
	return mst

