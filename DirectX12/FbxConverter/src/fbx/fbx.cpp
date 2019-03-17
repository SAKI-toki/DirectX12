#include "fbx.h"
#include <fstream>

bool ConvertFbx(const std::string& path)
{
	FbxManager* fbx_manager = FbxManager::Create();
	FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "fbx");
	//Import
	{
		FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "imp");
		FbxString file_path(path.c_str());
		std::cout << "FbxImporter�̏�������";
		if (fbx_importer->Initialize(file_path.Buffer(), -1, fbx_manager->GetIOSettings()))
		{
			std::cout << "����" << std::endl;
		}
		else
		{
			std::cout << "���s" << std::endl;
			return false;
		}
		std::cout << "Fbx��Import��";
		if (fbx_importer->Import(fbx_scene))
		{
			std::cout << "����" << std::endl;
		}
		else
		{
			std::cout << "���s" << std::endl;
			return false;
		}
		fbx_importer->Destroy();
	}
	//���W�n�̕ϊ�
	{
		FbxAxisSystem scene_axis = fbx_scene->GetGlobalSettings().GetAxisSystem();
		if (scene_axis != FbxAxisSystem::DirectX)
		{
			FbxAxisSystem::DirectX.ConvertScene(fbx_scene);
			std::cout << "���W�n��DirectX�ɕϊ�" << std::endl;
		}
	}
	//�O�p��
	{
		FbxGeometryConverter geometryConverter(fbx_manager);
		geometryConverter.Triangulate(fbx_scene, true);
		std::cout << "�O�p������" << std::endl;
	}
	//�m�[�h������
	std::cout << "�m�[�h���߂���A���b�V���̂ݓǂݍ��݂܂�" << std::endl;
	std::vector<FbxData> fbx_data;
	try
	{
		RecursiveNode(fbx_scene->GetRootNode(), fbx_data);
	}
	catch (...)
	{
		return false;
	}
	return OutputFile(path, fbx_data);
}

void RecursiveNode(FbxNode* node, std::vector<FbxData>& fbx_data)
{
	auto attribute = node->GetNodeAttribute();
	if (attribute != nullptr&&
		node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		fbx_data.push_back(LoadMesh(node->GetMesh()));
	}
	for (int i = 0; i < node->GetChildCount(); ++i)
	{
		RecursiveNode(node->GetChild(i), fbx_data);
	}
}

FbxData LoadMesh(FbxMesh* mesh)
{
	FbxData fbx_data;
	int polygon_num = mesh->GetPolygonCount();
	int polygon_vertex_num = mesh->GetPolygonVertexCount();
	int* index_array = mesh->GetPolygonVertices();
	FbxVector4 pos, nor;
	fbx_data.vertex.resize(polygon_num * 3);
	for (int i = 0; i < polygon_num; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			pos = mesh->GetControlPointAt(mesh->GetPolygonVertex(i, j));
			mesh->GetPolygonVertexNormal(i, j, nor);

			fbx_data.vertex[i * 3 + j].pos =
			{ static_cast<float>(pos[0]),static_cast<float>(pos[1]),static_cast<float>(pos[2]) };
			fbx_data.vertex[i * 3 + j].nor =
			{ static_cast<float>(nor[0]),static_cast<float>(nor[1]),static_cast<float>(nor[2]) };
		}
	}
	fbx_data.vertex_num = polygon_num * 3;
	return fbx_data;
}

bool OutputFile(const std::string& path, std::vector<FbxData>& fbx_data)
{
	std::ofstream ofs(
		path.substr(0, path.size() - 3) + std::string("sakimdl"),
		std::ios_base::binary);
	if (ofs.fail())
	{
		std::cout << "����Ƀt�@�C�����J���܂���ł���(�����ł��܂���ł���)" << std::endl;
		return false;
	}
	unsigned int size = static_cast<unsigned int>(fbx_data.size());
	ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (auto&& data : fbx_data)
	{
		ofs.write(reinterpret_cast<char*>(&data.vertex_num), sizeof(data.vertex_num));
		for (unsigned int i = 0; i < data.vertex_num; ++i)
		{
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].pos.x), sizeof(data.vertex[i].pos.x));
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].pos.y), sizeof(data.vertex[i].pos.y));
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].pos.z), sizeof(data.vertex[i].pos.z));
		}
		for (unsigned int i = 0; i < data.vertex_num; ++i)
		{
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].nor.x), sizeof(data.vertex[i].nor.x));
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].nor.y), sizeof(data.vertex[i].nor.y));
			ofs.write(reinterpret_cast<char*>(&data.vertex[i].nor.z), sizeof(data.vertex[i].nor.z));
		}
	}
	ofs.close();
	return true;
}