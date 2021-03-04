#include <iostream>
using namespace std;

/*
	Const好处
	//合理的利用const，
	1指针做函数参数，可以有效的提高代码可读性，减少bug；
	2清楚的分清参数的输入和输出特性

结论：
	C语言中的const变量
		C语言中const变量是只读变量，有自己的存储空间

	C++中的const常量
		可能分配存储空间,也可能不分配存储空间
		当const常量为全局，并且需要在其它文件中使用，会分配存储空间
		当使用&操作符，取const常量的地址时，会分配存储空间
		当const int &a = 10; const修饰引用时，也会分配存储空间

*/
#if 0
void test()
{
	{
		const int a = 10;
		int const b = 10;//第一个第二个意思一样 代表一个常整形数

		const int* c = &a;//第三个 c是一个指向常整形数的指针(所指向的内存数据不能被修改，但是本身可以修改)
		//*c = 100;//err
		int arr[10] = { 1,2 };
		int* const d = arr;//第四个 d 常指针（指针变量不能被修改，但是它所指向内存空间可以被修改）

		//const int* const e; //第五个 e一个指向常整形的常指针（指针和它所指向的内存空间，均不能被修改）
	}

	/*
	* C中“冒牌货”
	*
	C++编译器对const常量的处理
	当碰见常量声明时，在符号表中放入常量 =?问题：那有如何解释取地址
	编译过程中若发现使用常量则直接以符号表中的值替换
	编译过程中若发现对const使用了extern或者&操作符，则给对应的常量分配存储空间（兼容C）

	*/
	{
		//int& c = 1;// 字面量 1 没有地址，没有地址何来引用 error C2440: 'initializing': cannot convert from 'int' to 'int &'

		const int a = 10;
		int* p = (int*)&a;
		printf("a = %d\n", a);//a =10
		*p = 11;
		printf("a = %d\n", a);//a = 10 C++编译器虽然可能为const常量分配空间，但不会使用其存储空间中的值。直接使用常量表中的值
		const int& b = a;	//引用,取到了a的地址，*a 内存中的值已经改变了
		std::cout << "b = " << b << std::endl;//b = 11


		const int& d = 100;//ok
		std::cout << "d = " << d << std::endl;//d = 100
		printf("Hello......\n");
	}
}

#endif

/*
* 对比加深
	C++中的const常量类似于宏定义
	const int c = 5; ≈ #define c 5
	C++中的const常量与宏定义不同
	const常量是由编译器处理的，提供类型检查和作用域检查
	宏定义由预处理器处理，单纯的文本替换
*/

//在func1定义a，在func2中能使用
//在func1中定义的b，在func2中不能
#if 0
void fun1()
{
#define a 10
	//#undef a
	const int b = 20;
}

void fun2()
{
	printf("a = %d\n", a);
	//printf("b = %d\n", b);
}

void test()
{
	fun1();
	fun2();
}
#endif

/*
	引用是一个有地址，引用是常量

	引用的本质
	1）引用在C++中的内部实现是一个常指针
	Type& name  <=> Type* const name
	2）C++编译器在编译过程中使用常指针作为引用的内部实现，因此引用所占用的空间大小与指针相同。
	3）从使用的角度，引用会让人误会其只是一个别名，没有自己的存储空间。这是C++为了实用性而做出的细节隐藏

	4）	请仔细对比间接赋值成立的三个条件
	1定义两个变量 （一个实参一个形参）
	2建立关联 实参取地址传给形参
	3*p形参去间接的修改实参的值

	引用结论
	1）引用在实现上，只不过是把：间接赋值成立的三个条件的后两步和二为一
	//当实参传给形参引用的时候，只不过是c++编译器帮我们程序员手工取了一个实参地址，传给了形参引用（常量指针）
	2）当我们使用引用语法的时，我们不去关心编译器引用是怎么做的
	当我们分析奇怪的语法现象的时，我们才去考虑c++编译器是怎么做的

*/
#if 0
struct Teacer {
	int& a; //等价于 int*const a;
	int& b;
};

void func(int& a)
{
	a = 5;
}

void func(int*const a)
{
	*a = 5;
}

void test()
{
	int a = 10;
	int& b = a;
	b = 11;

	cout << "b--->" << a << endl;
	printf("a:%d\n", a);
	printf("b:%d\n", b);
	printf("&a:%d\n", &a);
	printf("&b:%d\n", &b);  //请思考：对同一内存空间可以取好几个名字

	printf("sizeof(Teacher) %d\n", sizeof(Teacer));//sizeof(Teacher) 8
}
#endif

