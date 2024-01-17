i=1
while i<10:
    print(i)
    i+=1
    # #!/usr/bin/env python
# # -*- coding:utf-8 -*-
# # Author:X311
#
# #print(*objects, sep=' ', end='\n', file=sys.stdout)
# #print(eval(input('Enter a number: '))**2)
#
# # & | ^ ~ << >>
# print(round(2.35,1))
# print("七章一章没看"[2:])
# a,b,c,d,e,f='winter'
# print(a,b,c,d,e,f)
# a=52.1
# b=52
# if a>b:max1=a
# print(max1,type(max1))
# flag='def'
# result='abc'if flag else 'def'
# print(result)
#
# score='A'
# match score:
#     case 'A':
#         print('excellent')
#     case _:
#         pass
#
# for i in 'winter':
#     print(i,end='')
#
# sum1=0
# for i in range(1,11): #前闭后开
#     sum1+=i
# print(sum1)
#
# s='Hello'
# s1=s[::-2]
# print(s1*3)
#
# print('e' in s)
# print('e' not in s)
# print(len(s),end='')
# print(s.count('l'),end='')
# print(s.index('l'))
# print(min(s))
#
# lst=[1,'hello','world']
# print(lst)
# lst2=list('HELLOWORLD')
# print(lst2)
# lst3=(list(range(1,11,3)))
# print(lst3)
# print(lst+lst2+lst3)
# print(max(lst3))
# lst4=[10,20,30]
# del lst4
#
# #使用遍历循环for遍历列表元素
# for item in lst:
#     print(item,end='')
# #使用for循环，range（）函数，len（）函数，根据索引进行遍历
# for i in range(0,len(lst)):
#     print(lst[i],end='')
# print('\n')
# #使用enumearte函数进行遍历
# for index,item in enumerate(lst):
#     print(index,item) #index是序号，不是索引
# #手动修改序号索引值
# for index,item in enumerate(lst,start=1):
#     print(index,item)
# for index, item in enumerate(lst,1):
#         print(index, item)
#
# print('原列表:',lst,id(lst))
# lst.append('abc')
# print('增加元素之后:',lst,id(lst)) #元素可变但内存地址不变，所以列表是可变数据类型
# lst.insert(1,100)
# print(lst)
# lst.remove(100)
# print('移除元素后：',lst)
# print(lst.pop(1))
# print(lst)
# # lst.clear()
# # print(lst)
# lst.reverse()
# print('反转后：',lst)
# new_lst=lst.copy()
# print('复制后的新列表：',new_lst)
# lst[1]='my'
# print('改变元素后：',lst)
# lst=[3,53,78,4,98,11,9]
#
# lst.sort()
# print('升序',lst)
# lst.sort(reverse=True)
# print('降序',lst)
# #忽略大小写进行比较
# #lst.sort(key=str.lower)  #注意str.lower后不加括号（是参数）
# sorted_lst=sorted(lst)
#
# #列表生成式
# import random
# lst=[item**2 for item in range(1,11) if item % 2==0]
# print(lst)
# lst=[random.randint(1,100) for _ in range(10)]
# print('随机数',lst)
#
# #遍历二维数组
# # for row in lst:
# #     for item in row:
# #         print(item,end='\t')
# #     print()
#
# #列表生成式生成一个4行5列的二维列表
# lst2=[[j for j in range(5)]for i in range(4)]
# print(lst2)
#
# #使用小括号创建元组
# t=(1,2,'python','[1,3,t]')
# print(t)
# #使用内置函数tuple（）创建元组
# t=tuple('helloworld')
# print(t)
# t=tuple([10,20,30])
# print(t)
# #若元组中只有一个元素，逗号不能省
# t=(10)
# print(type(t))
# t=(10,)
# print(type(t))
# del t
#
# #元组生成式结果为生成器对象，需要转换成元组或列表才能看到内容
# t=(i for i in range(1,4))
# print(i)
# t=tuple(t)
# print(t)
# #取出生成器中的元素
# t=(i for i in range(1,4))
# print(t.__next__())
# print(t.__next__())
# print(t.__next__())
# t=tuple(t)
# print(t)
#
# #字典类型的创建方式 key需为不可变数据类型
# d={10:'a',15:'b',20:'a'}
# print(d)#key值相同时，value进行覆盖
#
# lst1=[1,2,3,4]
# lst2=['a','b','c']
# x=zip(lst1,lst2)
# x=dict(x)
# print(x)
#
# d=dict(a=1,b=2)
# print(d)
# #字典元素的访问
# d={10:'a',15:'b',20:'a'}
# print(d[15])
# print(d.get('y'))
# print(d.get('y','不存在'))
# #字典元素的遍历
# for item in d.items():
#     print(item,end='\t')
# for key,value in d.items():
#     print(key,value,end='\t')
# #向字典中添加元素
# d[50]=1
# #获取字典中所有的Key
# keys=d.keys()
# print()
# print(1111111111,keys,list(keys),tuple(keys))
# #获取字典中所有的value
# values=d.values()
# print(1111111111,values,list(values),tuple(values))
# #将字典中的数据转成key-value的形式，以元组的方式展现
# lst=list(d.items())
# print(lst)#可来回映射
# #使用pop函数
# print(d.pop(20,'不存在'))
# print(d,)
# #随机删除
# print(d.popitem())
# print(d)
# #清空字典中所有元素
# # d.clear()
# # print(d)
#
# #字典生成式
# import random
# d={item:random.randint(1,100) for item in range(4)}
# print(d)
# d={key:value for key, value in zip(lst1,lst2)}
# print(d)
#
# #集合的创建方式  集合存储不可变数据类型
# s={10,20,30,40}
# s=set('hello')
# print(s)#无序且不重复
# s=set([10,20,50])
# s=set(range(1,10))
# s=set() #创建了一个空集合
# s={} #数据类型为字典
#
# #交集操作 &
# #并集操作 |
# #差集操作 -
# #补集操作 ^
#
# #集合操作
# s={10,20,30,40}
# s.add(100)
# s.remove(20)
# #s.clear()
#
# #字典合并
# d1={'a':100,'b':200}
# d2={'c':30,'d':2}
# d3=d1|d2
# print(d3)
#
# fruit=['apple','banana']
# count={10,5}
# for a,b in zip(fruit,count):
#     match a,b:
#         case 'apple',10:
#             pass
#
# #字符串的分割
# email='xln311@163.com'
# lst=email.split('@')
# print('邮箱名：',lst[0],'服务器域名：',lst[1])
#
# #find找不到返回-1，index找不到报错
#
# print(email.startswith('xln'))
# email.replace('x','谢',1)
# print(email.center(20,'*'))
#
# #去掉字符串左右的空格
# # email.strip()
# # email.lstrip()
# # email.rstrip()
# #去掉指定的字符
# print('去掉指定的字符：',email.strip('xln'))
#
# #格式化字符串
# name='谢一'
# age=1
# print('姓名：%s,年龄：%d' % (name,age))
# print(f'{name},{age}')
# print('{1},{0}'.format(name,age))
#
# s1='a'
# s2='b'
# # s3='*'.join([s1,s2])
#
# try:
#     gender=input('Enter your gender:')
#     if gender!='男'and gender!='女':
#         raise Exception('Invalid gender')
#     else:
#         print('gender')
# except Exception as e:
#     print(e)
class Student:
    #类属性：定义在类中，方法外的变量
    school='8z'
    def __init__(self,xm,age):
        self.xm = xm
        self.age = age

    def show(self):
        print(f'xm: {self.xm}, age: {self.age}')