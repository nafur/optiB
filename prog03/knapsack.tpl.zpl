param filename := "§FILENAME§";

set OBJ := { 
	read filename as "<1n>" skip 2 comment "#" 
};

param weight[OBJ] := 
	read filename as "<1n> 2n" skip 2 comment "#"
;
param value[OBJ] := 
	read filename as "<1n> 3n" skip 2 comment "#"
;
param size :=  
	read filename as "1n" skip 1 use 1 comment "#"
;

var sel[OBJ] binary;

subto cSize:
	(sum <o> in OBJ: weight[o] * sel[o]) <= size
;

maximize profit:
	sum <o> in OBJ: value[o] * sel[o]
;