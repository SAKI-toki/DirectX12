#pragma once
#include "../common/common.h"

//�ʂ���擾����C���f�b�N�X
struct Index
{
	unsigned int ipos, inor, iuv;
};

//�I�u�W�F�N�g�f�[�^
struct Obj
{
	//���_���W
	std::vector<saki::vector3<float>> pos;
	//�@��
	std::vector<saki::vector3<float>> nor;
	//UV
	std::vector<saki::vector2<float>> uv;
	//�C���f�b�N�X
	std::vector<Index> index;
};

bool ObjApp(const char*);
void OutputObj(Obj&);
