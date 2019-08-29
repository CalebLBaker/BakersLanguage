#include "Namespace.h"


Namespace::Namespace(Scope *s, Namespace *n) : Scope(s, n), types(), functions() {}


Namespace::Namespace(Namespace&& old) : Scope(), types(std::move(old.types)),
                                        functions(std::move(old.functions)) {}
