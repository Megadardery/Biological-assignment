#include "Sequence.h"
#include <cstring>
#include <math.h>
#include <stdexcept>
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
int Sequence:: getLCS (std :: string& s1, std :: string& s2, int i, int j)
{
    if (i == -1)	return 0;
    if (j == -1)	return 0;
    int& ret = mem[i][j];
    if (~ret)	return ret;
    ret = std :: max(getLCS(s1,s2,i - 1, j), getLCS(s1,s2,i, j - 1));
    if (s1[i] == s2[j])
        ret = std ::  max(ret, getLCS(s1,s2,i - 1, j - 1) + 1);
    return ret;
}
void Sequence:: fillLCS(std :: string& res,std :: string& s1, std :: string& s2, int i, int j)
{
    if (i == -1)	return;
    if (j == -1)	return;
    int ret = getLCS(s1,s2,i, j);
    if (ret == getLCS(s1,s2,i - 1, j))
    {
        fillLCS(res,s1,s2,i - 1, j);
    }
    else if (ret == getLCS(s1,s2,i, j - 1))
    {
        fillLCS(res,s1,s2,i, j - 1);
    }
    else
    {
        fillLCS(res,s1,s2,i - 1, j - 1);
        res+=s1[i];
    }
}
std::string Sequence::alignWith(const Sequence & other)
{
    std :: string s1 = strand;
    std :: string s2 = other.strand;
    std :: string res;
    // create memory
    int mx = std :: max(s1.size(),s2.size()) + 5;
    if (mx> MAX_ARRAY_SIZE) throw std::invalid_argument("Strings size is too large for this operation");
    mem = new int* [mx];
    for (int i = 0 ; i<mx ; ++i) mem[i] = new int [mx];
    //Initializing memory by -1
    for (int i = 0 ; i<mx ; ++i)
    {
        for (int j = 0 ; j<mx ; ++j)
        {
            mem[i][j] = -1;
        }
    }
    getLCS(s1,s2,s1.size()-1,s2.size()-1);
    fillLCS(res,s1,s2,s1.size()-1,s2.size()-1);

    // releasing memory
    for (int i = 0 ; i<mx ; ++i) delete[] mem[i];
    delete[] mem;
    return res;
}
Sequence :: ~Sequence()
{

}
