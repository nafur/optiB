import re

# read adjacency matrix from lgf file
def readlgf(filename):
	# read lines
	f = file(filename)
	lines = f.readlines()
	f.close()
	
	nodes = {}
	graph = []
	
	r = re.compile("(\\d+) (\\d+) (\\d+)")
	
	# mode = 0: skip
	# mode = 1: read node names
	# mode = 2: read edges
	mode = 0
	for l in lines:
		l = l.strip()
		if l == "":
			continue
		
		if mode == 1:
			if l.isdigit():
				# store node names
				nodes[l] = len(nodes)
		elif mode == 2:
			# parse edge
			res = r.match(l)
			if res != None:
				nfrom = nodes[res.group(1)]
				nto = nodes[res.group(2)]
				weight = int(res.group(3))
				
				# store weights
				graph[nfrom][nto] = weight
				graph[nto][nfrom] = weight
			

		if l == "label":
			mode = 1
		elif l == "weight":
			mode = 2
			# init graph
			graph = getgraph(len(nodes))
	
	return graph

def writelgf(graph, filename):
	f = file(filename, "w")
	f.write("@nodes\n")
	f.write("label\n")
	for i in range(0, len(graph)):
		f.write(str(i+1) + "\n")
	f.write("@edges\n")
	f.write("    weight\n")
	for x in range(0, len(graph)):
		for y in range(0, len(graph)):
			if y in graph[x]:
				f.write(str(x+1) + " " + str(y+1) + " " + str(graph[x][y]) + "\n")

# generate all edges sorted by weigth
def edgeAscGenerator(graph):
	a = []
	# collect all edges
	for x in range(0, len(graph)):
		for y in range(0, len(graph)):
			if y in graph[x]:
				a.append( (graph[x][y], x, y) )
	
	# sort by weight
	a.sort(key=lambda x: x[0])
	
	return a
	
def getgraph(n):
	res = []
	for i in range(0, n):
		res.append({})
	return res
