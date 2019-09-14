#include "TypeModifier.h"


namespace TypeModifier {

	std::string toString(Modifier mod) {
		if (mod == CONST) {
			return "#";
		}
		else {
			return "[]";
		}
	}

}

