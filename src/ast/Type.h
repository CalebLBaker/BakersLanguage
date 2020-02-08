#ifndef TYPE_H
#define TYPE_H


#include <memory>
#include <unordered_set>


class Type {
public:
	enum Category {
		TC_TYPE,
		TC_DATA,
		TC_FUNCTION
	};
	static const Type *TYPE;
	static const Type *UINT8;
	Type(Category category);
	Type(Type&& old) : mCategory(old.mCategory) {}
	Category getCategory() const;
	static const Type* findType(Type&& type);
protected:
	Category mCategory;

	virtual const Type* moveToHeap();
	virtual size_t hash() const;
	virtual bool equal(const Type& rhs) const;

private:

	class Hasher {
	public:
		size_t operator()(const Type *pType) const;
	};

	class Comparator {
	public:
		bool operator()(const Type *pLhs, const Type *pRhs) const;
	};

	static std::unordered_set<const Type*, Hasher, Comparator> mAllTypes;
};


#endif

