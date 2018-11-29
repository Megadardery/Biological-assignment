#ifndef _RNA_H
#define _RNA_H
#include "NucleicAcid.h"
#include "Codon.h"
class DNA;
class Protein;
class RNA : public NucleicAcid
{
public:
	RNA();
	RNA(const std::string& _strand, RNAType _type = RNA_UNKNOWN);
	RNA(const RNA& cpy);
	RNA(const DNA& dna, bool fromMainStrand, RNAType _type = RNA_UNKNOWN);

	void setType(RNAType _type);
	RNAType getType() const;
	std::string getTypeName() const;	//uses current value of RNAType and returns name in english

	Codon getCodon(int index) const;
	void setCodon(int index, const Codon& value);

	Protein toProtein(ProteinType _type = Protein_UNKNOWN) const;

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;

	std::string alignWith(const RNA& other) const;
	virtual ~RNA();
protected:
	RNAType type;
	std::string strand2;
	void generate_strand1();
	void generate_strand2();
};

#endif