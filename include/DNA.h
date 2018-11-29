#ifndef _DNA_H
#define _DNA_H
#include "NucleicAcid.h"

class RNA;
class DNA : public NucleicAcid
{
public:
	DNA();
	DNA(const std::string& _strand, DNAType _type = DNA_UNKNOWN);
	DNA(const DNA& cpy);

	std::string getStrand2() const;

	void setStrand(std::string _strand);		//we override this to automatically generate_strand2()
	void setStrand2(std::string _strand2);		//new function (not overridden) uses generate_strand1()
	
	DNAType getType() const;
	std::string getTypeName() const;	//uses current value of DNAType and returns name in english

	RNA toRNA(bool fromMainStrand = true, RNAType _type = RNA_UNKNOWN) const;

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;

	std::string alignWith(const DNA& other) const;
	virtual ~DNA();
protected:
	DNAType type;
	std::string strand2;
	void generate_strand1();
	void generate_strand2();
};
#endif
