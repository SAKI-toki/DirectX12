/**
* @file camera.h
* @brief �J�����N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../common/alias.h"
#include <saki/singleton.h>
#include <saki/math/degree_radian_conversion.h>

/**
* @brief �J�����N���X
*/
class Camera :public saki::singleton<Camera>
{
	//�߂�����
	static constexpr float NEAR_Z = 0.1f;
	//��������
	static constexpr float FAR_Z = 100.0f;
	//�s��
	Matrix view, projection, view_mul_projection;
	//�e�v�f
	Vector pos, lookat, up;
	//�s��
	static constexpr float fov = saki::to_radian(60.0f);
	//�s��̍X�V
	void MatrixUpdate();
public:
	Camera();
	void Update();
	Matrix GetView()const;
	Matrix GetProjection()const;
	Matrix GetViewMulProjection()const;
	Vector GetPos()const;
	void SetPos(const Vector& camera_pos);
	Vector GetLookAt()const;
	void SetLookAt(const Vector& camera_look_at);
};