#pragma once

#include <vector>

#include "Importer.hpp"
#include "GameObject.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	bool Import3DFromFile(GameObject & _gameObject);
	void genVAOsAndUniformBuffer(GameObject & _gameObject);
	int LoadGLTextures(GameObject & _gameObject);
	void get_bounding_box_for_node(const aiNode* nd, aiVector3D* min, aiVector3D* max);
	void get_bounding_box(aiVector3D* min, aiVector3D* max);
private:
	Assimp::Importer	m_importer;
	const aiScene*		m_scene = NULL;
	float				m_scale;
};
