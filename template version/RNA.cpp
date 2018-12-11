#include "RNA.h"
#include "DNA.h"
#include "Protein.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
template<typename T>
RNA<T>::RNA(int _length) : Sequence<T>(_length) { }

template<typename T>
RNA<T>::RNA(const T* _strand, int _length, RNAType _type) : Sequence<T>(_strand, _length)
{
	type = _type;
}

template<typename T>
RNA<T>::RNA(const RNA<T>& cpy) : Sequence<T>(cpy)
{
	type = cpy.type;
}

template<typename T>
RNA<T>::RNA(const DNA<T>& dna, bool fromMainStrand, RNAType _type, int s, int e)
{
	RNA tmp = dna.toRNA(fromMainStrand, _type, s, e);
	setStrand(tmp.strand, tmp.length);
	type = tmp.type;
}

template<typename T>
void RNA<T>::setType(RNAType _type)
{
	type = _type;
}

template<typename T>
RNAType RNA<T>::getType() const
{
	return type;
}

template<typename T>
const char* RNA<T>::getTypeName() const
{
	switch (type) {
	case mRNA:
		return "mRNA";
	case mRNA_exon:
		return "mRNA exon";
	case mRNA_intron:
		return "mRNA intron";
	case pre_mRNA:
		return "pre mRNA";
	default:
		return "Unknown";
	}
}
template<typename T>
Codon RNA<T>::getCodon(int index) const
{
	return Codon(this->strand[index * 3], this->strand[index * 3 + 1], this->strand[index * 3 + 2]);
}
template<typename T>
void RNA<T>::setCodon(int index, const Codon & value)
{

	this->strand[index * 3] = value.a;
	this->strand[index * 3 + 1] = value.b;
	this->strand[index * 3 + 2] = value.c;

}
template<typename T>
void RNA<T>::setStrand(const T* _strand, int _length)
{
	this->length = _length;
	delete[] this->strand;
	this->strand = new T[this->length];
	for (int i = 0; i < (int)_length; ++i)
	{
		if (_strand[i] != 'A' && _strand[i] != 'U' && _strand[i] != 'G' && _strand[i] != 'C')
			throw std::invalid_argument("Invalid character for RNA encountered");
		this->strand[i] = _strand[i];
	}
}
template<typename T>
Protein<T> RNA<T>::toProtein(ProteinType _type, int s) const
{
	T* ret = new T[(this->length - s) / 3];
	int sz = 0;
	char currAmino;
	for (int i = s; i+2 < this->length; i += 3)
	{
		currAmino = Codon(this->strand[i], this->strand[i + 1], this->strand[i + 2]).toAminoAcid();
		if (currAmino != '*')
			ret[sz++] = currAmino;
		else
			break;
	}
	Protein<T> res(ret, sz);
	delete[] ret;
	return res;
}
template<typename T>
bool RNA<T>::LoadSequenceFromFile(const char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
template<typename T>
bool RNA<T>::SaveSequenceToFile(const char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
template<typename T>
RNA<T> RNA<T>::operator+(const RNA<T> & other) const
{
	int newlength = this->length + other.length;
	T* temp = new T[newlength];

	memcpy(temp, this->strand, this->length * sizeof T);
	memcpy(temp + this->length, other.strand, other.length * sizeof T);

	RNA<T> ret(temp, newlength);
	delete[] temp;
	return ret;
}
template<typename T>
bool RNA<T>::operator==(const RNA<T> & other) const
{
	if (this->length != other.length || type != other.type)
		return 0;
	else
		return !memcmp(this->strand, other.strand, this->length * sizeof T);
}
template<typename T>
bool RNA<T>::operator!=(const RNA<T> & other) const
{
	return !(*this == other);
}
template<typename T>
RNA<T> :: ~RNA()
{

}
template<typename T>
std::ostream & operator<<(std::ostream & out, const RNA<T> & obj)
{
	out << obj.getTypeName() << '\n';
	out << obj.length << '\n';

	for (int i = 0; i < obj.length; ++i)
		out << obj.strand[i] << " ";

	return out << '\n';
}
template<typename T>
std::istream & operator>>(std::istream & in, RNA<T> & obj)
{
	char typeName[31];
	in.getline(typeName,30);
	//make input lowercase
	for (int i = 0; typeName[i]; i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (typeName == "mrna") obj.type = mRNA;
	else if (typeName == "pre mrna") obj.type = pre_mRNA;
	else if (typeName == "mrna exon") obj.type = mRNA_exon;
	else if (typeName == "mrna intron") obj.type = mRNA_intron;
	else obj.type = RNA_Unknown;

	int _length;
	in >> _length;
	T* tmp = new T[_length];
	for (int i = 0; i < _length; ++i)
		in >> tmp[i];

	obj.setStrand(tmp, _length);
	delete[] tmp;
	return in;
}

template class RNA<int>;
template class RNA<char>;
