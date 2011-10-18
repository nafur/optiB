import graph

import lsg01
import lsg02

def collapse(g, nodes):
	
	h = graph.getgraph(len(nodes))
	paths = {}
	
	for n in range(0, len(nodes)):
		(dist, p) = lsg02.SSSP(g, nodes[n])
		print "path for " + str(n) + ": " + str(p)
		paths[n] = p
		for m in range(0, len(nodes)):
			h[n][m] = dist[nodes[m]]
	
	return (h, paths)

def expand(h, paths, nodes):
	print h
	print nodes
	print "paths:"
	print paths
	pass

def steiner(g, nodes):
	(h, paths) = collapse(g, nodes)
	mst = lsg01.minSpanTree(h)
	print mst
	expand(mst, paths, nodes)
