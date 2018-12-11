#ifndef _SEQUENCE_H
#define _SEQUENCE_H
#include <vector>
enum DNAType
{
	Promoter,
	Motif,
	Tail,
	Noncoding,
	DNA_Unknown = -1
};
enum RNAType
{
	mRNA,
	pre_mRNA,
	mRNA_exon,
	mRNA_intron,
	RNA_Unknown = -1
};
enum ProteinType
{
	Hormon,
	Enzyme,
	TF,
	Cellular_Function,
	Protein_Unknown = -1
};
template<typename T>
class Sequence
{
public:
	Sequence(int _length = 0);
	Sequence(const T* _strand, int _length);
	Sequence(const Sequence<T>& cpy);

	virtual const T* getStrand() const;
	virtual void setStrand(const T* _strand, int _length);

	int getLength() const;

	virtual const char* getTypeName() const = 0;		//returns type name, ex. promoter DNA, rRNA, etc.

	virtual bool LoadSequenceFromFile(const char* filename) = 0;
	virtual bool SaveSequenceToFile(const char* filename) const = 0;

	const T* alignWith(const Sequence<T>& other);

	template<typename U>
	friend T* alignSequences(const Sequence<U>& a, const Sequence<U>& b);
	virtual ~Sequence();
protected:
	int length;
	T* strand;
private:
	const int MAX_ARRAY_SIZE = (int)2e6;
	int** mem;
	int getLCS(const T* s1, const T* s2, int i, int j);
	void fillLCS(std::vector<T>& res, const T* s1, const T* s2, int i, int j);
};

#endif
