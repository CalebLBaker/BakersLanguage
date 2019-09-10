#include "Alias.h"


Alias::Alias(const TypeDefinition *ref) : TypeDefinition(ref->size), referenced_type(ref) {}
