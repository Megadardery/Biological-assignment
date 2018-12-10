#include "Protein.h"
#include "DNA.h"
#include "RNA.h"
#include <fstream>
#include <algorithm>
#include <stdexcept>
//debugging
#include <iostream>
Protein::Protein()
{

}
Protein::Protein(std::string _strand, ProteinType _type)
{
	strand = _strand;
	type = _type;
}
Protein::Protein(const Protein& cpy)
{
	strand = cpy.strand;
	type = cpy.type;
}
void Protein::setType(ProteinType _type)
{
	type = _type;
}
ProteinType Protein::getType() const
{
	return type;
}
std::string Protein::getTypeName() const
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
void Protein::setStrand(std::string _strand)
{
	const char allowed[] = "ACDEFGHIKLMNPQRSTVWY";
	for (int i = 0; i < (int)_strand.size(); ++i)
	{
		if (!std::binary_search(allowed, allowed + 21, _strand[i]))
			throw std::invalid_argument("Invalid character for Protein encountered");
	}
	strand = _strand;
}
bool Protein::LoadSequenceFromFile(char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
bool Protein::SaveSequenceToFile(char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
Protein Protein::operator+(const Protein & other) const
{
	return Protein(strand + other.strand);
}
bool Protein::operator==(const Protein & other) const
{
	return strand == other.strand && type == other.type;
}
bool Protein::operator!=(const Protein & other) const
{
	return !(*this == other);
}
std :: vector <DNA> Protein::GetDNAsEncodingMe(const DNA & bigDNA) const
{
    std :: vector <DNA> ret;
	std :: string DNAstrand = bigDNA.getStrand();
	int DNAsiz = DNAstrand.size();
	int Psiz = strand.size();
	int en = (DNAsiz - (Psiz+1)*3);
	for (int i = 0 ; i <=en ; ++i)
    {
        if (Protein((bigDNA.toRNA(1,RNA_Unknown,i,i+(Psiz+1)*3-1)).toProtein(type,0)) == *this)
        {
           ret.push_back(DNA(DNAstrand.substr(i,(Psiz+1)*3-1)));
        }
    }
	return ret;
}
Protein :: ~Protein()
{

}

std::ostream & operator<<(std::ostream & out, const Protein & obj)
{
	out << obj.getTypeName() << '\n' << obj.strand << '\n';
	return out;
}

std::istream & operator>>(std::istream & in, Protein & obj)
{
	std::string typeName;
	getline(in, typeName);
	//make input lowercase
	for (int i = 0; i < (int)typeName.size(); i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (typeName == "hormon") obj.type = Hormon;
	else if (typeName == "enzyme") obj.type = Enzyme;
	else if (typeName == "tf") obj.type = TF;
	else if (typeName == "cellular function") obj.type = Cellular_Function;
	else obj.type = Protein_Unknown;

	std::string tmp;
	getline(in, tmp);
	obj.setStrand(tmp);
	return in;
}
