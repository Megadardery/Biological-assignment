#ifndef _DNA_H
#define _DNA_H
#include "Sequence.h"
#include <iosfwd>

class RNA;
class DNA : public Sequence
{
public:
	DNA();
	DNA(const std::string& _strand, DNAType _type = DNA_Unknown);
	DNA(const DNA& cpy);

	std::string getStrand2() const;

	void setStrand(std::string _strand);		//we override this to automatically generate_strand2()
	void setStrand2(std::string _strand2);		//new function (not overridden) uses generate_strand1()
	
	DNAType getType() const;
	std::string getTypeName() const;	//uses current value of DNAType and returns name in english

	RNA toRNA(bool fromMainStrand = true, RNAType _type = mRNA, int s = -1, int e = -1) const;

	bool LoadSequenceFromFile(char* filename);
	bool SaveSequenceToFile(char* filename) const;
 
	DNA operator +(const DNA& other) const;
	bool operator ==(const DNA& other) const;
	bool operator !=(const DNA& other) const;
	friend std::ostream& operator <<(std::ostream& out, const DNA& obj);
	friend std::istream& operator >>(std::istream& in, DNA& obj);

	virtual ~DNA();
protected:
	DNAType type;
	std::string strand2;
	void generate_strand1();
	void generate_strand2();
private:
	void generate_strand_util(std::string& src, std::string& des);
};
#endif
