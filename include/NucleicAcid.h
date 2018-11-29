#ifndef _NUCLEIC_ACID_H
#define _NUCLEIC_ACID_H
#include <string>
enum DNAType {
	PROMOTER,
	MOTIF,
	TAIL,
	NONCODING,
	DNA_UNKNOWN = -1
};
enum RNAType {
	mRNA,
	tRNA,
	rRNA,
	RNA_UNKNOWN = -1
};
enum ProteinType {
	HORMON,
	ENZYME,
	TF,
	CELLULAR_FUNCTION,
	Protein_UNKNOWN = -1
};
class NucleicAcid
{
public:
	NucleicAcid();
	NucleicAcid(const std::string& _strand);
	NucleicAcid(const NucleicAcid& cpy);

	std::string getStrand() const;
	virtual void setStrand(std::string _strand);

	virtual std::string getTypeName() const = 0;		//returns type name, ex. promoter DNA, rRNA, etc.

	virtual bool LoadSequenceFromFile(char* filename) = 0;
	virtual bool SaveSequenceToFile(char* filename) const = 0;

	virtual ~NucleicAcid();
protected:
	std::string strand;
};

#endif