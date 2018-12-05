#include "RNA.h"
#include "DNA.h"
#include "Protein.h"
RNA::RNA()
{

}
RNA::RNA(const std::string& _strand, RNAType _type)
{
	strand = _strand;
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
	case rRNA:
		return "rRNA";
	case mRNA:
		return "mRNA";
	case tRNA:
		return "tRNA";
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
Protein RNA::toProtein(ProteinType _type) const
{
	std::string ret;
	char tmp;
	if (strand.size() % 3)
	{
		//@TODO :: throw exception
	}
	for (int i = 0; i < (int)strand.size(); i += 3)
	{
		tmp = Codon(strand[i], strand[i + 1], strand[i + 2]).toAminoAcid();
		if (!(tmp - '0'))
		{
			ret += tmp;
		}
		else
		{
			return (Protein(ret, _type));
		}
	}
	return (Protein(ret, _type));
}
bool RNA::LoadSequenceFromFile(char * filename)
{
	// @TODO: implement
	return 0;
}
bool RNA::SaveSequenceToFile(char * filename) const
{
	// @TODO: implement
	return 0;
}
RNA RNA::operator+(const RNA & other) const
{
	return RNA(strand + other.strand);
}
bool RNA::operator==(const RNA & other) const
{
	// @TODO: implement
	return 0;
}
bool RNA::operator!=(const RNA & other) const
{
	// @TODO: implement
	return 0;
}
std::string RNA::alignWith(const RNA & other) const
{
	// @TODO: implement
	return 0;
}
RNA :: ~RNA()
{

}

std::ostream & operator<<(std::ostream & out, const RNA & obj)
{
	// @TODO: implement
	return out;
}

std::istream & operator>>(std::istream & in, RNA & obj)
{
	// @TODO: implement
	return in;
}
