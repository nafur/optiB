all: mitschrift.pdf

mitschrift.pdf: $(wildcard *.tex)
	pdflatex --halt-on-error mitschrift.tex
	makeglossaries mitschrift
	pdflatex --halt-on-error mitschrift.tex

clean:
	rm -rf *.acn *.acr *.alg *.aux *.glo *.ist *.log *.out *.glg *.ilg *.ind *.toc *.xdy

superclean: clean
	rm -rf *.pdf

keepCompiling:
	iwatch -e modify -c make -t ".*(tex|cls)" .