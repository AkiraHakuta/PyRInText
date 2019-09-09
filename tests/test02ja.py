print('###PyRInText2019###')
print(110)
print('###PyRInText2019###')

import io,sys 
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')
num = 10
str = '日本語.jp~'
print(str + 'を', num, '回表示します。\\par \\vspace{1mm}')
for i in range(num):
	print(str)

