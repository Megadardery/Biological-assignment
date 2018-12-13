// Course:  CS213 - Programming II  - 2018
// Title:   RNA Header
// Purpose: A class that manages RNAs
// Author:  Ahmed Nasr Eldardery, Belal Hamdy Ezzat, Adham Mamdouh Mohammed
// Date:    13th December 2018
// Version: 1.0
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
	RNA<T>& operator =(const RNA<T> other);

	template<typename U>
	friend std::ostream& operator <<(std::ostream& out, const RNA<U>& obj);
	template<typename Z>
	friend std::istream& operator >>(std::istream& in, RNA<Z>& obj);

	virtual ~RNA();
protected:
	RNAType type;
};

#endif
