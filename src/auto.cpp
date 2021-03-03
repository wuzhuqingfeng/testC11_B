#include <iostream>
using namespace std;

#include <iostream>
#include <vector>
#include <list>
/*
C++ 11 ������ `auto` �� `decltype` �������ؼ���ʵ���������Ƶ�
 `auto` �������ں������Σ����������������޷�ͨ������ģ��������ص����⣬����Ӧ��ʹ��ģ�壩
 `auto` �����������Ƶ���������
*/
int test()
{
    //��ͨ������, һ�����룬����������
    int ary[5] = { 1, 2, 3, 4, 5 };
    //auto muAry = arr;//error

	int* pAry = new int[5];
	for (int i = 0; i < sizeof(ary); i++) {
		std::cout << ary[i] << std::endl;
	}

    //����---��̬���� ����ָ�����С����������鵱ǰ��ʹ��������ж�̬������
    //ģ������
    std::vector<int> v;

    //��������
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    //for (int i = 0; i < v.size(); i++){
    //    std::cout << v[i] << std::endl;
    //}

    //ʹ�õ������ķ�ʽ��������
    std::vector<int>::iterator it; //��������ģ�����е��ڲ���
    for (it = v.begin(); it != v.end(); it++) {
        std::cout << *it << std::endl; //* it ������ģ����ľ����ֵ
    }

    //ͳһ�ı�����ʽ ����
    std::list<std::string> l;
    l.push_back("hello1");
    l.push_back("hello2");
    l.push_back("hello3");

    //for (std::list<std::string>::iterator it2 = l.begin(); it2 != l.end(); it2++) {
    //    std::cout << (*it2).c_str() << std::endl; //* it ������ģ����ľ����ֵ
    //}

    //auto �����Ƶ��ؼ���
    for (auto it2 = l.begin(); it2 != l.end(); it2++) {
        std::cout << (*it2).c_str() << std::endl; //* it ������ģ����ľ����ֵ
    }


    //for(std::string str : l){
    //    std::cout << str.c_str() << std::endl;
    //}

    for (auto str : l) {
        std::cout << str.c_str() << std::endl;
    }

	auto i = 5;             // i ���Ƶ�Ϊ int
    auto arr = new int(10); // arr ���Ƶ�Ϊ int *

    return 0;
}


int main(void)
{
	test();
	system("pause");
	return 0;
}