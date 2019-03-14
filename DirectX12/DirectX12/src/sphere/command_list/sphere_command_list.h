/**
* @file sphere_command_list.h
* @brief �X�t�B�A�p�̃R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief �X�t�B�A�p�̃R�}���h���X�g�N���X
*/
class SphereCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};