#include <iostream>
#include "RNA.h"
#include "DNA.h"
#include "Protein.h"

using namespace std;

typedef char mytype;

int main_bak() {
	Codon::loadCodonsFromFile("CodonTable.txt");
	//AUU AUC AUA
	DNA<mytype> D1("AAGAATATTCAACCTTGA", 18);
	DNA<mytype> D2("AAAAACATCCAGCCCTAA", 18);
	DNA<mytype> D3("AAGAACATACAGCCATAG", 18);
	DNA<mytype> D4("CCTCCCATTCCGTGATAA", 18); //invalid
	DNA<mytype> D5("TTGAAAGAATATTCAACCTTGA", 22);

	cout << D1 << endl << D2 << endl << D3 << endl << D4 << endl << D5;
	
	cout << D2.toRNA().toProtein() << endl;

	D1.SaveSequenceToFile("mytest.txt");
	DNA<mytype> Dload;
	Dload.LoadSequenceFromFile("mytest.txt");
	cout << Dload << endl;
	
	DNA<mytype> bigDNA = D1 + D2 + D3 + D4 + D5 + D1;
	Protein<mytype> prot("KNIQP", 5);

	vector <DNA<mytype>> tmp = prot.GetDNAsEncodingMe(bigDNA);
	cout << bigDNA << endl;
	cout << "GetDNAsEncodingMe:\n";
	for (auto x : tmp) cout << x << endl;

	cout << "waiting";
	cin.getline(nullptr, 50);
	vector<mytype> alignment1 = D1.alignWith(D2);
	vector<mytype> alignment2 = D1.alignWith(D1);
	for (mytype x : alignment1)
		cout << x << " ";
	cout << endl;
	for (mytype x : alignment2)
		cout << x << " ";
	cout << endl;

	DNA<mytype> mydna;
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
	RNA<mytype> myrna1 = mydna.toRNA(true, mRNA);
	RNA<mytype> myrna2 = mydna.toRNA(false, pre_mRNA, 0, 4);
	cout << myrna1 << endl;
	cout << myrna2 << endl;

	cout << myrna1.toProtein() << endl;
	//cout << "Hello World";

	return 0;
}
