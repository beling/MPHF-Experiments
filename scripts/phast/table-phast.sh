#!/bin/bash

./sqlplot-tools table-phast.tex
rm -f table-phast.pdf
pdflatex table-phast.tex
pdflatex table-phast.tex
rm -f *.out *.log *.aux