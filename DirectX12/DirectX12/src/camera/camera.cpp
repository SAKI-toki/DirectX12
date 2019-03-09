/**
* @file camera.cpp
* @brief �J�����N���X�̊֐���`
* @author �ΎR�@�I
* @date 2019/02/08
*/
#include "camera.h"
#include "../common/window_size.h"

/**
* @brief �J�����̏�����
*/
void Camera::Init()
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
* @brief �s��̍X�V
*/
void Camera::MatrixUpdate()
{
	view = DirectX::XMMatrixLookAtLH(pos, lookat, up);
	projection = DirectX::XMMatrixPerspectiveFovLH(
		fov, static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
		NEAR_Z, FAR_Z);
	view_mul_projection = view * projection;
}

/**
* @brief �ʒu�̃Q�b�^
* @return �ʒu
*/
Vector Camera::GetPos()const
{
	return pos;
}

/**
* @brief �ʒu�̃Z�b�^
* @param _pos �V�����J�����̈ʒu
*/
void Camera::SetPos(const Vector& _pos)
{
	pos = _pos;
}

/**
* @brief �����_�̃Q�b�^
* @return �����_
*/
Vector Camera::GetLookAt()const
{
	return lookat;
}

/**
* @brief �����_�̃Z�b�^
* @param _lookat �V���������_
*/
void Camera::SetLookAt(const Vector& _lookat)
{
	lookat = _lookat;
}