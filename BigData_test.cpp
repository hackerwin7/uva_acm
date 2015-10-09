#include"BigData.h"
#include <stdlib.h>
int main()
{
	BigData d1 = BigData("123456");
	BigData d2 = BigData("334455");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("23066");
	d2 = BigData("-978");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("0");
	d2 = BigData("0");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("-172");
	d2 = BigData("-999");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("23897");
	d2 = BigData("-3467856");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("-3467856");
	d2 = BigData("23897");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("-3467856");
	d2 = BigData("3467856");
	cout << d1 << "+" << d2 << "=" << d1 + d2 << endl;
	d1 = BigData("-3467856");
	d2 = BigData("-3467856");
	cout << d1 << "-" << d2 << "=" << d1 - d2 << endl;
	d1 = BigData("-123");
	d2 = BigData("-321");
	cout << d1 << "*" << d2 << "=" << d1 * d2 << endl;
	d1 = BigData("39483");
	d2 = BigData("-321");
	cout << d1 << "/" << d2 << "=" << d1 / d2 << endl;
	d1 = BigData("39683");
	d2 = BigData("-321");
	cout << d1 << "%" << d2 << "=" << d1 % d2 << endl;
	d1 = BigData("123123342134123432");
	d2 = BigData("-2342432");
	cout << d1 << "/" << d2 << "=" << d1 / d2 << endl;
	cout << d1 << "%" << d2 << "=" << d1 % d2 << endl;
	d1 = BigData("-52562184146");
	d2 = BigData("-2342432");
	cout << d1 << "*" << d2 << "=" << d1 * d2 << endl;
	/*int a = 2, b = 3, c = 5;
	if (a * b < c) printf("true");//why this priority is right but my overload * and < 's priority is wrong, I know that , the parameter must be quote type
	else printf("false");*/
	system("pause");
	return(0);
}