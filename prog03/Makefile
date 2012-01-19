
default:
	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack1.txt/g' > knapsack1.zpl
	@zimpl knapsack1.zpl >> /dev/null
	./scip -f knapsack1.lp | grep -E "^(objective value|sel#)"

	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack2.txt/g' > knapsack2.zpl
	@zimpl knapsack2.zpl >> /dev/null
	./scip -f knapsack2.lp | grep -E "^(objective value|sel#)"

	@cat knapsack.tpl.zpl | sed 's/§FILENAME§/Knapsack3.txt/g' > knapsack3.zpl
	@zimpl knapsack3.zpl >> /dev/null
	./scip -f knapsack3.lp | grep -E "^(objective value|sel#)"

clean:
	rm -f *.lp *.tbl knapsack1.zpl knapsack2.zpl knapsack3.zpl