
#n = 3
#w = [0, 1, 3, 2]
#v = [0, 1, 4, 3]
#B = 4
n = 3
w = [0, 1, 3, 2]
v = [0, 0.5, 4, 3]
B = 5

R = []
for i in range(0, n+2):
	R.append([0] * (B+1))

for i in range(n, 0, -1):
	print R
	for j in range(1, B+1):
		if w[i] <= j:
			R[i][j] = max(v[i] + R[i+1][j-w[i]], R[i+1][j] )
		else:
			R[i][j] = R[i+1][j]

print R[1][B]