@echo off 
set filename=%1
@echo pdflatex.exe -synctex=1 -interaction=nonstopmode -file-line-error %filename:_pyr=%
@echo;
call pdflatex.exe -synctex=1 -interaction=nonstopmode -file-line-error %filename:_pyr=%
rem C:/Users/Akira/Documents/bat_test/test_pyrlatex/pdflatex_pyr.bat test_pyr.tex