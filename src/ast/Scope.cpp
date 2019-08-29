#include "Scope.h"


Scope::Scope(Scope *s, Namespace *n) : owning_scope(s), owning_namespace(n) {}

