import time
import sys
import graph
import lsg01_kruskal
import lsg02

for i in range(1, 7):
	t = time.time()

	print("calculating mst for graph " + str(i))
	g = graph.readlgf("Graph" + str(i) + ".lgf")
	mst = lsg01_kruskal.minSpanTree(g)
	graph.writelgf(mst, "Graph" + str(i) + ".mst.lgf")
	t = time.time() - t
	print(str(t) + " seconds")

	(dist, paths) = lsg02.SSSP(g, 1)
	print "Dijkstra: " + str(dist[2])	
