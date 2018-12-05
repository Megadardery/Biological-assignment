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
/*std :: string match(std :: string strand1, std :: string strand2)
{
	// @TODO complete function
}*/
Sequence :: ~Sequence()
{

}
