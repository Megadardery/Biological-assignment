#include "Codon.h"
#include <iostream>
#include <fstream>
char Codon::mem[];
/*
char Codon::mem[] = { 'K','N','K','N','T','T','T','T',
				'R','S','R','S','I','I','M','I',
				'Q','H','Q','H','P','P','P','P',
				'R','R','R','R','L','L','L','L',
				'E','D','E','D','A','A','A','A',
				'G','G','G','G','V','V','V','V',
				'*','Y','*','Y','S','S','S','S',
				'*','C','W','C','L','F','L','F' };
*/

Codon::Codon(char _a, char _b, char _c)
{
	setSequence(_a, _b, _c);
}
Codon::Codon(char* data)
{
	setSequence(data);
}
char Codon::toAminoAcid() const
{
	int f, s, l;
	char tmp[4] = { 'A','C','G','U' };
	for (int i = 0; i < 4; ++i)
	{
		if (a == tmp[i]) f = i;
		if (b == tmp[i]) s = i;
		if (c == tmp[i]) l = i;
	}
	return mem[f * 16 + s * 4 + l];
}
bool Codon::operator==(const Codon & other) const
{
	return a == other.a && b == other.b && c == other.c;
}
bool Codon::operator!=(const Codon & other) const
{
	return !(*this == other);
}
const char* Codon::getSequence() const
{
	//TODO: might be broken
	const char ret[3] = { a,b,c };
	return ret;
}
void Codon::setSequence(char * data)
{
	a = data[0];
	b = data[1];
	c = data[2];
}
void Codon::setSequence(char _a, char _b, char _c)
{
	a = _a;
	b = _b;
	c = _c;
}
Codon :: ~Codon() {}

bool Codon::loadCodonsFromFile(const char * codonsFileName)
{
	std::ifstream file;
	file.open(codonsFileName);
	if (!file.is_open()) return 0;
	char currLine[6];
	currLine[4] = '*';
	file.getline(currLine, 6);
	int myline = 1;
	while (!file.eof()) {
		int f, s, l;
		char tmp[4] = { 'A','C','G','U' };
		for (int i = 0; i < 4; ++i)
		{
			if (currLine[0] == tmp[i]) f = i;
			if (currLine[1] == tmp[i]) s = i;
			if (currLine[2] == tmp[i]) l = i;
		}
		mem[f * 16 + s * 4 + l] = currLine[4];
		currLine[4] = '*';
		file.getline(currLine, 6);
		myline++;
	}
	file.close();
	return 1;
}


std::ostream & operator<<(std::ostream & out, const Codon & obj)
{
	out << "Raw :" << obj.a << " " << obj.b << " " << obj.c;
	out << ", AminoAcid: " << obj.toAminoAcid();
	return out;
}

std::istream & operator>>(std::istream & in, Codon & obj)
{
	return in >> obj.a >> obj.b >> obj.c;
}
