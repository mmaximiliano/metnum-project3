filename=informe
TEX = pdflatex

pdf:
	${TEX} ${filename}.tex
	${TEX} ${filename}.tex

read:
	xdg-open ${filename}.pdf

clean:
	rm -f *.pdf
	rm -f *.log
	rm -f *.aux
	rm -f *.out
	rm -f *.toc

