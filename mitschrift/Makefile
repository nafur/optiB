all: mitschrift.pdf

mitschrift.pdf: mitschrift.tex
	pdflatex mitschrift.tex
	makeglossaries mitschrift
	pdflatex mitschrift.tex

clean:
	rm -rf *.aux
