#include "Protein.h"
#include "DNA.h"
#include "RNA.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <cstring>
template<typename T>
Protein<T>::Protein(int _length) : Sequence<T>(_length) { }

template<typename T>
Protein<T>::Protein(const T* _strand, int _length, ProteinType _type) : Sequence<T>(_strand,_length)
{
	type = _type;
}

template<typename T>
Protein<T>::Protein(const Protein<T>& cpy) : Sequence<T>(cpy)
{
	type = cpy.type;
}

template<typename T>
void Protein<T>::setType(ProteinType _type)
{
	type = _type;
}

template<typename T>
ProteinType Protein<T>::getType() const
{
	return type;
}

template<typename T>
const char* Protein<T>::getTypeName() const
{
	switch (type) {
	case Hormon:
		return "Hormon";
	case Enzyme:
		return "Enzyme";
	case TF:
		return "TF";
	case Cellular_Function:
		return "Cellular Function";
	default:
		return "Unknown";
	}
}

template<typename T>
void Protein<T>::setStrand(const T* _strand, int _length)
{
	delete[] this->strand;
	this->strand = new T[_length];
	this->length = _length;

	const char allowed[] = "ACDEFGHIKLMNPQRSTVWY";
	for (int i = 0; i < (int)_length; ++i)
	{
		if (!std::binary_search(allowed, allowed + 21, (char)_strand[i]))
			throw std::invalid_argument("Invalid character for Protein encountered");
		this->strand[i] = _strand[i];
	}
}

template<typename T>
bool Protein<T>::LoadSequenceFromFile(const char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
template<typename T>
bool Protein<T>::SaveSequenceToFile(const char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
template<typename T>
Protein<T> Protein<T>::operator+(const Protein<T> & other) const
{
	int newlength = this->length + other.length;
	T* temp = new T[newlength];

	memcpy(temp, this->strand, this->length * sizeof T);
	memcpy(temp + this->length, other.strand, other.length * sizeof T);

	Protein ret(temp, newlength);
	delete[] temp;
	return ret;
}
template<typename T>
bool Protein<T>::operator==(const Protein<T> & other) const
{
	if (this->length != other.length || type != other.type)
		return 0;
	else
		return !memcmp(this->strand, other.strand, this->length * sizeof T);
}

template<typename T>
bool Protein<T>::operator!=(const Protein<T> & other) const
{
	return !(*this == other);
}

template<typename T>
std::vector <DNA<T>> Protein<T>::GetDNAsEncodingMe(const DNA<T> & bigDNA) const
{
	std::vector <DNA<T>> ret;
	const T* DNAstrand = bigDNA.getStrand();
	int DNAsiz = bigDNA.getLength();
	int Psiz = this->length;
	int en = (DNAsiz - (Psiz + 1) * 3);
	for (int i = 0; i < en; ++i)
	{
		if (Protein<T>((bigDNA.toRNA(1, RNA_Unknown, i, i + (Psiz + 1) * 3 - 1)).toProtein(type, 0)) == *this)
		{
			ret.push_back(DNA<T>(DNAstrand.substrand(i, (Psiz + 1) * 3 - 1)),(Psiz + 1) * 3 - 1),bigDNA.getType());
		}
	}
	return ret;
}
template<typename T>
Protein<T> :: ~Protein()
{

}

template<typename T>
std::ostream & operator<<(std::ostream & out, const Protein<T> & obj)
{
	out << obj.getTypeName() << '\n';
	out << obj.length << '\n';

	for (int i = 0; i < obj.length; ++i)
		out << obj.strand[i] << " ";

	return out << '\n';
}

template<typename T>
std::istream & operator>>(std::istream & in, Protein<T> & obj)
{
	char typeName[31];
	in.getline(typeName,30);
	//make input lowercase
	for (int i = 0; i < typeName[i]; i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (typeName == "hormon") obj.type = Hormon;
	else if (typeName == "enzyme") obj.type = Enzyme;
	else if (typeName == "tf") obj.type = TF;
	else if (typeName == "cellular function") obj.type = Cellular_Function;
	else obj.type = Protein_Unknown;

	int _length;
	in >> _length;
	T* tmp = new T[_length];
	for (int i = 0; i < _length; ++i)
		in >> tmp[i];

	obj.setStrand(tmp, _length);
	delete[] tmp;
	return in;
}

template class Protein<int>;
template class Protein<char>;
