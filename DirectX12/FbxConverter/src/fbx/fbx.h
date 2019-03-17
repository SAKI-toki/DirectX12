#pragma once
#include <fbxsdk.h>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <saki/vector.h>

struct VertexData
{
	saki::vector3<float> pos;
	saki::vector3<float> nor;
};

struct FbxData
{
	std::vector<VertexData> vertex;
	unsigned int vertex_num;
};

bool ConvertFbx(const std::string& path);
void RecursiveNode(FbxNode* node, std::vector<FbxData>& fbx_data);
FbxData LoadMesh(FbxMesh* mesh);
bool OutputFile(const std::string& path, std::vector<FbxData>& fbx_data);