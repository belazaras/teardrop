#include "Script.h"

// Included here to avoid circular dependencies.
#include <GameObject.h>

Script::Script(GameObject *go)
{
	this->parent = go;
}


Script::~Script()
{
}
