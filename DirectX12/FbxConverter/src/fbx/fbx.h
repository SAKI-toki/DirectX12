/**
* @file fbx.h
* @brief fbxをコンバートする関数や構造体の宣言
* @author 石山　悠
* @date 2019/03/18
*/
#pragma once
#include <fbxsdk.h>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <saki/vector.h>

#ifdef _DLL
#ifdef _DEBUG
#pragma comment(lib,"debug/libfbxsdk-md.lib")
#else
#pragma comment(lib,"release/libfbxsdk-md.lib")

#endif //_DEBUG
#endif //_DLL

/**
* @brief 頂点情報
*/
struct VertexData
{
	saki::vector3<float> pos;
	saki::vector3<float> nor;
};

/**
* @brief FBXのデータ
*/
struct FbxData
{
	std::vector<VertexData> vertex;
	unsigned int vertex_num;
};

bool ConvertFbx(const std::string& path);
void RecursiveNode(FbxNode* node, std::vector<FbxData>& fbx_data);
bool LoadMesh(FbxMesh* mesh, FbxData& fbx_data);
bool OutputFile(const std::string& path, std::vector<FbxData>& fbx_data);