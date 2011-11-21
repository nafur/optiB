all: mitschrift.pdf

mitschrift.pdf: $(wildcard *.tex)
	pdflatex mitschrift.tex
	makeglossaries mitschrift
	pdflatex mitschrift.tex

clean:
	rm -rf *.aux
