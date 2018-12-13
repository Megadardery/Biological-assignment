#ifndef _PROTEIN_H
#define _PROTEIN_H
#include "Sequence.h"
#include <iosfwd>
#include <vector>

template<typename T>
class DNA;
template<typename T>
class RNA;

template<typename T>
class Protein : public Sequence<T>
{
public:
	Protein(int _length = 0);	//initializes the protein with an empty sequence and an unknown type
	Protein(const T* _strand, int _length, ProteinType _type = Cellular_Function);
	Protein(const Protein<T>& cpy);

	void setType(ProteinType _type);
	ProteinType getType() const;
	const char * getTypeName() const;			//uses current value of RNAType and returns name in english

	void setStrand(const T * _strand, int _length);

	bool LoadSequenceFromFile(const char* filename);
	bool SaveSequenceToFile(const char* filename) const;

	Protein<T> operator +(const Protein<T>& other) const;
	bool operator ==(const Protein<T>& other) const;
	bool operator !=(const Protein<T>& other) const;
	Protein<T>& operator =(const Protein<T>& other);

	template<typename U>
	friend std::ostream& operator <<(std::ostream& out, const Protein<U>& obj);
	template<typename Z>
	friend std::istream& operator >>(std::istream& in, Protein<Z>& obj);
	std::vector<DNA<T>> GetDNAsEncodingMe(const DNA<T> & bigDNA) const;

	virtual ~Protein();
protected:
	ProteinType type;
};
#endif
