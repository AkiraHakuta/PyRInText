## PyRInText  

PyRInText is a tool that runs Python and R code embedded in text file,   
and makes the new text file that is replaced with its output.

### Building PyRInText (Windows only)   
<ol>
<li>

Install [mingw-w64](https://mingw-w64.org/doku.php)  
Set path C:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin   
</li>
<li>

Install [cmake](https://cmake.org)  
cmake-3.15.2-win64-x64.msi  
Set path C:\CMake\bin  
</li>
<li>

Download [antlr4-4.7.2.zip](https://github.com/antlr/antlr4)  
ANTLR (ANother Tool for Language Recognition) is a powerful parser generator  
</li>
<li>

Making antlr4 C++ static library `libantlr4-runtime.a`  
Open `Dos Command Prompt`  
$ unzip antlr4-4.7.2.zip  
$ cd .../antlr4-4.7.2/runtime/Cpp  
$ mkdir build  
$ cd build  
$ cmake -G "MinGW Makefiles" ..  
$ mingw32-make.exe  
$ mingw32-make.exe install  
If the following error message shows 

```
Install the project...   
-- Install configuration: "Release"  
CMake Error at cmake_install.cmake:36 (file):  
file cannot create directory: C:/Program Files  
``` 

You change `cmake_install.cmake` as follows  
old : set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/LIBANTLR4")  
new : set(CMAKE_INSTALL_PREFIX "C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/usr/local") 

Copy the `cmake` folder to the `..mingw64/usr/local`  folder 
</li>
<li>

Download [java](https://www.java.com/en/)   
Download antlr-4.7.2-complete.jar ([Complete ANTLR 4.7.2 Java binaries jar](http://www.antlr.org/download.html))  
Make C:\Javalib and 
save antlr-4.7.2-complete.jar in C:/Javalib. 
</li>
<li>

Copied [cmdline.h](https://github.com/tanakh/cmdline)  
About  
This is a simple command line parser for C++.  
- Easy to use  
- Only one header file  
- Automatic type check  
</li>
<li>

Compiling pyrintext.cpp  
Open `Dos Command Prompt`  
$ cd ..../PyRInText  
$ mkdir build  
$ cd build   
$ cmake -G "MinGW Makefiles" ..  
$ mingw32-make.exe   

This compiled binary file is in **release**.  
Unzip [PyRInText-1.0-win64.zip](https://github.com/AkiraHakuta/PyRInText/releases/tag/v1.0).
</li>
</ol>

### Usage  
<ol>
<li>

Install [Python3](https://www.python.org/downloads/)  
Add Python 3.7 to PATH check  
</li>
<li>

Install [R](https://www.r-project.org)  
e.g. install folder C:\R-3.6.1  
Write the full path of Rscript.exe to `pyrintext.ini`   
Install package knitr for  tests/test01_pyr.tex  
</li>
<li>
	
Install [TeX Live](http://www.tug.org/texlive/acquire-netinstall.html)  
</li>
<li>

Install [Sumatra PDF](https://www.sumatrapdfreader.org/free-pdf-reader.html)  
</li>
<li>

pyrintext.exe command line options
```
usage: pyrintext.exe filename [options] 
options:
  -p, --pycd       insert code in the top of Python (e.g. -p ans=1)
  -r, --rcd        insert code in the top of R (e.g. -r "b<-0")
  -h, --help       print usage and exit
  -v, --version    print version and exit
filename (add the suffix "_pyr"  e.g. test_pyr.tex)
e.g. $ C:/.../pyrintext.exe test_pyr.tex -p ans=0 -r "value<-23"
```  
</li>
<li>

Tests    
Open `Dos Command Prompt`  
```
$ cd C:/.../tests
$ C:/.../pyrintext.exe test01_pyr.tex

This is pyrintext 1.0
Output written on test01.py
python.exe -u  test01.py
Output written on test01.r
C:/R-3.6.1/bin/x64/Rscript.exe --encoding=utf-8 ../test01.r
Output written on test01.tex
```
or
```
$ C:/.../pyrintext.exe test01_pyr.tex -p ans=0
```
Compile `test01.tex` with pdflatex  
</li>
<li>

PyRInText commands    
**Python**  
```
\begin{pycode}
a = 312
b = 534
\end{pycode}
```  
`\pyc{a = 312;b = 534;\pyc}`&nbsp; execute the same Python code.  
&nbsp;  
`\pyp{'a=',a,',b=',b\pyp}` replaces it with 'a=312,b=534'.  

`\pyc{print('a=',a,',b=',b)\pyc}` is the same.  

**R**   
```
\begin{Rcode}
a <- 312
b <- 534
\end{Rcode}
```  
`\Rc{a <- 312;b <- 534;\Rc}`&nbsp; execute the same R code.  
&nbsp;  
`\Rcat{"a=",a,",b=",b\Rcat}` replaces it with 'a=312,b=534'.  

`\Rc{cat("a=",a,",b=",b)\Rc}` is the same.  
</li>
<li>

Batch Files
```
$ C:/.. /etc/pdflatex_pyr.bat test01_pyr.tex

pdflatex.exe -synctex=1 -interaction=nonstopmode -file-line-error test01.tex
....
```
```
$ C:/.. /etc/sumatrapdf_pyr.bat test01_pyr.tex

SumatraPDF.exe -reuse-instance test01.pdf
```
</li>
</ol>

### Change log  

##### version 1.0 (2019/09/09)&nbsp;  Initial version  

##### version 1.1 (2019/09/15)&nbsp;
- modified `PyRInText.g4` for speedup   

&nbsp;  

*******  
####  in Japanese   
<ol>
<li>

PyRInText は Python と R の code が埋め込まれた text file から code を抜き取って実行、  
さらにその code を Python と R の出力で置き換えるツールです。  
出力がない code は、空文字に置き換わります。 tex のマクロではありません。  
[pythontex](https://github.com/gpoore/pythontex) の簡易版として作成しました。(Windows only)      
</li>
<li>

tests/test02ja_pyr.tex は日本語の使用例 (Python のみ) です。  
```py  
import io,sys  
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
```  
を挿入すると、「日本語の文字化け」を防ぐことができます。 
</li>

</ol>

