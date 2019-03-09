#pragma once
#include "../common/common.h"

//面から取得するインデックス
struct Index
{
	unsigned int ipos, inor, iuv;
};

//オブジェクトデータ
struct Obj
{
	//頂点座標
	std::vector<saki::vector3<float>> pos;
	//法線
	std::vector<saki::vector3<float>> nor;
	//UV
	std::vector<saki::vector2<float>> uv;
	//インデックス
	std::vector<Index> index;
};

bool ObjApp(const char*);
void OutputObj(Obj&);
