#include "DNA.h"
#include "RNA.h"
#include <fstream>
DNA::DNA()
{
	type = DNA_UNKNOWN;
}
DNA::DNA(const std::string& _strand, DNAType _type)
{
	strand = _strand;
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
	strand = _strand;
	generate_strand2();
}
void DNA::setStrand2(std::string _strand2)
{
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
	std::string tmp1, tmp2;
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	getline(file, tmp1);
	getline(file, tmp2);
	for (int i = 0; i < (int)tmp1.size(); ++i)
	{
		if (tmp1[i] != 'A' || tmp1[i] != 'T' || tmp1[i] != 'G' || tmp1[i] != 'C') return 0;
	}
	for (int i = 0; i < (int)tmp2.size(); ++i)
	{
		if (tmp2[i] != 'A' || tmp2[i] != 'T' || tmp2[i] != 'G' || tmp2[i] != 'C') return 0;
	}
	strand = tmp1;
	for (int i = 0; i < (int)tmp2.size(); ++i) strand2[i] = tmp2[tmp2.size() - i - 1];
	return 1;
}
bool DNA::SaveSequenceToFile(char* filename) const
{
	std::string tmp2 = strand2;
	for (int i = 0; i < (int)tmp2.size(); ++i) tmp2[i] = strand2[tmp2.size() - i - 1];
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	file << strand << "\n" << tmp2 << "\n";
	return 1;
}
DNA DNA::operator+(const DNA & other) const
{
	return DNA(strand + other.strand);
}
bool DNA::operator==(const DNA & other) const
{
	// @TODO: implement
	return 0;
}
bool DNA::operator!=(const DNA & other) const
{
	// @TODO: implement
	return 0;
}
void DNA::generate_strand1()
{
	strand.resize(strand2.size());
	int s = 0;
	int e = strand2.size() - 1;
	for (int i = s; i <= e; ++i)
	{
		switch (strand2[i])
		{
		case 'A':
			strand[i] = 'T';
			break;
		case 'T':
			strand[i] = 'A';
			break;
		case 'C':
			strand[i] = 'G';
			break;
		case 'G':
			strand[i] = 'C';
			break;
		default:
			continue;
		}
	}
}
void DNA::generate_strand2()
{
	strand2.resize(strand.size());
	strand2.resize(strand.size());
	int s = 0;
	int e = strand2.size() - 1;
	for (int i = s; i <= e; ++i)
	{
		switch (strand[i])
		{
		case 'A':
			strand2[i] = 'T';
			break;
		case 'T':
			strand2[i] = 'A';
			break;
		case 'C':
			strand2[i] = 'G';
			break;
		case 'G':
			strand2[i] = 'C';
			break;
		default:
			continue;
		}
	}
}
RNA DNA::toRNA(bool fromMainStrand, RNAType _type, int s, int e) const
{
	std::string converted_strand;
	std::string curr_strand = strand2;
	if (s == -1) s++;
	if (e == -1) e = strand2.size() - 1;
	if (!(s >= 0 && s <= e && e < (int)strand2.size()))
	{
		//@TODO :: throw exception
	}
	if (fromMainStrand) curr_strand = strand;
	converted_strand = curr_strand;
	for (int i = s; i <= e; ++i)
	{
		if (curr_strand[i] == 'T') converted_strand[i] = 'U';
	}
	return RNA(converted_strand, _type);
}
std::string DNA::alignWith(const DNA & other) const
{
	// @TODO: implement
	return std::string();
}
DNA :: ~DNA()
{

}

std::ostream & operator<<(std::ostream & out, const DNA & obj)
{
	// @TODO: implement
	return out;
}

std::istream & operator>>(std::istream & in, DNA & obj)
{
	// @TODO: implement
	return in;
}
