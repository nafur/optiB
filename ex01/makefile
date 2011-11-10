all: *.pdf

%.pdf: %.tex
	pdflatex --halt-on-error $^

clean: rm -rf *.pdf
