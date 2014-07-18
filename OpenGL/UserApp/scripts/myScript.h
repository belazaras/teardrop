#pragma once
#include <Script.h>

class myScript : 
	public Script
{
public:
	myScript(GameObject* go);

	void start();
	void update();
};