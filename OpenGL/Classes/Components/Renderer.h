#pragma once
#include <Component.h>
#include <Material.h>

struct SAMPLE_POINTS
{
	glm::vec4     point[256];
	glm::vec4     random_vectors[256];
};

class Renderer :
	public Component
{
private:
	//Material *material;
	std::vector<Material> materials;
	void setUpSSAO();

	//SUPER BETA:
	SAMPLE_POINTS point_data;
	GLuint      points_buffer;
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
	void ssao_render(GLuint pID);
};

