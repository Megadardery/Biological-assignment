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
int Sequence<T>::getLCS(const T* s1, const T* s2, int i, int j, int** mem) const
{
	if (i == -1)	return 0;
	if (j == -1)	return 0;
	int& ret = mem[i][j];
	if (~ret)	return ret;
	ret = std::max(getLCS(s1, s2, i - 1, j,mem), getLCS(s1, s2, i, j - 1, mem));
	if (s1[i] == s2[j])
		ret = std::max(ret, getLCS(s1, s2, i - 1, j - 1, mem) + 1);
	return ret;
}
template<typename T>
void Sequence<T>::fillLCS(std::vector<T>& res, const T* s1, const T* s2, int i, int j, int** mem) const
{
	if (i == -1)	return;
	if (j == -1)	return;
	int ret = getLCS(s1, s2, i, j,mem);
	if (ret == getLCS(s1, s2, i - 1, j, mem))		//optimal is 
	{
		fillLCS(res, s1, s2, i - 1, j, mem);
	}
	else if (ret == getLCS(s1, s2, i, j - 1, mem))
	{
		fillLCS(res, s1, s2, i, j - 1, mem);
	}
	else
	{
		fillLCS(res, s1, s2, i - 1, j - 1, mem);
		res.push_back(s1[i]);
	}
}

template<typename T>
std :: vector<T> Sequence<T>::alignWith(const Sequence & other) const
{

	std :: vector <T> res;
	int siz1 = this->length;
	int siz2 = other.getLength();
	// create memory
	if ((siz1*siz2) > MAX_ARRAY_SIZE) throw std::invalid_argument("Strings size is too large for this operation");
	int** mem = new int*[siz1 + 5];
	for (int i = 0; i < (int)(siz1 + 5); ++i) mem[i] = new int[siz2 + 5];

	//Initializing memory by -1
	for (int i = 0; i < siz1 + 5; ++i)
	{
		for (int j = 0; j < siz2 + 5; ++j)
		{
			mem[i][j] = -1;
		}
	}
	getLCS(this->strand, other.strand, siz1-1, siz2 - 1, mem);
	fillLCS(res, this->strand, other.strand, siz1-1, siz2 - 1, mem);

	// releasing memory
	for (int i = 0; i < siz1 + 5; ++i) delete[] mem[i];
	delete[] mem;
	return res;

}

template<typename T>
T** Sequence<T>::NeedlemanWunschWith(const Sequence<T>& other, int gapScore, int matchScore, int mismatchScore) const{

	int n = this->length;
	int m = other.length;

	T* seq1 = this->strand;
	T* seq2 = other.strand;

	n++, m++;
	//allocation
	int **mem = new int*[n];
	for (int i = 0; i < n; i++) mem[i] = new int[m];

	//matrix initialization
	mem[0][0] = 0;
	for (int i = 1; i < n; i++) mem[i][0] = mem[i - 1][0] + gapScore;
	for (int j = 1; j < m; j++) mem[0][j] = mem[0][j - 1] + gapScore;

	//fill step
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			int fromDiag, fromLeft, fromUp;
			int s = seq1[i - 1] == seq2[j - 1] ? matchScore : mismatchScore;

			fromDiag = mem[i - 1][j - 1] + s;
			fromLeft = mem[i][j - 1] + gapScore;
			fromUp = mem[i - 1][j] + gapScore;


			mem[i][j] = std::max(fromDiag, std::max(fromLeft, fromUp));
		}
	}

	//Traceback Step

	n--, m--;

	int mx = n + m;
	T* AlignmentA = new T[mx];
	T* AlignmentB = new T[mx];

	for (int i = 0; i < mx; i++) AlignmentA[i] = ' ';
	for (int i = 0; i < mx; i++) AlignmentB[i] = ' ';

	int sz = mx - 1;
	while (m > 0 && n > 0)
	{
		int s = seq1[n - 1] == seq2[m - 1] ? matchScore : mismatchScore;


		if (mem[n][m] == mem[n - 1][m - 1] + s)
		{
			AlignmentA[sz] = seq1[n - 1];
			AlignmentB[sz] = seq2[m - 1];
			n--, m--;
		}
		else if (mem[n][m] == mem[n - 1][m] + gapScore)
		{
			AlignmentA[sz] = seq1[n - 1];
			AlignmentB[sz] = '-';
			n--;
		}
		else //if (n > 0 && mem[n][m] == mem[n - 1][m] + gapScore)
		{
			AlignmentA[sz] = '-';
			AlignmentB[sz] = seq2[m - 1];
			m--;
		}
		sz--;
	}
	while (n > 0) {
		AlignmentA[sz] = seq1[n - 1];
		AlignmentB[sz] = '-';
		--n;
		sz--;

	}
	while (m > 0) {
		AlignmentA[sz] = '-';
		AlignmentB[sz] = seq2[m - 1];
		--m;
		sz--;
	}
	
	//deallocation
	for (int i = 0; i < n; i++) delete[] mem[i];
	delete[] mem;

	T** ret = new T*[2];
	ret[0] = AlignmentA;
	ret[1] = AlignmentB;

	return ret;
}

template<typename T>
Sequence<T> :: ~Sequence()
{
	delete[] strand;
}
template<typename U>
std ::vector<U> alignSequences(const Sequence<U> & a, const Sequence<U> & b)
{
	return a.alignWith(b);
}



template class Sequence<int>;
template class Sequence<char>;
