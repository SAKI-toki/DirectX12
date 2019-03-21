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
	static constexpr float FAR_Z = 10000.0f;
	//����
	static constexpr float fov = saki::to_radian(60.0f);
	//�s��
	Matrix view, projection, view_mul_projection;
	//�ʒu,�����x�N�g��
	Vec3 pos, forward_vector;
	//�s��̍X�V
	void MatrixUpdate();
	//Z����]
	float rot_z;
public:
	Camera();
	void Update();
	Matrix GetView()const;
	Matrix GetProjection()const;
	Matrix GetViewMulProjection()const;
	Vec3 GetForward()const;
	void SetForward(const Vec3& camera_forward);
	void LookAt(const Vec3& look_at);
	Vec3 GetPos()const;
	void SetPos(const Vec3& camera_pos);
	float GetRotZ()const;
	void SetRotZ(const float camera_rot_z);
};