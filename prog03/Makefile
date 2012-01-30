
knapsack:
	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack1.txt/g' > knapsack1.zpl
	@zimpl knapsack1.zpl >> /dev/null
	./scip -f knapsack1.lp | grep -E "^(objective value|sel#)"

	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack2.txt/g' > knapsack2.zpl
	@zimpl knapsack2.zpl >> /dev/null
	./scip -f knapsack2.lp | grep -E "^(objective value|sel#)"

	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack3.txt/g' > knapsack3.zpl
	@zimpl knapsack3.zpl >> /dev/null
	./scip -f knapsack3.lp | grep -E "^(objective value|sel#)"

sudoku9:
	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/Sudoku9.data/g' | sed 's/§SPECIAL§//g' > sudoku9.zpl
	zimpl sudoku9.zpl
	./scip -f sudoku9.lp | grep -E "^(objective value|res#)"

sudoku16:
	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/Sudoku16.data/g' | sed 's/§SPECIAL§//g' > sudoku16.zpl
	zimpl sudoku16.zpl
	./scip -f sudoku16.lp | grep -E "^(objective value|res#)"

	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/Sudoku16.data/g' | sed 's/§SPECIAL§/subto dif: res[1,1,5] == 0;/g' > sudoku16.zpl
	zimpl sudoku16.zpl
	./scip -f sudoku16.lp | grep -E "^(objective value|res#)"

	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/Sudoku16.data/g' | sed 's/§SPECIAL§/subto dif: res[1,1,5] == 0; subto dif2: res[1,1,8] == 0;/g' > sudoku16.zpl
	zimpl sudoku16.zpl
	./scip -f sudoku16.lp | grep -E "^(objective value|res#)"

sudoku25:
	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/Sudoku25.data/g' | sed 's/§SPECIAL§//g' > sudoku25.zpl
	zimpl sudoku25.zpl
	./scip -f sudoku25.lp

sudoku36:
	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/BonusSudoku.data/g' | sed 's/§SPECIAL§/set g2:={read "BonusManual.data" as "<1n,2n,3n>" skip 1 comment "#"}; subto G2: forall <x,y,z> in g2: res[x,y,z]==1;/g' > sudokuBonus.zpl
#	@cat sudoku.tpl.zpl | sed 's/§FILENAME§/BonusSudoku.empty.data/g' | sed 's/§SPECIAL§//g' > sudokuBonus.zpl
	zimpl sudokuBonus.zpl
	./scip -f sudokuBonus.lp

