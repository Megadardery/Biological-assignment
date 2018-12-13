// Course:  CS213 - Programming II  - 2018
// Title:   Codon Header
// Purpose: A class that manages codons
// Author:  Ahmed Nasr Eldardery, Belal Hamdy Ezzat, Adham Mamdouh Mohammed
// Date:    13th December 2018
// Version: 1.0
#ifndef _CODON_H
#define _CODON_H
#include <iosfwd>
class Codon
{

public:
	Codon(char _a, char _b, char _c);
	Codon(char* data);

	char toAminoAcid() const;

	bool operator ==(const Codon& other) const;
	bool operator !=(const Codon& other) const;
	friend std::ostream& operator <<(std::ostream& out, const Codon& obj);
	friend std::istream& operator >>(std::istream& in, Codon& obj);

	const char* getSequence() const;
	void setSequence(char* data);
	void setSequence(char _a, char _b, char _c);
	virtual ~Codon();

	static bool loadCodonsFromFile(const char * codonsFileName);
	char a, b, c;
protected:
	static char mem[64];
};
#endif