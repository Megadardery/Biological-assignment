// Course:  CS213 - Programming II  - 2018
// Title:   Main
// Purpose: Main menu and tests
// Author:  Ahmed Nasr Eldardery, Belal Hamdy Ezzat, Adham Mamdouh Mohammed
// Date:    13th December 2018
// Version: 1.0
#include <iostream>
#include <vector>
#include <algorithm>
#include "RNA.h"
#include "DNA.h"
#include "Protein.h"

typedef char mytype;
using namespace std;
const int STR_SIZE = 300;

template<typename SEQ>
void Take_Sequence(SEQ& curr);

template<typename SEQ>
void Align_Sequence(SEQ& curr);

template<typename D>
void DNAMenu(DNA<D>& curr);

template<typename R>
void RNAMenu(RNA<R>& curr);

template<typename P>
void ProteinMenu(Protein<P>& curr);

void getNum(int& n, int s, int e);

int main()
{
	DNA<mytype> dna;
	RNA<mytype> rna;
	Protein<mytype> protein;
	int choice = 1;
	cout << "Ahlan ya user ya 7abiby \n";
	char codonfilename[100];
	do {
		cout << "Enter Codon Table filename:\n";
		cin.getline(codonfilename, 100);
	}//Keep looping until success, if fail, display an error message
	while(!Codon::loadCodonsFromFile(codonfilename) && (cout << "Can't open file\n", 1));

	while (choice)
	{
		cout << "3auz eh delw2ty\n1-DNA\n2-RNA\n3-Protein\n0-Exit\n";
		getNum(choice, 0, 3);
		switch (choice)
		{
		case 1:
			DNAMenu<mytype>(dna);
			break;
		case 2:
			RNAMenu<mytype>(rna);
			break;
		case 3:
			ProteinMenu<mytype>(protein);
			break;
		default:
			cout << "Bye Bye ya 2alby ^_^ \n";
			return 0;
		}
	}
	return 0;
}
template<typename D>
void DNAMenu(DNA<D>& curr)
{
	RNA<D> changemenu;
	char filename[300];
	DNA<D> tmp;
	while (true) {

		int mainChoice;
		cout << "1- Enter new sequence\n2- Print the current sequence\n3- Compare between the current DNA and another one\n"
			<< "4- Save Current DNA\n5- Append with another sequence\n6- Align with another sequence\n7- Change to RNA\n0- Exit\n";
		getNum(mainChoice, 0, 7);
		switch (mainChoice)
		{
		case 1:
			Take_Sequence(curr);
			break;
		case 2:
			cout << curr;
			break;
		case 3:
			Take_Sequence(tmp);
			if (curr == tmp) cout << "SAME\n";
			else cout << "DIFFERENT\n";
			break;
		case 4:
			cout << "Enter the name of the file (don't forget the extension)\n";
			cin >> filename;
			if (!curr.SaveSequenceToFile(filename))
				cout << "Can't open file\n";

			break;
		case 5:
			Take_Sequence(tmp);
			curr = curr + tmp;
			break;
		case 6:
			Align_Sequence(curr);
			break;

		case 7:
			int mainstrand;
			int startStrand, endStrand;
			cout << "From the main strand (1) or From the complementary strand (0)?\n";
			getNum(mainstrand, 0, 1);
			cout << "Enter the start and the end of the strand {(-1,-1) for the whole strand}\n";
			getNum(startStrand, -1, curr.getLength());
			getNum(endStrand, startStrand, curr.getLength());
			changemenu = curr.toRNA(mainstrand,mRNA,startStrand,endStrand);
			RNAMenu(changemenu);
			break;
		case 0:
			return;
		default:
			return;
		}
	}
}
template<typename R>
void RNAMenu(RNA<R>& curr)
{
	Protein<R> changemenu;
	char filename[300];
	RNA<R> tmp;
	while (true) {

		int mainChoice;
		cout << "1- Enter new sequence\n2- Print the current sequence\n3- Compare between the current RNA and another one\n"
			<< "4- Save Current RNA\n5- Append with another sequence\n6- Align with another sequence\n7- Change to Protein\n0- Exit\n";
		getNum(mainChoice, 0, 7);
		switch (mainChoice)
		{
		case 1:
			Take_Sequence(curr);
			break;
		case 2:
			cout << curr;
			break;
		case 3:
			Take_Sequence(tmp);
			if (curr == tmp) cout << "SAME\n";
			else cout << "DIFFERENT\n";
			break;
		case 4:
			cout << "Enter the name of the file (don't forget the extension)\n";
			cin.getline(filename, STR_SIZE);
			if (!curr.SaveSequenceToFile(filename))
				cout << "Can't open file\n";

			break;
		case 5:
			Take_Sequence(tmp);
			curr = curr + tmp;
			break;
		case 6:
			Align_Sequence(curr);
			break;

		case 7:
			int startStrand;
			cout << "Enter the start of the strand (-1) for the whole strand\n";
			getNum(startStrand, -1, curr.getLength());
			changemenu = curr.toProtein(Hormon, startStrand);
			ProteinMenu(changemenu);
			break;
		case 0:
			return;
		default:
			return;
		}
	}
}
template<typename P>
void ProteinMenu(Protein<P>& curr)
{
	char filename[300];
	DNA<P> longsequence;
	vector <DNA<P>> resEncoding;
	Protein<P> tmp;
	while (true) {
		int mainChoice;
		cout << "1- Enter new sequence\n2- Print the current sequence\n3- Compare between the current Protein and another one\n"
			<< "4- Save Current Protein\n5- Append with another sequence\n6- Align with another sequence\n7- Get DNA Encoding me\n0- Exit\n";
		getNum(mainChoice, 0, 8);
		switch (mainChoice)
		{
		case 1:
			Take_Sequence(curr);
			break;
		case 2:
			cout << curr;
			break;
		case 3:
			Take_Sequence(tmp);
			if (curr == tmp) cout << "SAME\n";
			else cout << "DIFFERENT\n";
			break;
		case 4:
			cout << "Enter the name of the file (don't forget the extension)\n";
			cin.getline(filename, STR_SIZE);
			if (!curr.SaveSequenceToFile(filename))
				cout << "Can't open file\n";

			break;
		case 5:
			Take_Sequence(tmp);
			curr = curr + tmp;
			break;
		case 6:
			Align_Sequence(curr);
			break;

		case 7:
			cout << "Enter the long sequence of DNA\n";
			Take_Sequence(longsequence);
			resEncoding = curr.GetDNAsEncodingMe(longsequence);
			for (auto item : resEncoding) cout << item << " ";
			cout << "\n";
			break;
		case 0:
			return;
		default:
			return;
		}
	}
}
template<typename SEQ>
void Align_Sequence(SEQ& curr) {
	SEQ tmp;
	Take_Sequence(tmp);
	int secondChoice;
	cout << "1- Longest Common Subsequence\n2- Needleman Wunsch\n";
	getNum(secondChoice, 1, 2);
	switch (secondChoice)
	{
	case 1:
		for (auto item : curr.alignWith(tmp)) cout << item << " ";
		break;
	case 2:
		auto ret = curr.NeedlemanWunschWith(tmp);
		int sz = tmp.getLength() + curr.getLength();
		for (int i = 0; i < sz; i++) cout << ret[0][i] << " ";
		cout << endl;
		for (int i = 0; i < sz; i++) cout << ret[1][i] << " ";
		delete[] ret[0];
		delete[] ret[1];
		delete[] ret;
		break;
	}
	cout << "\n";
}
template<typename SEQ>
void Take_Sequence(SEQ& curr)
{
	char filename[100];
	int secondChoice;
	cout << "1- Enter from Console\n2- Enter from File\n";
	getNum(secondChoice, 1, 2);
	switch (secondChoice)
	{
	case 1:
		cout << "Input format :\nLine 1 : TYPE\nLine 2 : SIZE\nLine 3 : DATA\n\n";
		cin >> curr;
		break;
	case 2:
		cout << "Enter the name of the file (don't forget the extension)\n";
		//cin.ignore(INT_MAX, '\n');
		cin.getline(filename, STR_SIZE);
		if (!curr.LoadSequenceFromFile(filename))
			cout << "Can't open file\n";
		break;
	}
}
void getNum(int& n, int s, int e)
{
	while (true)
	{
		cin >> n;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid input.\n";
		}
		else if (n > e || n < s)
		{
			cout << "Invalid input. only (" << s << " , " << e << ") allowed only\n";
		}
		else
		{
			cin.ignore(INT_MAX, '\n');
			return;
		}
	}
}
