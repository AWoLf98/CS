#include <iostream>
using namespace std;
#define BITS 8
void print_bits(int);
int division(int, int);
int main(){
	int a = 13;
	int b = 2;
	int div = division(a, b);
	cout << "div = " << div << endl;
	system("PAUSE");
	return 0;
}
void print_bits(int x){
	for (int i = BITS - 1; i >= 0; i--) 
		if ((x >> i) & 0x1) cout<< "1"; //перевіряємо кожен біт на рівність 1
		else cout<< "0";
	cout <<endl;
}
int division(int divident, int divisor){
	cout << "divident = " << divident << "\nIn bits: ";
	print_bits(divident);
	cout << "divisor = " << divisor << "\nIn bits: ";
	print_bits(divisor);
	int n = 0;
	for (int i = 1; i <= BITS; i++)
		if ((divisor << i) & 0x1 << BITS) 
		{
			n = i - 1;
			break;
		}
	divisor <<= n;
	cout << "divisor: ";
	print_bits(divisor);
	while (divisor > divident)
		divisor >>= 1;
	int q = 0;
	cout << "------------------------------" << endl;
	cout << "divident: ";
	print_bits(divident);
	cout << "divisor: ";
	print_bits(divisor);
	while (divident != 0 && divident != divisor)
	{ 
		if (divident < divisor)
		{
			q <<= 1; 
			cout << " divisor більше - 0 наступний біт quotient"<<endl;
		}
		else 
		{ 
			divident -= divisor;
			q = q << 1 | 1; 
			cout << "divisor менше – віднімаємо від divident, 1 наступний біт quotient"<<endl;
		}
		cout << "quot: ";
		print_bits(q);
		cout << "------------------------------" << endl;
		divisor >>= 1;
		cout << "divident: ";
		print_bits(divident);
		cout << "divisor: ";
		print_bits(divisor);
	}
	return q;
}