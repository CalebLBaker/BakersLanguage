#ifndef TYPE_H
#define TYPE_H


#include <memory>
#include <unordered_set>
#include <vector>


class Type {
public:
	enum Category {
		TC_TYPE = 0,
		TC_DATA,
		TC_FUNCTION
	};
	static const Type *TYPE;
	static const Type *UINT8;
	static const Type *INT64;
	static const Type *INT;
	constexpr Type(Category category) : mCategory(category) { }
	Type(Type&& old) : mCategory(old.mCategory) {}
	Category getCategory() const;
	static const Type* findType(Type&& type);
	constexpr bool canImplicitCast(const Type *pOther) const {
		return pOther == this;// || std::find(mImplicitCasts.begin(), mImplicitCasts.end(), pOther) != mImplicitCasts.end();
	}
	
	static void initializePrimitives();
	Category mCategory;
		
protected:

	virtual const Type* moveToHeap();
	virtual size_t hash() const;
	virtual bool equal(const Type& rhs) const;

	const size_t TYPE_MASK = 0;
	const size_t PRIMITIVE_MASK = 1;
	const size_t FUNCTION_MASK = 2;

private:

	class Hasher {
	public:
		size_t operator()(const Type *pType) const;
	};

	class Comparator {
	public:
		bool operator()(const Type *pLhs, const Type *pRhs) const;
	};

	//std::vector<const Type*, > mImplicitCasts;

	static std::unordered_set<const Type*, Hasher, Comparator> mAllTypes;
};


#endif

