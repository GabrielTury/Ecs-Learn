#include "Coordinator.hpp"
#include <iostream>

struct Transform {
	float x;
	float y;
};
int main()
{
	Coordinator coord;

	for (int i = 0; i < 10; i++)
	{
		Entity e = coord.CreateEntity();
		coord.AddComponent(e, Transform{ float(i), float(i) });
	}

	std::cout << (coord.HasComponent<Transform>(5) ? "Entity 5 has a Transform" : "Entity 5 doesnt have a Transform") << "\n";
	
	coord.PrintComponents<Transform>();

	coord.DestroyEntity(5);
	coord.DestroyEntity(3);

	coord.PrintComponents<Transform>();
}