#include "OBJConverter.h"

int main(int argc, char* argv[])
{
	std::string temp = "D:/GL/Teardrop/Debug/media/models/rungholt/rungholt.obj";
	std::vector<tinyobj::shape_t> shapes;
	clock_t begin, end;
	int ms_spent;
	std::string s;


	begin = clock();
	std::string err = tinyobj::LoadObj(shapes, temp.c_str());
	end = clock();
	ms_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;
	printf("Mesh loading: %i ms.\n", ms_spent);

	if (!err.empty()) {
		std::cerr << err << std::endl;
		std::getline(std::cin, s);
		return -1;
	}

	std::ofstream fileout("output.cobj", std::ios::out | std::ios::binary);
	if (fileout)
	{
		assert(sizeof(float) == sizeof(uint32_t));
		const auto sz = sizeof(uint32_t);
		const uint32_t nMeshes = static_cast<uint32_t>(shapes.size());
		const uint32_t nMatProperties = 3;

		fileout.write((const char*)&nMeshes, sz);        // nMeshes
		fileout.write((const char*)&nMatProperties, sz); // nMatProperties

		for (size_t i = 0; i < nMeshes; ++i) {
			const uint32_t nVertices = (uint32_t)shapes[i].mesh.positions.size();
			const uint32_t nNormals = (uint32_t)shapes[i].mesh.normals.size();
			const uint32_t nTexcoords = (uint32_t)shapes[i].mesh.texcoords.size();
			const uint32_t nIndices = (uint32_t)shapes[i].mesh.indices.size();

			// Write nVertices, nNormals,, nTexcoords, nIndices
			// Write #nVertices positions
			// Write #nVertices normals
			// Write #nVertices texcoord
			// Write #nIndices  indices
			// Write #nMatProperties material properties
			fileout.write((const char*)&nVertices, sz);
			fileout.write((const char*)&nNormals, sz);
			fileout.write((const char*)&nTexcoords, sz);
			fileout.write((const char*)&nIndices, sz);

			fileout.write((const char*)&shapes[i].mesh.positions[0], nVertices  * sz);
			fileout.write((const char*)&shapes[i].mesh.normals[0], nNormals   * sz);
			fileout.write((const char*)&shapes[i].mesh.texcoords[0], nTexcoords * sz);
			fileout.write((const char*)&shapes[i].mesh.indices[0], nIndices   * sz);
			fileout.write((const char*)&shapes[i].material.ambient[0], 3 * sz);
		}
	}
	
	std::getline(std::cin, s);
	return 0;
}
