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

	nullptr ���ֵ�Ŀ����Ϊ�����   NULL  ����ĳ����������˵����ͳ C++ ���   NULL  ��  0   ��Ϊͬһ�ֶ�����
	��ȡ���ڱ�������ζ��� NULL����Щ�������Ὣ NULL ����Ϊ   ((void*)0)  ����Щ���ֱ�ӽ��䶨��Ϊ   0  ��

	C++ ������ֱ�ӽ�   void *   ��ʽת�����������ͣ������   NULL   ������Ϊ   ((void*)0)  ��
	��ô������   char *ch = NULL;   ʱ��  NULL   ֻ�ñ�����Ϊ   0  ��������Ȼ��������⣬
	��������   C++   ���������Իᷢ�����ң�


	C++ 11 ������ nullptr�ؼ��֣�ר���������ֿ�ָ�롢0��
	nullptr  ������Ϊ nullptr_t���ܹ���ʽ��ת��Ϊ�κ�ָ����Աָ������ͣ�
	Ҳ�ܺ����ǽ�����Ȼ��߲��ȵıȽϡ�
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

	foo(NULL);//�����佫��ȥ���� foo(int)
	foo(nullptr);//�����û���Ҫ��
}


/*
	constexpr
	C++ �����Ѿ��߱��˳������ʽ�ĸ������   1+2  ��  3*4   ���ֱ��ʽ���ǻ������ͬ�Ľ������û���κθ����á�
	����������ܹ��ڱ���ʱ�Ͱ���Щ���ʽֱ���Ż���ֲ�뵽��������ʱ���������ӳ�������ܡ�
	
	C++ 11 �ṩ��   constexpr   ���û���ʽ����������������캯���ڱ��������Ϊ������
	����ؼ�����ȷ�ĸ��߱�����Ӧ��ȥ��֤
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
*	�� C++ 14 ��ʼ��  constexptr   �����������ڲ�ʹ�þֲ�������ѭ���ͷ�֧�ȼ���䣬
	�� C++ 11 ���ǲ����Եġ���������Ĵ����� C++ 11 �ı�׼���ǲ��ܹ�ͨ������ģ�
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
	//char arr_3[len + 5];          // �Ƿ�
	const int len_2 = 10;			//�� C++11 ֮ǰ�������ڳ������ʽ��ʹ�õı������뱻����Ϊ   const  ��const  �� ����������˳���
	char arr_4[len_2 + 5];        // �Ϸ�

	//  arr_5   ��˵��C++98 ֮ǰ�ı������޷���֪   len_foo()   �� ������ ʵ�����Ƿ���һ����������Ҳ�͵����˷Ƿ��Ĳ�����
	//char arr_5[len_foo() + 5];  // �Ƿ�  
	char arr_5[len_foo2() + 5];
}

int main01(void)
{
	test();
	system("pause");
	return 0;
}