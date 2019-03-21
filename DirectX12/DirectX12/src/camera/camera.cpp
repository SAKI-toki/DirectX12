/**
* @file camera.cpp
* @brief �J�����N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "camera.h"
#include "../common/window_size.h"
#include <cmath>
#include <saki/math/pi.h>

#pragma region public

/**
* @brief �J�����̃R���X�g���N�^
*/
Camera::Camera() :
	pos({ 0.0f,0.0f,0.0f }),
	forward_vector({ 0.0f,0.0f,1.0f }),
	rot_z(0.0f)
{
	MatrixUpdate();
}

/**
* @brief �J�����̍X�V
*/
void Camera::Update()
{
	MatrixUpdate();
}

/**
* @brief �r���[�s��̎擾
* @return �r���[�s��
*/
Matrix Camera::GetView()const
{
	return view;
}

/**
* @brief �v���W�F�N�V�����s��̎擾
* @return �v���W�F�N�V�����s��
*/
Matrix Camera::GetProjection()const
{
	return projection;
}

/**
* @brief �r���[�s��ƃv���W�F�N�V�����s����������s��̎擾
* @return �r���[�s��ƃv���W�F�N�V�����s����������s��
*/
Matrix Camera::GetViewMulProjection()const
{
	return view_mul_projection;
}

/**
* @brief �����x�N�g���̃Q�b�^
* @return �����x�N�g��
*/
Vec3 Camera::GetForward()const
{
	return forward_vector;
}

/**
* @brief �����x�N�g���̃Z�b�^
* @param camera_forward_vector �V���������x�N�g��
*/
void Camera::SetForward(const Vec3& camera_forward_vector)
{
	//������0,0,0�̏ꍇ�͉����������Ȃ�
	if (camera_forward_vector == Vec3{})return;
	forward_vector = camera_forward_vector;
	forward_vector.normalize();
}

/**
* @brief �������ʒu��������x�N�g�����Z�b�g����
* @param look_at �������ʒu
*/
void Camera::LookAt(const Vec3& look_at)
{
	//�������ʒu�ƃJ�����̈ʒu�������ꍇ�͉����������Ȃ�
	if (look_at == pos)return;
	Camera::getinstance()->SetForward(look_at - pos);
}

/**
* @brief �ʒu�̃Q�b�^
* @return �ʒu
*/
Vec3 Camera::GetPos()const
{
	return pos;
}

/**
* @brief �ʒu�̃Z�b�^
* @param _pos �V�����J�����̈ʒu
*/
void Camera::SetPos(const Vec3& camera_pos)
{
	pos = camera_pos;
}

/**
* @brief �J������z����]�̃Q�b�^
* @return �J������z����]
*/
float Camera::GetRotZ()const
{
	return rot_z;
}

/**
* @brief �J������z����]�̃Z�b�^
* @param camera_rot_z �V�����J������z����]
*/
void Camera::SetRotZ(const float camera_rot_z)
{
	rot_z = camera_rot_z;
}

#pragma endregion

#pragma region private

/**
* @brief �s��̍X�V
*/
void Camera::MatrixUpdate()
{
	Vector vec_pos{ pos.x,pos.y,pos.z };
	Vector vec_look_at = DirectX::XMVectorAdd(vec_pos, { forward_vector.x, forward_vector.y, forward_vector.z });
	//�r���[�s��
	view = DirectX::XMMatrixLookAtLH(vec_pos, vec_look_at, { 0.0f,1.0f,0.0f });
	//�v���W�F�N�V�����s��
	projection = DirectX::XMMatrixPerspectiveFovLH(
		fov, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
		NEAR_Z, FAR_Z);
	//2D�p�̃v���W�F�N�V����
	//projection = DirectX::XMMatrixOrthographicLH(
	//	static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT), NEAR_Z, FAR_Z);
	//�r���[�ƃv���W�F�N�V�����s���������(Z����]���l��)
	view_mul_projection = view * DirectX::XMMatrixRotationRollPitchYaw(0, 0, rot_z) * projection;
}

#pragma endregion