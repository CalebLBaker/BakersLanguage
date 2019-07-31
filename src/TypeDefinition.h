#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

// TypeKind enumerates the differnt kinds of types that a type could be.
enum TypeKind {
	VOID,
	SINT8,
	SINT16,
	SINT32,
	SINT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	POINTER,
	ARRAY,
	UNION,
	STRUCT,
	ALIAS
};

// TypeDefinition defines a data type
class TypeDefinition {
	public:

		// kind represents what kind of type the type is.
		TypeKind kind;		
};

#endif
