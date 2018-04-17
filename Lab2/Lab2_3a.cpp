#include <iostream>
#include <bitset>
#include <cmath>
#define REGISTER 32
#define EXP 8
#define MANTISSA 23
#define SIGN 31 //знак
using namespace std;
void check_numbers(float*, float*); //перевіряємо числа у випадку якщо f1<f2 переставляємо місцями
float add_floats(float, float);

int main()
{
	float f1 = 9.75;
	float f2 = 0.5625;
	float f3 = add_floats(f1, f2);
	bitset<REGISTER> b_fpn3 = bitset<REGISTER>(*(long unsigned int*)(&f3));
	cout << "f3 = " << f3 << endl << b_fpn3 << endl;
	system("PAUSE");
	return 0;
}
void check_numbers(float* f1, float* f2){
	if (abs(*f1) < abs(*f2))
	{ 
		double temp;
		temp = *f1;
		*f1 = *f2;
		*f2 = temp;
	}
}
float add_floats(float f1, float f2){
	check_numbers(&f1, &f2);
	bitset<REGISTER> b_fpn1 = bitset<REGISTER>(*(long unsigned int*)(&f1));
	bitset<REGISTER> b_fpn2 = bitset<REGISTER>(*(long unsigned int*)(&f2));

	cout << f1 << ":" << b_fpn1 << endl;
	cout << f2 << ":" << b_fpn2 << endl;

	int sign1 = b_fpn1[SIGN], sign2 = b_fpn2[SIGN], sign3;//sign3 - знак відповіді
	bitset<EXP> exp1, exp2, exp3; //порядок
	bitset<MANTISSA> mant1, mant2, mant3;

	for (int i = 0; i < EXP; i++){
		exp1[i] = b_fpn1[i + MANTISSA];
		exp2[i] = b_fpn2[i + MANTISSA];
	}
	for (int i = 0; i < MANTISSA; i++){
		mant1[i] = b_fpn1[i];
		mant2[i] = b_fpn2[i];
	}
	
	cout << "FPN-1\nSIGN: " << sign1 << "\nEXPONENT: " << exp1.to_ullong() << "\nBITS:" << exp1 << "\nMANTISSA: " << mant1.to_ullong() << "\nBITS:" << mant1 << endl;
	cout <<"------------------------------------------------------------------"<<endl;
	cout << "FPN-2\nSIGN: " << sign2 << "\nEXPONENT: " << exp2.to_ullong() << "\nBITS:" << exp2 << "\nMANTISSA: " << mant2.to_ullong() << "\nBITS:" << mant2 << endl;
	cout <<"------------------------------------------------------------------"<<endl;
	/*f1 та f2 можуть бути додані лише якщо експоненти однакові, тобто exp1 = exp2. 
	Початкове значення експоненти має бути більшим одного з двох чисел, оскільки ми знаємо,
	що експонента рівня f1 буде більшиою, отже вихідний результат експоненти exp3 = exp1. */
	exp3 = exp1;
	int exp_diff;
	cout <<"Обчислюємо різницю експонент. (exp_diff = (exp1-exp2))"<<endl;
	exp_diff = exp1.to_ullong() - exp2.to_ullong();
	cout << "exp_diff: " << exp_diff << endl;
	exp2 = exp1;
	mant2 >>= 1;
	mant2[MANTISSA - 1] = 1;
	mant2 >>= exp_diff;
	mant1 >>= 1;
	mant1[MANTISSA - 1] = 1;
	cout << "Виконуємо вирівнювання порядків і корекцію відповідної мантиси. \n При вирівнюванні порядків вміст розрядів мантиси числа з меншим порядком треба зсунути вправо на різницю порядків.\n При цьому виштовхувані молодші розряди мантиси числа з меншим порядком зникають, в її старші розряди вписуються нулі \n а порядок даного числа збільшується на отриману різницю порядків" << endl;
	cout << "MANTISSA-1:" << mant1 << endl;
	cout << "MANTISSA-2:" << mant2 << endl;
	cout <<"Обчислюємо суму / різницю мантиси залежно від знака біт SIGN1 та SIGN2"<<endl;
	if (sign1 == sign2)
	{
		mant3 = mant1.to_ullong() + mant2.to_ullong();
		cout << "Знаки f1 та f2 рівні (sign1 == sign2), додаємо мантиси."<<endl;
	}
	else
	{
		mant3 = mant1.to_ullong() - mant2.to_ullong();
		cout << "Знаки f1 та f2 не є рівними (f1! = F2), віднімаємо мантиси."<<endl;
	}
	cout << "MANTISSA-3:" << mant3 << endl;
	int e = 127 - exp3.to_ullong();
	e = abs(e);
	bitset<MANTISSA> integer;
	integer = mant3 >> MANTISSA - e - 1;
	bitset<MANTISSA> fraction;
	fraction = mant3 << e + 1;
	double frac = 0;
	for (int i = MANTISSA - 1; i >= 0; i--)
		if (fraction[i] * 0x1)  //рахуємо ціле число
			frac += pow(2, (i - MANTISSA));
		cout << "\nFPN-3_MANSTISSA\nINTEGER:" << integer.to_ullong() << endl << integer << endl;
		cout << "FRACTION:" << frac << endl << fraction << endl << endl;
	return integer.to_ullong() + frac;
}
