#ifndef _SEQUENCE_H
#define _SEQUENCE_H
#include <string>
enum DNAType {
	Promoter,
	Motif,
	Tail,
	Noncoding,
	DNA_Unknown = -1
};
enum RNAType {
	mRNA,
	pre_mRNA,
	mRNA_exon,
	mRNA_intron,
	RNA_Unknown = -1
};
enum ProteinType {
	Hormon,
	Enzyme,
	TF,
	Cellular_Function,
	Protein_Unknown = -1
};
class Sequence
{
public:
	Sequence();
	Sequence(const std::string& _strand);
	Sequence(const Sequence& cpy);

	virtual std::string getStrand() const;
	virtual void setStrand(std::string _strand);

	virtual std::string getTypeName() const = 0;		//returns type name, ex. promoter DNA, rRNA, etc.

	virtual bool LoadSequenceFromFile(char* filename) = 0;
	virtual bool SaveSequenceToFile(char* filename) const = 0;

	std::string alignWith(const Sequence& other) const;

	virtual ~Sequence();
protected:
	std::string strand;
};

#endif