/*
	强制类型转换是有一定风险的，有的转换并不一定安全，如把整型数值转换成指针，
	把基类指针转换成派生类指针，把一种函数指针转换成另一种函数指针，
	把常量指针转换成非常量指针等。

	强制转换运算符

	C++ 引入了四种功能不同的强制类型转换运算符以进行强制类型转换：
	- const_cast
	- static_cast
	- reinterpret_cast
	- dynamic_cast

	C语言强制类型转换缺点：

	主要是为了克服C语言强制类型转换的以下三个缺点。

	- 没有从形式上体现转换功能和风险的不同。
		  例如，将 int 强制转换成 double 是没有风险的，而将常量指针转换成非常量指针，
		  将基类指针转换成派生类指针都是高风险的，而且后两者带来的风险不同（即可能引发
		  不同种类的错误），C语言的强制类型转换形式对这些不同并不加以区分。

	- 将多态基类指针转换成派生类指针时不检查安全性，即无法判断转换后的指针是否确实指向一个派生类对象。

	- 难以在程序中寻找到底什么地方进行了强制类型转换。

	  强制类型转换是引发程序运行时错误的一个原因，因此在程序出错时，可能就会想到是不是有哪些强制类型转换出了问题。
*/

/*
	const_cast
	仅用于进行去除 const 属性的转换，它也是四个强制类型转换运算符中唯一能够去除 const 属性的运算符。

	常量对象或者是基本数据类型不允许转化为非常量对象，只能通过指针和引用来修改
*/
#if 0
void test()
{
	const int n = 5;
	const std::string s = "hello";

	//std::string t = const_cast<std::string>(s);
	//int k = const_cast<int>(n);//error C2440: 'const_cast': cannot convert from 'const int' to 'int'

	std::string& t = const_cast<std::string&>(s);//转换成引用
	t = "123456";
	std::cout << "s = " << s << " t = " << t << std::endl;//s = 123456 t = 123456

	int* k = const_cast<int*>(&n);//转换成指针
	*k = 10;
	std::cout << "n = " << n << " *k = " << *k << std::endl;//n = 5 *k = 10 n为什么还是等于5 ？ n的值 是从常量表中拿到的
}
#endif

/*
	const_cast
	常成员函数中去除this指针的const属性
*/
#if 1
class CTest
{
public:
	
	CTest() :m_i(2) { std::cout << m_i << std::endl; }
public:

	/*
		const用于函数的末尾
		这是对于类而言的
		常成员函数，不改变对象的成员变量，也不调用类中任何非const成员函数

		在const成员函数中,this的类型是一个指向const类类型对象的 const指针,
		既不能改变this所指向的对象,也不能改变this所保存的地址
	*/
	void foo(int n) const// const 修饰的是this  <==> void foo(const CTest * pThis)
	{
		{
			//m_i = n;//error C3490: 'm_i' cannot be modified because it is being accessed through a const object
		}

		{	
			const_cast<CTest*>(this)->m_i = n;//将const CTest * pThis  指针所指向的内容不能改变
			std::cout << "m_i = " << m_i << std::endl;
		}
		
		{
			//myPrint();//error C2662: 'void CTest::myPrint(void)': cannot convert 'this' pointer from 'const CTest' to 'CTest &'
			//this->myP
			//myPrint()的函数原型为                   <==>  void myPrint(CTest* pThis) 
			//在const成员函数中 this指针是  const CTest* pThis    而 普通的非const 成员函数myPrint 是 void myPrint(CTest* pThis)
			//存在类型不匹配的情况 const CTest* pThis --> CTest* pThis   编译器 from 'const CTest' to 'CTest &'
			const_cast<CTest*>(this)->myPrint();
		}
	}

	/*
		在普通的非const 成员函数中，this的类型是一个指向类类型的const指针,
		等价于 this  <==>  CTest *
		可以改变this所指向的值,但不能改变this所保存的地址
	*/
	void myPrint() //<==>     void foo(const CTest* pThis) -->   void myPrint(CTest* pThis)  
	{
		std::cout << "myPrint(）m_i = " << m_i << std::endl;
	}
	int m_i;
};

void test()
{
	CTest obj;
	obj.foo(10);
}
#endif

/*
	static_cast
	基本等价于隐式转换的一种类型转换运算符，可使用于需要明确隐式转换的地方。
	
	可以用于低风险的转换。
		- 整型和浮点型
		- 字符与整形
		- 转换运算符
		-空指针转换为任何目标类型的指针

	不可以用与风险较高的转换
		- 不同类型的指针之间互相转换
		- 整型和指针之间的互相转换
		- 不同类型的引用之间的转换
*/
#if 0
class CInt
{
public:
	CInt(int i):m_n(i)
	{
	}
	//转换函数c++ plus 416页
	/*
	 将类转换为 typeName 类型，定义
	 operator typeName()
	 1 转换函数必须是类方法
	 2 转换函数不能指定返回类型
	 3 转换函数不能有参数

	 typeName 指出了要转换成的类型,因此不需要指定返回类型，
	 转换函数是类方法，即需要通过类对象来调用,从而告知函数要转换的值，
	 因此函数不需要参数
	*/
	operator int()
	{
		m_n = 32.123;
		std::cout << m_n << std::endl;
		return m_n;
	}

public:
	int m_n;
};

