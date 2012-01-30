param filename := "§FILENAME§";


param size :=  
	read filename as "2n" use 1 comment "#"
;

set N :=
	{ 1 .. (size*size) }
;
set M := 
	{ 1 .. size }
;

set given :=
	{ read filename as "<1n,2n,3n>" skip 1 comment "#" }
;

var res[N * N * N] binary;

maximize cost: 0 * 
	(sum <x,y,z> in N*N*N: res[x,y,z])
;

subto Given:
	forall <x,y,z> in given do
		res[x,y,z] == 1
;
subto SingleChoice:
	forall <x,y> in N*N do
		sum <z> in N: res[x,y,z] == 1
;
subto Cols:
	forall <x,z> in N*N do
		sum <y> in N: res[x,y,z] == 1
;
subto Rows:
	forall <y,z> in N*N do
		sum <x> in N: res[x,y,z] == 1
;
subto SubMatrix:
	forall <a,b,z> in M*M*N do
		sum <x,y> in M*M: res[(a-1)*size+x,(b-1)*size+y,z] == 1
;

§SPECIAL§