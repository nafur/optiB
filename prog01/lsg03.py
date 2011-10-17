import graph
import lsg02

paths = {}

def collapse(g, nodes):
	
	h = graph.getgraph(len(nodes))
	
	for n in nodes:
		(dist, p) = lsg2.SSSP(g, n)
		paths[n] = p
		h[n] = dist
	
	return h

def expand(h, paths):
	pass
