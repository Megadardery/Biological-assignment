#include "Sequence.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>
template<typename T>
Sequence<T>::Sequence(int _length) {
	length = _length;
	strand = new T[length];
}

template<typename T>
Sequence<T>::Sequence(const T* _strand, int _length)
{
	strand = nullptr;
	setStrand(_strand, _length);
}
template<typename T>
Sequence<T>::Sequence(const Sequence<T>& cpy)
{
	strand = nullptr;
	setStrand(cpy.strand, cpy.length);
}
template<typename T>
const T* Sequence<T>::getStrand() const
{
	return strand;
}
template<typename T>
void Sequence<T>::setStrand(const T* _strand, int _length)
{
	delete[] strand;
	length = _length;
	strand = new T[length];
	memcpy(strand, _strand, length * sizeof(T));
}
template<typename T>
int Sequence<T>::getLength() const
{
	return length;
}
template<typename T>
int Sequence<T>::getLCS(const T* s1, const T* s2, int i, int j)
{
	if (i == -1)	return 0;
	if (j == -1)	return 0;
	int& ret = mem[i][j];
	if (~ret)	return ret;
	ret = std::max(getLCS(s1, s2, i - 1, j), getLCS(s1, s2, i, j - 1));
	if (s1[i] == s2[j])
		ret = std::max(ret, getLCS(s1, s2, i - 1, j - 1) + 1);
	return ret;
}
template<typename T>
void Sequence<T>::fillLCS(std::vector<T>& res, const T* s1, const T* s2, int i, int j)
{
	if (i == -1)	return;
	if (j == -1)	return;
	int ret = getLCS(s1, s2, i, j);
	if (ret == getLCS(s1, s2, i - 1, j))
	{
		fillLCS(res, s1, s2, i - 1, j);
	}
	else if (ret == getLCS(s1, s2, i, j - 1))
	{
		fillLCS(res, s1, s2, i, j - 1);
	}
	else
	{
		fillLCS(res, s1, s2, i - 1, j - 1);
		res.push_back(s1[i]);
	}
}

template<typename T>
std :: vector<T> Sequence<T>::alignWith(const Sequence & other)
{

	std :: vector <T> res;
	int siz1 = this->length;
	int siz2 = other.getLength();
	// create memory
	if ((siz1*siz2) > MAX_ARRAY_SIZE) throw std::invalid_argument("Strings size is too large for this operation");
	mem = new int*[siz1 + 5];
	for (int i = 0; i < (int)(siz1 + 5); ++i) mem[i] = new int[siz2 + 5];

	//Initializing memory by -1
	for (int i = 0; i < siz1 + 5; ++i)
	{
		for (int j = 0; j < siz2 + 5; ++j)
		{
			mem[i][j] = -1;
		}
	}
	getLCS(this->strand, other.strand, siz1-1, siz2 - 1);
	fillLCS(res, this->strand, other.strand, siz1-1, siz2 - 1);

	// releasing memory
	for (int i = 0; i < siz1 + 5; ++i) delete[] mem[i];
	delete[] mem;
	return res;

}

template<typename T>
Sequence<T> :: ~Sequence()
{
	delete[] strand;
}
template<typename T>
T * alignSequences(const Sequence<T> & a, const Sequence<T> & b)
{
	return a.alignWith(b);
}



template class Sequence<int>;
template class Sequence<char>;
