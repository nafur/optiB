import time
import sys
import graph
import os
import fnmatch

import lsg01
import lsg02
import lsg03

for i in range(1, 2):
	t = time.time()

	print("calculating mst for graph " + str(i))
	g = graph.readlgf("Graph" + str(i) + ".lgf")
	mst = lsg01.minSpanTree(g)
	graph.writelgf(mst, "Graph" + str(i) + ".mst.lgf")
	t = time.time() - t
	print(str(t) + " seconds")

	(dist, paths) = lsg02.SSSP(g, 1)
	print "Dijkstra: " + str(dist[2])	

	for file in os.listdir("."):
		if fnmatch.fnmatch(file, "Graph" + str(i) + "_Terminals*.txt"):
			lsg03.steiner(g, graph.readterminals(file))