void test()
{
	int n = 5;
	double dbl = n;
	char ch = 'a';

	//c11 整型浮点型 显示的隐士转换
	dbl = static_cast<double>(n);

	//整型与字符型
	ch = static_cast<char>(n);

	//转换运算符

	CInt nObj(1);
	int i = int(nObj);
	int j = nObj;     //作用一样  编译器发现 左侧 是int 类型 右侧 是 CInt 类型,因此编译器查看类中是否有转换函数 

	int k = static_cast<int>(nObj);
	std::cout << k << std::endl;

}
#endif
/*
	static_cast用于基类与派生类的转换过程中，但是没有运行时类型检查。
*/
#if 0
class CFather
{
public:
	CFather() 
	{
		m_nTest = 3;
	}

	virtual void foo()
	{
		std::cout << "CFather()::void foo()" << std::endl;
	}

	int m_nTest;
};

class CSon : public CFather
{
public:
	CSon()
	{
		m_son = 66;
	}

	virtual void foo() override
	{
		std::cout << "CSon::void foo()" << std::endl;
	}
public:
	int m_son;
};
void test()
{
	CFather f;
	CSon s;
	CFather* pFather = &f;
	CSon* pSon = &s;

	pFather = pSon;//子类赋值给父类 
	pFather = static_cast<CFather*>(pSon);//子类转父类 安全 但是没有运行时类型检查。

	//pSon = pFather;//error C2440: '=': cannot convert from 'CFather *' to 'CSon *'
	pSon = static_cast<CSon*>(pFather);//父类转子类 不安全 但是没有运行时类型检查。

}
#endif

/*
	dynamic_cast
	用于具有虚函数的基类与派生类之间的指针或引用的转换。

	-基类必须具备虚函数
		原因：dynamic_cast是  运行时类型检查  ，需要运行时类型信息(RTTI)，而这个信息是存储与类的
		虚函数表  关系紧密，只有一个类定义了虚函数，才会有虚函数表。

	-运行时检查，转型不成功则返回一个空指针
	-非必要不要使用dynamic_cast，有额外的函数开销

	常见的转换方式：
	- 基类指针或引用 转派生类指针（必须使用dynamic_cast）
	- 派生类指针或引用 转基类指针（可以使用dynamic_cast,但是更推荐使用static_cast）
*/
#if 0
class CFather
{
public:
	CFather()
	{
		m_nTest = 3;
	}

	virtual void foo()
	{
		std::cout << "CFather()::void foo()" << std::endl;
	}

	int m_nTest;
};

class CSon : public CFather
{
public:
	CSon()
	{
		m_son = 66;
	}

	virtual void foo() override
	{
		std::cout << "CSon::void foo()" << std::endl;
	}
public:
	int m_son;
};
void test()
{
	CFather f;
	CSon s;
	CFather* pFather = &f;
	CSon* pSon = &s;

	//父类转子类（不安全）
	//pSon = pFather;
	pSon = dynamic_cast<CSon*>(pFather); //运行时的检测,返回空
	//pSon->foo(); //运行时，pSon为NULL 程序崩溃

	//pFather = static_cast<CFather* >(&s); //子类转父类，安全 建议使用
	pFather = dynamic_cast<CFather*>(&s); //子类转父类也可以通过dynamic_cast，但不是必须的 有内存开销
	
	//验证 子类转父类 static_cast 或者 dynamic_cast都是可以的，
	pSon = dynamic_cast<CSon*>(pFather); //运行时的检测,可以通过类型检测
	pSon->foo();

}
#endif

/*
	reinterpret_cast
	用于进行各种不同类型的转换
		-不同类型指针之间
		-不同类型引用之间
		-指针和能容纳指针的整数类型之间的转换
	编译期处理,执行的是逐字节复制的操作
	类似于显式强转，后果自负
*/
#if 0
void foo() 
{
	cout << "foo()" << endl;
}

void test()
{
	int nTemp = 0;

	// 指针转整数
	int nTemp1 = reinterpret_cast<int>(&nTemp);
	cout << hex << nTemp1 << '\n';

	//整数转指针
	int* p1 = reinterpret_cast<int*>(nTemp1);
	cout << *p1 << '\n';

	//将整型转为指针
	unsigned int nTemp2 = 0x00500000;
	int* pTemp = reinterpret_cast<int*>(nTemp2);

	//将一个函数转为一个函数指针并转回
	void(*fp1)() = reinterpret_cast<void(*)()>(foo);	//void(*)()
	int(*fp2)() = reinterpret_cast<int(*)()>(fp1);		//int(*)()

	cout << dec << fp2() << '\n';
}
#endif
int main(void)
{
	test();
	system("pause");
	return 0;
}