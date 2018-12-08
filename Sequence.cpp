#include "Sequence.h"
#include <cstring>
Sequence::Sequence()
{

}
Sequence::Sequence(const std::string& _strand)
{
	strand = _strand;
}
Sequence::Sequence(const Sequence& cpy)
{
	strand = cpy.strand;
}
std::string Sequence::getStrand() const
{
	return strand;
}
void Sequence::setStrand(std::string _strand)
{
	strand = _strand;
}
std::string Sequence::alignWith(const Sequence & other) const
{
	//Notice: this function uses polymorphism
	//TODO be implemented
	return std::string();
}
Sequence :: ~Sequence()
{

}
