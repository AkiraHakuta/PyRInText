@echo off 
set filename=%1
set filename=%filename:.tex=.pdf%
@echo SumatraPDF.exe -reuse-instance %filename:_pyr=%
@echo;
call SumatraPDF.exe -reuse-instance %filename:_pyr=%
rem C:/Users/Akira/Documents/bat_test/test_pyrlatex/sumatrapdf_pyr.bat test_pyr.tex