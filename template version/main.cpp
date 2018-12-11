#include <iostream>
#include "RNA.h"
#include "DNA.h"
#include "Protein.h"

using namespace std;

int main() {
	DNA<char> D2("AGTG", 4);
	DNA<char> D1("AGCTG", 5);
	cout << D1;
	//cout << D1.alignWith(D2) << "\n" << D1.alignWith(D1) << endl;
	Protein<char> prot("KNTRI", 5);
	DNA<char> dna("AAGAATACTCGAATTTAAAAGAATACTCGAATTTAAAAGAATACTCGAATTAAGTAAAATACTCGAATTTAAAAGAATACTCGAATTTAAAAGAATACT", 100);
	vector <DNA<char>> tmp = prot.GetDNAsEncodingMe(dna);
	for (auto it = tmp.begin(); it != tmp.end(); ++it) cout << *it << endl;
	DNA<char> mydna;
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
	RNA<char> myrna1 = mydna.toRNA(true, mRNA);
	RNA<char> myrna2 = mydna.toRNA(false, pre_mRNA, 0, 4);
	cout << myrna1 << endl;
	cout << myrna2 << endl;

	cout << myrna1.toProtein() << endl;
	//cout << "Hello World";
}
