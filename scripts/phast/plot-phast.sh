#!/bin/bash

./sqlplot-tools ST50M.tex
rm -f ST50Mprev.pdf
pdflatex ST50Mprev.tex
pdflatex ST50Mprev.tex

./sqlplot-tools MT50M.tex
rm -f MT50Mprev.pdf
pdflatex MT50Mprev.tex
pdflatex MT50Mprev.tex

rm -f *.out *.log *.aux