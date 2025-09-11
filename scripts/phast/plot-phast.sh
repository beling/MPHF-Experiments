#!/bin/bash

./sqlplot-tools ST50M.tex
rm -f ST50Mprev.pdf
pdflatex ST50Mprev.pdf
pdflatex ST50Mprev.pdf

./sqlplot-tools MT50M.tex
rm -f MT50Mprev.pdf
pdflatex MT50Mprev.pdf
pdflatex MT50Mprev.pdf

rm -f *.out *.log *.aux