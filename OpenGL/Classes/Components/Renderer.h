#pragma once
#include <Component.h>
#include <Material.h>

class Renderer :
	public Component
{
private:
	//Material *material;
	std::vector<Material> materials;
public:
	bool enabled;
	Renderer(GameObject *go);
	~Renderer();
	void setMaterial(Material material);
	void setMaterials(std::vector<Material> materials);
	Material getMaterial();
	void reloadMaterials(); // Super Beta
	void render();
	void deferred_render(GLuint pID);
};

