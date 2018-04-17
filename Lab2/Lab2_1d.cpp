#include <iostream>
#include <cmath>
#define BITS 4
using namespace std;
int multiplication();
void print_bits(int, int);
void shift(int*);
void sub(int*, int);
void add(int*, int);
int m, r;

int main() {
	int result = multiplication();
	cout << result<< endl;
	system("PAUSE");
}
void add(int * mreg, int A){
	cout << "Додаємо до P A: ";
	*mreg += A;
	print_bits(*mreg, BITS * 2 + 2);
}
void sub(int * mreg, int S){
	cout << "Додаємо до P S: ";
	*mreg += S;
	print_bits(*mreg, BITS * 2 + 2);
}
void shift(int * mreg){
	cout << "Зсуваємо вправо на 1 біт: ";
	*mreg >>= 1;
	print_bits(*mreg, BITS * 2 + 2);
}
int multiplication(){
	cout << "-------------BOOTH'S MULTIPLICATIOM ALGORITHM--------------" << endl;
	cout << "Алгоритм Бута включаеє в себе цикличне складення\nодного із двух раніше встановлених значень A і S з произведенням P,\nа потім виконання арифметичного здвигу вправо над P.\nНехай m і r — множене і множник відповідно,\nа x і y представляють собою кількість біт в m і r." << endl;
	m = 8;
	r = 2;
	cout << "m = " << m << endl << "В бітах:";
	print_bits(m, BITS);
	cout << "r = " << r << endl << "В бітах:";
	print_bits(r, BITS);
	cout << "1. Встановити значеня A и S, а також початкове значеня P.\nКожне із цих чисел повино мати довжину, рівну(x + y + 1)." << endl;
	cout << "A: Заповнити найбільш значимі (ліві) біти значенням m в додатковому коді \nЗаповнити ті що залишились (y + 1) біт нулями.\nІ додати додатковий біт зліва" << endl;
	int A = 0;
	A |= m << BITS << 1 | 1 << BITS * 2 << 1;
	print_bits(A, BITS * 2 + 2);
	cout << "S: Заповнити найбільш значимі (ліві) біти значенням -m в додатковому коді \nЗаповнити ті що залишились (y + 1) біт нулями.\nІ додати додатковий біт зліва" << endl;
	int S = 0;
	S = (~m + 1) << BITS + 1;
	int mask = -1;
	mask = ~(mask << BITS * 2 << 1);
	S &= mask;
	print_bits(S, BITS * 2 + 2);
	cout << "P: Заповнити найбільш значимі x біт нулями.\nСправа від них заповнить біти значенням r.\nЗаписати 0 в крайній наименш значимий (правий) біт\nІ додати додатковий біт зліва" << endl;
	int P = 0;
	mask = 0;
	mask |= -1 << BITS << 1;
	mask = ~mask;
	P |= r;
	P <<= 1;
	P &= mask;
	mask = -1;
	mask = ~(mask << BITS * 2 << 1);
	P &= mask;
	print_bits(P, BITS * 2 + 2);
	cout << "Якщо їх значеня рівне 01, додаємо A до P. Переповненя ігнорувати.\n\
Якщо їх значеня рівне 10, додаємо S до P.Переповненя ігнорувати.\n\
Якщо їх значеня рівне 00, дій не потребує. P використовується без змін на наступному кроці.\n\
Якщо їх значеня рівне 11, дій не потребує. P використовується без змін на наступному кроці." << endl;;
	for (int i = 0; i < 4; i++) {
		switch (P & 3) {
		case 0 | 3:
			break;
		case 1:
			add(&P, A);
			break;
		case 2:
			sub(&P, S);
			break;
		}
		shift(&P);
	}
	cout << "Відкидаємо крайні бити: ";
	P >>= 1;

	print_bits(P, BITS * 2);
	return P;
}
void print_bits(int n, int bits){
	for (int i = bits - 1; i >= 0; i--)
		if ((n >> i) & 0x1) cout << "1";
		else cout << "0";
		cout << endl;
}

