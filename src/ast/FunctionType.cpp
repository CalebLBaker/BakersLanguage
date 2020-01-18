#include "FunctionType.h"


FunctionType::FunctionType(const ParameterList&, const Expression*) :
   Type(TC_FUNCTION) {}


FunctionType::FunctionType(FunctionType&& old) : Type(std::move(old)) {}


const Type* FunctionType::moveToHeap() {
	return new FunctionType(std::move(*this));
}


size_t FunctionType::hash() const {
	return TC_FUNCTION;
}


bool FunctionType::equal(const Type& rhs) const {
	return rhs.getCategory() == TC_FUNCTION;
}

