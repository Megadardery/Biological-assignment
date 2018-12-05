#include "Protein.h"
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
	case HORMON:
		return "Hormon";
	case ENZYME:
		return "Enzyme";
	case TF:
		return "TF";
	case CELLULAR_FUNCTION:
		return "Cellular Function";
	default:
		return "Unknown";
	}
}
bool Protein::LoadSequenceFromFile(char * filename)
{
	//@TODO: implement
	return 0;
}
bool Protein::SaveSequenceToFile(char * filename) const
{
	//@TODO: implement
	return 0;
}
Protein Protein::operator+(const Protein & other) const
{
	return Protein(strand + other.strand);
}
bool Protein::operator==(const Protein & other) const
{
	//@TODO: implement
	return 0;
}
bool Protein::operator!=(const Protein & other) const
{
	//@TODO: implement
	return 0;
}
std::string Protein::alignWith(const Protein & other) const
{
	//@TODO: implement
	return std::string();
}
Protein :: ~Protein()
{

}

std::ostream & operator<<(std::ostream & out, const Protein & obj)
{
	//@TODO: implement
	return out;
}

std::istream & operator>>(std::istream & in, Protein & obj)
{
	//@TODO: implement
	return in;
}
