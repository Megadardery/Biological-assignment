#ifndef _PROTEIN_H
#define _PROTEIN_H
#include "NucleicAcid.h"
class Protein : public NucleicAcid
{
public:
	Protein();
	Protein(std::string _strand, ProteinType _type = Protein_UNKNOWN);
	Protein(const Protein& cpy);

	void setType(ProteinType _type);
	ProteinType getType() const;
	std::string getTypeName() const;	//uses current value of RNAType and returns name in english

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;

	std::string alignWith(const Protein& other) const;

	virtual ~Protein();
};
#endif