/**
* @file cube_command_list.h
* @brief キューブ用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/11
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief キューブ用のコマンドリストクラス
*/
class CubeCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};