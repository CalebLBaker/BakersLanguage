#include "Type.h"

#include "Primitive.h"


const Type *Type::TYPE;
const Type *Type::UINT8;
const Type *Type::INT64;
const Type *Type::INT;

std::unordered_set<const Type*, Type::Hasher, Type::Comparator> Type::mAllTypes;


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

void Type::initializePrimitives() {
	TYPE = new Type(TC_TYPE);
	UINT8 = new Primitive(1, Primitive::UNSIGNED);
	INT64 = new Primitive(8, Primitive::SIGNED);
	INT = INT64;
}

