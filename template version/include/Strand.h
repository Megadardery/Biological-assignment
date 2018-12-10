#ifndef _STRAND_H
#define _STRAND_H
template<typename T>
class Strand
{
public:
	Strand(const T*);
	~Strand();
	T& operator[](int i) {
		return data[i];
	}
	int Size() const {
		return sz;
	}
private:
	int sz;
	T* data;
};
#endif
