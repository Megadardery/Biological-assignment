#ifndef _PROTEIN_H
#define _PROTEIN_H
#include "Sequence.h"
#include <iosfwd>
class DNA;
class Protein : public Sequence
{
public:
	Protein();	//initializes the protein with an empty sequence and an unknown type
	Protein(std::string _strand, ProteinType _type = Cellular_Function);
	Protein(const Protein& cpy);

	void setType(ProteinType _type);
	ProteinType getType() const;
	std::string getTypeName() const;	//uses current value of RNAType and returns name in english

	void setStrand(std::string _strand);

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;

	Protein operator +(const Protein& other) const;
	bool operator ==(const Protein& other) const;
	bool operator !=(const Protein& other) const;
	friend std::ostream& operator <<(std::ostream& out, const Protein& obj);
	friend std::istream& operator >>(std::istream& in, Protein& obj);

	DNA* GetDNAsEncodingMe(const DNA & bigDNA);

	virtual ~Protein();
protected:
	ProteinType type;
};
#endif