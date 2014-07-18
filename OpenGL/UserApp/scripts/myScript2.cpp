#include <Script.h>

class myScript2 : public Script
{
public:
	myScript2(GameObject* go) : Script(go) {}
	void start()
	{
		//printf("Soy myScript2");
	}

	void update()
	{
	}
};