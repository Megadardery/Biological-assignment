#include <iostream>
#include "RNA.h"
#include "DNA.h"
#include "Protein.h"
using namespace std;

int main() {
	DNA mydna;
	bool entered = 0;
	while (!entered) {
		try {
			cin >> mydna;
			entered = 1;
		}
		catch (const exception& ex) {
			cout << ex.what() << endl;
		}
	}
	cout << endl << mydna;
	RNA myrna1 = mydna.toRNA(true, mRNA);
	RNA myrna2 = mydna.toRNA(false, pre_mRNA,0,5);
	cout << myrna1 << endl;
	cout << myrna2 << endl;

	cout << myrna1.toProtein() << endl;
	//cout << "Hello World";
}