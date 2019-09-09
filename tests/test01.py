ans=0
print('###PyRInText2019###')
print(177)
print('###PyRInText2019###')

try:
	ans
except:
	ans = 1
if ans==1:
	anscolor='\\color{blue}'
else:
	anscolor='\\color{white}'

# for natural numbers a and b return [g, x, y]
# g is Greatest Common Divisor, x and y is ax+by=g
def gcdExtended(a, b): # This is python comment
    q = a // b
    r = a % b
    if r == 0:
        x1 = 0
        y1 = 1
        return [b, x1, y1]
    else:
        g, x, y = gcdExtended(b, r)
        return [g, y, x - q*y]

print('###PyRInText2019###')
print(559)
print('###PyRInText2019###')
a = 312;b = 534;g,x,y = gcdExtended(a, b)
print('###PyRInText2019###')
print(567)
print('###PyRInText2019###')
print('a=',a,',~b=',b)
print('###PyRInText2019###')
print(590)
print('###PyRInText2019###')
print('g(a,~b)={:d},~x={:d},~y={:d}'.format(g,x,y))
print('###PyRInText2019###')
print(603)
print('###PyRInText2019###')
print('{:d}\\times({:d})+{:d}\\times({:d})={:d}'.format(a, x, b, y, g))
print('###PyRInText2019###')
print(616)
print('###PyRInText2019###')
a = 315;b = 540;g,x,y = gcdExtended(a, b)
print('###PyRInText2019###')
print(624)
print('###PyRInText2019###')
print('a=',a,',~b=',b)
print('###PyRInText2019###')
print(637)
print('###PyRInText2019###')
print(anscolor)
print('###PyRInText2019###')
print(655)
print('###PyRInText2019###')
print('g(a,~b)={:d},~x={:d},~y={:d}'.format(g,x,y))
print('###PyRInText2019###')
print(668)
print('###PyRInText2019###')
print('{:d}\\times({:d})+{:d}\\times({:d})={:d}'.format(a, x, b, y, g))
