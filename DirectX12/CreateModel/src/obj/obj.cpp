#include "obj.h"
#include <algorithm>

bool ObjApp(const char* path)
{
	std::ifstream ifs(path);
	if (ifs.fail())
	{
		ConsoleComment("ファイルの読み込みに失敗");
		return false;
	}
	Obj obj;
	std::string buf;
	unsigned int prev_index = 0;
	while (true)
	{
		//文字列を読み込む
		ifs >> buf;
		if (!ifs)
		{
			break;
		}
		//コメント
		if (buf == "#")
		{
		}
		//頂点座標
		else if (buf == "v")
		{
			float x, y, z;
			ifs >> x >> y >> z;
			obj.pos.push_back({ x,y,z });
		}
		//法線
		else if (buf == "vn")
		{
			float x, y, z;
			ifs >> x >> y >> z;
			obj.nor.push_back({ x,y,z });
		}
		//UV
		else if (buf == "vt")
		{
			float x, y;
			ifs >> x >> y;
			obj.uv.push_back({ x,y });
		}
		//面
		else if (buf == "f")
		{
			unsigned int ipos, inor, iuv;
			for (int i = 0; i < 3; ++i)
			{
				ifs >> ipos;
				ifs.ignore();
				ifs >> iuv;
				ifs.ignore();
				ifs >> inor;
				obj.index.push_back({ ipos - 1,inor - 1,iuv - 1 });
			}
		}
	}

	//出力
	OutputObj(obj);

	return true;
}

//出力
void OutputObj(Obj& obj)
{
	//出力するパス
	char o_path[PATH_SIZE];
	ConsoleComment("出力するパスを入力してください");
	std::cin >> o_path;
	std::ofstream ofs(o_path, std::ios_base::binary);
	unsigned int pos_num = static_cast<unsigned int>(obj.pos.size());
	unsigned int nor_num = static_cast<unsigned int>(obj.nor.size());
	unsigned int uv_num = static_cast<unsigned int>(obj.uv.size());
	unsigned int index_num = static_cast<unsigned int>(obj.index.size());
	ofs.write(reinterpret_cast<char*>(&pos_num), sizeof(pos_num));
	ofs.write(reinterpret_cast<char*>(&nor_num), sizeof(nor_num));
	ofs.write(reinterpret_cast<char*>(&uv_num), sizeof(uv_num));
	ofs.write(reinterpret_cast<char*>(&index_num), sizeof(index_num));
	for (unsigned int i = 0; i < pos_num; ++i)
	{
		ofs.write(reinterpret_cast<char*>(&obj.pos[i].x), sizeof(obj.pos[i].x));
		ofs.write(reinterpret_cast<char*>(&obj.pos[i].y), sizeof(obj.pos[i].y));
		ofs.write(reinterpret_cast<char*>(&obj.pos[i].z), sizeof(obj.pos[i].z));
	}
	for (unsigned int i = 0; i < nor_num; ++i)
	{
		ofs.write(reinterpret_cast<char*>(&obj.nor[i].x), sizeof(obj.nor[i].x));
		ofs.write(reinterpret_cast<char*>(&obj.nor[i].y), sizeof(obj.nor[i].y));
		ofs.write(reinterpret_cast<char*>(&obj.nor[i].z), sizeof(obj.nor[i].z));
	}
	for (unsigned int i = 0; i < uv_num; ++i)
	{
		ofs.write(reinterpret_cast<char*>(&obj.uv[i].x), sizeof(obj.uv[i].x));
		ofs.write(reinterpret_cast<char*>(&obj.uv[i].y), sizeof(obj.uv[i].y));
	}
	for (unsigned int i = 0; i < index_num; ++i)
	{
		ofs.write(reinterpret_cast<char*>(&obj.index[i].ipos), sizeof(obj.index[i].ipos));
		ofs.write(reinterpret_cast<char*>(&obj.index[i].inor), sizeof(obj.index[i].inor));
		ofs.write(reinterpret_cast<char*>(&obj.index[i].iuv), sizeof(obj.index[i].iuv));
	}
}