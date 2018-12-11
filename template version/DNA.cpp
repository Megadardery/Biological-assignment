#include "DNA.h"
#include "RNA.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>
template<typename T>
DNA<T>::DNA(int _length) : Sequence<T>(_length)
{
	type = DNA_Unknown;
	strand2 = nullptr;
	generate_strand2();
}
template<typename T>
DNA<T>::DNA(const T * _strand1, int _length, DNAType _type) : Sequence<T>(_strand1, _length)
{
	type = _type;
	strand2 = nullptr;
	generate_strand2();
}
template<typename T>
DNA<T>::DNA(const DNA<T>& cpy) : Sequence<T>(cpy)
{
	type = cpy.type;
	strand2 = nullptr;
	generate_strand2();
}
template<typename T>
const T* DNA<T>::getStrand2() const
{
	return strand2;
}
template<typename T>
void DNA<T>::setStrand(const T* _strand, int _length)
{
	this->length = _length;
	delete[] this->strand;
	this->strand = new T[this->length];
	for (int i = 0; i < this->length; ++i)
	{
		if (_strand[i] != 'A' && _strand[i] != 'T' && _strand[i] != 'G' && _strand[i] != 'C')
			throw std::invalid_argument("Invalid character for DNA encountered");
		this->strand[i] = _strand[i];
	}
	generate_strand2();
}
template<typename T>
void DNA<T>::setStrand2(const T* _strand2, int _length)
{
	this->length = _length;
	delete[] strand2;
	strand2 = new T[this->length];
	for (int i = 0; i < this->length; ++i)
	{
		if (_strand2[i] != 'A' && _strand2[i] != 'T' && _strand2[i] != 'G' && _strand2[i] != 'C')
			throw std::invalid_argument("Invalid character for DNA encountered");
		strand2[i] = _strand2[i];
	}
	generate_strand1();
}
template<typename T>
DNAType DNA<T>::getType() const
{
	return type;
}

template<typename T>
const char* DNA<T>::getTypeName() const
{
	if (!type) return "Promoter";
	else if (type == 1) return "Motif";
	else if (type == 2) return "Tail";
	else if (type == 3) return "Noncoding";
	else return "Unknown";
}
template<typename T>
bool DNA<T>::LoadSequenceFromFile(const char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
template<typename T>
bool DNA<T>::SaveSequenceToFile(const char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
template<typename T>
DNA<T> DNA<T>::operator+(const DNA & other) const
{
	int newlength = this->length + other.length;
	T* temp = new T[newlength];

	memcpy(temp,  (this->strand), (this->length * sizeof T));
	memcpy(temp + this->length, other.strand, other.length * sizeof T);

	DNA ret(temp, newlength);
	delete[] temp;
	return ret;
}
template<typename T>
bool DNA<T>::operator==(const DNA & other) const
{
	if (this->length != other.length || type != other.type)
		return 0;
	else
		return !memcmp(this->strand, other.strand, this->length * sizeof T);
}
template<typename T>
bool DNA<T>::operator!=(const DNA & other) const
{
	return !(*this == other);
}

template<typename T>
void DNA<T>::generate_strand_util(const T* src, T* &des) {
	delete[] des;
	des = new T[this->length];

	int s = 0;
	int e = this->length - 1;
	for (int i = s; i <= e; ++i)
	{
		switch (src[i])
		{
		case 'A':
			des[e - i] = 'T';
			break;
		case 'T':
			des[e - i] = 'A';
			break;
		case 'C':
			des[e - i] = 'G';
			break;
		case 'G':
			des[e - i] = 'C';
			break;
		default:
			des[e - i] = src[e - i];
		}
	}
}
template<typename T>
void DNA<T>::generate_strand1()
{
	generate_strand_util(strand2, this->strand);
}
template<typename T>
void DNA<T>::generate_strand2()
{
	generate_strand_util(this->strand, strand2);
}
template<typename T>
T* DNA<T> ::  substrand(int s , int siz)
{
    T* ret = new T [siz];
    for (int i = 0 ; i<siz ; ++i) ret[i] = this->strand[s++];
    return ret;
}
template<typename T>
RNA<T> DNA<T>::toRNA(bool fromMainStrand, RNAType _type, int s, int e) const
{
	if (s == -1) s++;
	if (e == -1) e = this->length - 1;
	if (!(s >= 0 && s <= e && e < this->length))
	{
		throw std::out_of_range("s and e out of range.");
	}

	int newlength = e - s + 1;
	T* converted = new T[newlength];
	if (fromMainStrand)
		memcpy(converted, this->strand + s, newlength * sizeof T);
	else
		memcpy(converted, strand2 + s, newlength * sizeof T);


	for (int i = 0; i < newlength; ++i)
	{
		if (converted[i] == 'T') converted[i] = 'U';
	}
	return RNA<T>(converted, newlength, _type);
}
template<typename T>
DNA<T> :: ~DNA()
{
	delete[] strand2;
}
template<typename T>
std::ostream & operator<<(std::ostream & out, const DNA<T> & obj)
{
	out << obj.getTypeName() << '\n';
	out << obj.length << '\n';

	for (int i = 0; i < obj.length; ++i)
		out << obj.strand[i] << " ";

	out << '\n';

	for (int i = 0; i < obj.length; ++i)
		out << obj.strand2[i] << " ";

	return out << '\n';
}
template<typename T>
std::istream & operator>>(std::istream & in, DNA<T> & obj)
{
	char typeName[31];
	in.getline(typeName,30);
	//make input lowercase
	for (int i = 0; typeName[i]; i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (strcmp(typeName, "promoter") == 0) obj.type = Promoter;
	else if (strcmp(typeName, "motif") == 0) obj.type = Motif;
	else if (strcmp(typeName, "tail") == 0) obj.type = Tail;
	else if (strcmp(typeName, "noncoding") == 0) obj.type = Noncoding;
	else obj.type = DNA_Unknown;

	int _length;
	in >> _length;
	T* tmp = new T[_length];
	for (int i = 0; i < _length; ++i)
		in >> tmp[i];

	obj.setStrand(tmp, _length);
	delete[] tmp;
	return in;
}

template class DNA<int>;
template class DNA<char>;
