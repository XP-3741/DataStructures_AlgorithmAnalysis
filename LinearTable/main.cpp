#include"Array_Description.h"
#include"Abstract_Classes.h"

int main()
{
	// ������������Ϊ 100 �����Ա�
	// linearList *x = (linearList)new arrayList<int>(100);
	arrayList<double> y(100);

	// ����������ȱʡֵ����һ�����Ա�
	arrayList<char> z;

	// �����Ա� y ���ƴ���һ�����Ա�
	arrayList<double> w(y);

	linearList<int>* list[10];
	list[0] = new arrayList<int>(20);
	list[1] = new arrayList<int>();
	/*list[2] = new chain<int>(5);
	list[3] = new chain<int>;*/

	return 0;
}