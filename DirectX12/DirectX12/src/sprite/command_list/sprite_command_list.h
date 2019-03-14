/**
* @file sprite_command_list.h
* @brief スプライト用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief スプライト用のコマンドリストクラス
*/
class SpriteCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};