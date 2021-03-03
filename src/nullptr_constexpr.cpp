#include <iostream>
using namespace std;

/*

#ifndef NULL
	#ifdef __cplusplus
		#define NULL 0
	#else
		#define NULL ((void *)0)
	#endif
#endif

	nullptr 出现的目的是为了替代   NULL  。在某种意义上来说，传统 C++ 会把   NULL  、  0   视为同一种东西，
	这取决于编译器如何定义 NULL，有些编译器会将 NULL 定义为   ((void*)0)  ，有些则会直接将其定义为   0  。

	C++ 不允许直接将   void *   隐式转换到其他类型，但如果   NULL   被定义为   ((void*)0)  ，
	那么当编译   char *ch = NULL;   时，  NULL   只好被定义为   0  。而这依然会产生问题，
	将导致了   C++   中重载特性会发生混乱，


	C++ 11 引入了 nullptr关键字，专门用来区分空指针、0。
	nullptr  的类型为 nullptr_t，能够隐式的转换为任何指针或成员指针的类型，
	也能和他们进行相等或者不等的比较。
*/


void foo(char* ch) {
	std::cout << "call foo(char*)" << std::endl;
}

void foo(int i) {
	std::cout << "call foo(int)" << std::endl;
}

void test()
{
	if (NULL == (void*)0) {
		std::cout << "NULL == 0" << std::endl;
	}
	else {
		std::cout << "NULL != 0" << std::endl;
	}

	foo(NULL);//这个语句将会去调用 foo(int)
	foo(nullptr);//符合用户的要求
}


/*
	constexpr
	C++ 本身已经具备了常数表达式的概念，比如   1+2  、  3*4   这种表达式总是会产生相同的结果并且没有任何副作用。
	如果编译器能够在编译时就把这些表达式直接优化并植入到程序运行时，将能增加程序的性能。
	
	C++ 11 提供了   constexpr   让用户显式的声明函数或对象构造函数在编译器会成为常数，
	这个关键字明确的告诉编译器应该去验证
*/

#define LEN 10

int len_foo()
{
	return 5;
}

constexpr int len_foo2()
{
	return 5;
}

constexpr int fibonacci(const int n) 
{
	return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

/*
*	从 C++ 14 开始，  constexptr   函数可以在内部使用局部变量、循环和分支等简单语句，
	但 C++ 11 中是不可以的。例如下面的代码在 C++ 11 的标准下是不能够通过编译的：
*/
constexpr int fibonacci2(const int n)
{
	if (n == 1) return 1;
	if (n == 2) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

void test02()
{
	char arr_1[10];
	char arr_2[LEN];
	int len = 5;
	//char arr_3[len + 5];          // 非法
	const int len_2 = 10;			//在 C++11 之前，可以在常量表达式中使用的变量必须被声明为   const  ，const  将 变量定义成了常量
	char arr_4[len_2 + 5];        // 合法

	//  arr_5   来说，C++98 之前的编译器无法得知   len_foo()   在 运行期 实际上是返回一个常数，这也就导致了非法的产生。
	//char arr_5[len_foo() + 5];  // 非法  
	char arr_5[len_foo2() + 5];
}

int main01(void)
{
	test();
	system("pause");
	return 0;
}