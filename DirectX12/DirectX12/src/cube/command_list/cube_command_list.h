/**
* @file cube_command_list.h
* @brief �L���[�u�p�̃R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/03/11
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief �L���[�u�p�̃R�}���h���X�g�N���X
*/
class CubeCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};