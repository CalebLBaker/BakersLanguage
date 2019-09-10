#include "Slice.h"


Slice::Slice(const TypeDefinition *bt, Scope *s, Namespace *n) : ClassDeclaration(s, n), base_type(bt) {}


Slice::Slice(Slice&& old) : ClassDeclaration(std::move(old)), base_type(old.base_type) {}

