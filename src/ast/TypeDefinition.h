#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

// TypeKind enumerates the differnt kinds of types that a type could be.
enum TypeKind {
	VOID,   // Non-type; used as return type for functions that don't return anything
	SINT8,  // 8 bit signed integer
	SINT16, // 16 bit signed integer
	SINT32, // 32 bit signed integer
	SINT64, // 64 bit signed integer
	UINT8,  // 8 bit unsigned integer
	UINT16, // 16 bit unsigned integer
	UINT32, // 32 bit unsigned integer
	UINT64, // 64 bit unsigned integer
	UNION,  // conglomerate with members of different types stored in the same memory location
	STRUCT, // conglomerate with members variables stored in contiguous memory locations
	ALIAS   // copy of existing type
};

// TypeDefinition defines a data type
class TypeDefinition {
public:

	// kind represents what kind of type the type is.
	TypeKind kind;		

	/**
	 * TypeDefinitions constructs a TypeDefinition
	 * param k: the kind of type to define
	 */
	TypeDefinition(TypeKind k = VOID);
};

#endif
