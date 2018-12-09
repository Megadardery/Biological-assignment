#include "RNA.h"
#include "DNA.h"
#include "Protein.h"
#include <fstream>
#include <stdexcept>
RNA::RNA()
{

}
RNA::RNA(const std::string& _strand, RNAType _type)
{
	setStrand(_strand);
	type = _type;
}
RNA::RNA(const RNA& cpy)
{
	strand = cpy.strand;
	type = cpy.type;
}
RNA::RNA(const DNA& dna, bool fromMainStrand, RNAType _type, int s, int e)
{
	RNA temp = dna.toRNA(fromMainStrand, type, s, e);
	strand = temp.strand;
	type = temp.type;
}
void RNA::setType(RNAType _type)
{
	type = _type;
}
RNAType RNA::getType() const
{
	return type;
}
std::string RNA::getTypeName() const
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
Codon RNA::getCodon(int index) const
{
	return Codon(strand[index * 3], strand[index * 3 + 1], strand[index * 3 + 2]);
}
void RNA::setCodon(int index, const Codon & value)
{
	std::string ret = value.getSequence();
	strand[index * 3] = ret[0];
	strand[index * 3 + 1] = ret[1];
	strand[index * 3 + 2] = ret[2];

}
void RNA::setStrand(std::string _strand)
{
	for (int i = 0; i < (int)_strand.size(); ++i)
	{
		if (_strand[i] != 'A' && _strand[i] != 'U' && _strand[i] != 'G' && _strand[i] != 'C')
			throw std::invalid_argument("Invalid character for RNA encountered");
	}
	strand = _strand;
}
Protein RNA::toProtein(ProteinType _type, int s) const
{
	std::string ret;
	char currAmino;
	for (int i = s; i < (int)strand.size(); i += 3)
	{
		currAmino = Codon(strand[i], strand[i + 1], strand[i + 2]).toAminoAcid();
		if (currAmino != '*')
			ret += currAmino;
		else
			return (Protein(ret, _type));
	}
	return (Protein(ret, _type));
}
bool RNA::LoadSequenceFromFile(char* filename)
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator>>(file, *this);
	file.close();
	return 1;
}
bool RNA::SaveSequenceToFile(char* filename) const
{
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) return 0;
	operator<<(file, *this);
	file.close();
	return 1;
}
RNA RNA::operator+(const RNA & other) const
{
	return RNA(strand + other.strand);
}
bool RNA::operator==(const RNA & other) const
{
	return strand == other.strand && type == other.type;
}
bool RNA::operator!=(const RNA & other) const
{
	return !(*this == other);
}
RNA :: ~RNA()
{

}

std::ostream & operator<<(std::ostream & out, const RNA & obj)
{
	out << obj.getTypeName() << '\n' << obj.strand << '\n';
	return out;
}

std::istream & operator>>(std::istream & in, RNA & obj)
{
	std::string typeName;
	getline(in, typeName);
	//make input lowercase
	for (int i = 0; i < (int)typeName.size(); i++) {
		if (typeName[i] >= 'A' && typeName[i] <= 'Z')
			typeName[i] += 0x20;
	}

	if (typeName == "mrna") obj.type = mRNA;
	else if (typeName == "pre mrna") obj.type = pre_mRNA;
	else if (typeName == "mrna exon") obj.type = mRNA_exon;
	else if (typeName == "mrna intron") obj.type = mRNA_intron;
	else obj.type = RNA_Unknown;

	std::string tmp;
	getline(in, tmp);
	obj.setStrand(tmp);
	return in;
}
