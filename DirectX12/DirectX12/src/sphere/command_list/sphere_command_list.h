/**
* @file sphere_command_list.h
* @brief スフィア用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"
#include "../../shader/shader.h"

/**
* @brief スフィア用のコマンドリストクラス
*/
class SphereCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};