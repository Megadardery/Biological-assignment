#ifndef _RNA_H
#define _RNA_H
#include "Sequence.h"
#include "Codon.h"
#include <iosfwd>

class DNA;
class Protein;
class RNA : public Sequence
{
public:
	RNA();
	RNA(const std::string& _strand, RNAType _type = RNA_Unknown);
	RNA(const RNA& cpy);
	RNA(const DNA& dna, bool fromMainStrand, RNAType _type = RNA_Unknown, int s = -1, int e = -1);

	void setType(RNAType _type);
	RNAType getType() const;
	std::string getTypeName() const;	//uses current value of RNAType and returns name in english

	Codon getCodon(int index) const;
	void setCodon(int index, const Codon& value);

	void setStrand(std::string _strand);

	Protein toProtein(ProteinType _type = Protein_Unknown, int s = 0) const;

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;

	RNA operator +(const RNA& other) const;
	bool operator ==(const RNA& other) const;
	bool operator !=(const RNA& other) const;
	friend std::ostream& operator <<(std::ostream& out, const RNA& obj);
	friend std::istream& operator >>(std::istream& in, RNA& obj);

	virtual ~RNA();
protected:
	RNAType type;
};

#endif