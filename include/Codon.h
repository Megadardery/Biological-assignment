#ifndef _CODON_H
#define _CODON_H
class Codon
{
public:
	Codon(char _a, char _b, char _c);
	Codon(char* data);

	char toAminoAcid() const;
	virtual ~Codon();
protected:
	char a, b, c;
};
#endif
