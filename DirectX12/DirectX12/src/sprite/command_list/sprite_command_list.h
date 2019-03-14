/**
* @file sprite_command_list.h
* @brief �X�v���C�g�p�̃R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief �X�v���C�g�p�̃R�}���h���X�g�N���X
*/
class SpriteCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};