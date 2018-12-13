// Course:  CS213 - Programming II  - 2018
// Title:   DNA Header
// Purpose: DNA header include complementry strand
// Author:  Ahmed Nasr Eldardery, Belal Hamdy Ezzat, Adham Mamdouh Mohammed
// Date:    13th December 2018
// Version: 1.0
#ifndef _DNA_H
#define _DNA_H
#include "Sequence.h"
#include <iosfwd>

template<typename T>
class RNA;

template<typename T>
class DNA : public Sequence<T>
{
public:
	DNA(int length = 0);
	DNA(const T* _strand1, int _length, DNAType _type = DNA_Unknown);
	DNA(const DNA<T>& cpy);

	const T* getStrand2() const;

	void setStrand(const T* _strand, int _length);			//we override this to automatically generate_strand2()
	void setStrand2(const T* _strand2, int _length);		//new function (not overridden) uses generate_strand1()

	DNAType getType() const;
	const char* getTypeName() const;						//uses current value of DNAType and returns name in english

	RNA<T> toRNA(bool fromMainStrand = true, RNAType _type = mRNA, int s = -1, int e = -1) const;


	bool LoadSequenceFromFile(const char* filename);
	bool SaveSequenceToFile(const char* filename) const;

	DNA<T> operator +(const DNA<T>& other)const ;
	bool operator ==(const DNA<T>& other) const;
	bool operator !=(const DNA<T>& other) const;
	DNA<T>& operator =(const DNA<T> other);
	template<typename U>
	friend std::ostream& operator <<(std::ostream& out, const DNA<U>& obj);
	template<typename Z>
	friend std::istream& operator >>(std::istream& in, DNA<Z>& obj);

    T* substrand(int s , int siz) const;
	virtual ~DNA();
protected:
	DNAType type;
	T* strand2;
	void generate_strand1();
	void generate_strand2();
private:
	void generate_strand_util(const T* src, T* & des);
};
#endif
