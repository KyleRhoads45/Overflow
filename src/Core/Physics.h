#pragma once
#include "../Components/Components.h"

class Physics {

public:

	static void Update();
	
private:

	static void PerformAABB(Transform& trans, DynamicBox& boxShape);
	static bool PerformCircleTrigger(Transform& trans, DynamicCircle& circle);

};
