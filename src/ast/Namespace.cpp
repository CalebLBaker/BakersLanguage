#include "Namespace.h"
#include "Slice.h"
#include "Constant.h"


Namespace GLOBAL_SCOPE;


Namespace::Namespace(Scope *s, Namespace *n) : Scope(s, n), types(), functions() {}


Namespace::Namespace(Namespace&& old) : Scope(), types(std::move(old.types)), functions(std::move(old.functions)) {}


const TypeDefinition* Namespace::getDefinition(const Type *type) {
	Namespace *n;
	const TypeDefinition *base = nullptr;
	const std::string *name = &type->name;
	for (n = this; n != nullptr; n = n->owning_namespace) {
		auto *n_types = &n->types;
		if (n_types->find(*name) != n_types->end()) {
			break;
		}
	}
	if (n == nullptr) {
		return nullptr;
	}

	const std::vector<TypeModifier::Modifier> *modifiers = &type->modifiers;
	return n->getDefinitionRecurse(name, modifiers->cbegin(), modifiers->cend());
}


const TypeDefinition* Namespace::getDefinitionRecurse(const std::string *name, std::vector<TypeModifier::Modifier>::const_iterator modifier_begin, std::vector<TypeModifier::Modifier>::const_iterator modifier_end) {

	std::string modified_name = "";
	for (auto i = modifier_begin; i != modifier_end; i++) {
		modified_name.append(toString(*i));
	}
	modified_name.append(*name);

	auto entry = types.find(modified_name);
	if (entry != types.end()) {
		return entry->second.get();
	}
	
	const TypeDefinition *base_type = getDefinitionRecurse(name, modifier_begin + 1, modifier_end);

	const TypeDefinition *ret;
	switch (*modifier_begin) {
		case TypeModifier::SLICE: {
			ret = new Slice(base_type);
			break;
		}
		case TypeModifier::CONST: {
			ret = new Constant(base_type);
			break;
		}
		default: {
			return nullptr;
		}
	}

	types.emplace(modified_name, ret);
	return ret;
}


