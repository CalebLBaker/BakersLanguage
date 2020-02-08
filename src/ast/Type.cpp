#include "Type.h"

#include "Primitive.h"


const Type* Type::TYPE = new Type(TC_TYPE);
const Type *Type::UINT8 = new Primitive();

std::unordered_set<const Type*, Type::Hasher, Type::Comparator> Type::mAllTypes;


Type::Type(Type::Category category) : mCategory(category) {}


Type::Category Type::getCategory() const {
	return mCategory;
}


const Type* Type::findType(Type&& type) {
	auto findResult = mAllTypes.find(&type);
	if (findResult == mAllTypes.end()) {
		return *mAllTypes.insert(type.moveToHeap()).first;
	}
	else {
		return *findResult;
	}
}


const Type* Type::moveToHeap() {
	return new Type(mCategory);
}


size_t Type::hash() const {
	return mCategory;
}


bool Type::equal(const Type& rhs) const {
	return mCategory == rhs.mCategory;
}


size_t Type::Hasher::operator()(const Type *pValue) const {
	return pValue->hash();
}


bool Type::Comparator::operator()(const Type *pLhs, const Type *pRhs) const {
	return pLhs->equal(*pRhs);
}

