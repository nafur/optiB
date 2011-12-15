TEX = $(shell ls *.tex)
PDF = $(TEX:.tex=.pdf)

all: $(PDF)

%.pdf: %.tex
	pdflatex --halt-on-error $^

clean:
	rm -rf $(PDF)
