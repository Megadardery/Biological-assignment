#ifndef _RNA_H
#define _RNA_H
#include "Sequence.h"
#include "Codon.h"
#include <iosfwd>

template<typename T>
class DNA;
template<typename T>
class Protein;

template<typename T>
class RNA : public Sequence<T>
{
public:
	RNA(int _length = 0);
	RNA(const T* _strand, int _length, RNAType _type = RNA_Unknown);
	RNA(const RNA<T>& cpy);
	RNA(const DNA<T>& dna, bool fromMainStrand, RNAType _type = RNA_Unknown, int s = -1, int e = -1);

	void setType(RNAType _type);
	RNAType getType() const;
	const char* getTypeName() const;	//uses current value of RNAType and returns name in english

	Codon getCodon(int index) const;
	void setCodon(int index, const Codon& value);

	void setStrand(const T* _strand, int _length);

	Protein<T> toProtein(ProteinType _type = Protein_Unknown, int s = 0) const;

	bool LoadSequenceFromFile(const char* filename);
	bool SaveSequenceToFile(const char* filename) const;

	RNA<T> operator +(const RNA<T>& other) const;
	bool operator ==(const RNA<T>& other) const;
	bool operator !=(const RNA<T>& other) const;
template<typename T>
	friend std::ostream& operator <<(std::ostream& out, const RNA<T>& obj);
	template<typename T>
	friend std::istream& operator >>(std::istream& in, RNA<T>& obj);

	virtual ~RNA();
protected:
	RNAType type;
};

#endif
