#ifndef _CODON_H
#define _CODON_H
#include <iosfwd>
#include <string>
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

	std::string getSequence() const;
	void setSequence(char* data);
	void setSequence(char _a, char _b, char _c);
	virtual ~Codon();

protected:
	char a, b, c;
	static const char mem[64];
};
#endif