#include "DNA.h"
#include "RNA.h"
#include <fstream>
#include <stdexcept>
DNA::DNA()
{
	type = DNA_Unknown;
}
DNA::DNA(const std::string& _strand, DNAType _type)
{
	setStrand(_strand);
	type = _type;
	generate_strand2();
}
DNA::DNA(const DNA& cpy)
{
	strand = cpy.strand;
	strand2 = cpy.strand2;
	type = cpy.type;
}
std::string DNA::getStrand2() const
{
	return strand2;
}
void DNA::setStrand(std::string _strand)
{
	for (int i = 0; i < (int)_strand.size(); ++i)
	{
		if (_strand[i] != 'A' && _strand[i] != 'T' && _strand[i] != 'G' && _strand[i] != 'C')
			throw std::invalid_argument("Invalid character for DNA encountered");
	}
	strand = _strand;
	generate_strand2();
}
void DNA::setStrand2(std::string _strand2)
{
	for (int i = 0; i < (int)_strand2.size(); ++i)
	{
		if (_strand2[i] != 'A' && _strand2[i] != 'T' && _strand2[i] != 'G' && _strand2[i] != 'C')
			throw std::invalid_argument("Invalid character for DNA encountered");
	}
	strand2 = _strand2;
	generate_strand1();
}
DNAType DNA::getType() const
{
	return type;
}
std::string DNA::getTypeName() const
{
	if (!type) return "Promoter";
	else if (type == 1) return "Motif";
	else if (type == 2) return "Tail";
	else if (type == 3) return "Noncoding";
	else return "Unknown";
}
bool DNA::LoadSequenceFromFile(char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
bool DNA::SaveSequenceToFile(char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
DNA DNA::operator+(const DNA & other) const
{
	return DNA(strand + other.strand);
}
bool DNA::operator==(const DNA & other) const
{
	return strand == other.strand && type == other.type;
}
bool DNA::operator!=(const DNA & other) const
{
	return !(*this == other);
}
void DNA::generate_strand_util(std::string& src, std::string& des) {
	des.resize(src.size());
	int s = 0;
	int e = src.size() - 1;
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
void DNA::generate_strand1()
{
	generate_strand_util(strand2, strand);
}
void DNA::generate_strand2()
{
	generate_strand_util(strand, strand2);
}
RNA DNA::toRNA(bool fromMainStrand, RNAType _type, int s, int e) const
{
	if (s == -1) s++;
	if (e == -1) e = strand2.size() - 1;
	if (!(s >= 0 && s <= e && e < (int)strand2.size()))
	{
		throw std::out_of_range("s and e out of range.");
	}

	std::string converted;
	if (fromMainStrand)
		converted = strand.substr(s, e - s + 1);
	else
		converted = strand2.substr(s, e - s + 1);

	for (int i = s; i <= e; ++i)
	{
		if (converted[i] == 'T') converted[i] = 'U';
	}
	return RNA(converted, _type);
}
DNA :: ~DNA()
{

}

std::ostream & operator<<(std::ostream & out, const DNA & obj)
{
	out << obj.getTypeName() << '\n' << obj.strand << '\n' << obj.strand2 << '\n';
	return out;
}
std::istream & operator>>(std::istream & in, DNA & obj)
{
	std::string typeName;
	getline(in, typeName);
	//make input lowercase
	for (int i = 0; i < (int)typeName.size(); i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (typeName == "promoter") obj.type = Promoter;
	else if (typeName == "motif") obj.type = Motif;
	else if (typeName == "tail") obj.type = Tail;
	else if (typeName == "noncoding") obj.type = Noncoding;
	else obj.type = DNA_Unknown;

	std::string tmp;
	getline(in, tmp);
	obj.setStrand(tmp);
	return in;
}
