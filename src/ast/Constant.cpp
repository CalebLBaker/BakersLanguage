#include <utility>

#include "Constant.h"


Constant::Constant(const TypeDefinition *bt) : TypeDefinition(), base_type(bt) {}


Constant::Constant(Constant&& old) : TypeDefinition(std::move(old)), base_type(old.base_type)
{}

