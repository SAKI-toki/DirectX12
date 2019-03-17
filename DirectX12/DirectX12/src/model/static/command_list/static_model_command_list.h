#pragma once
#include "../../../command_list/Execute/execute_command_list.h"
#include "../../../shader/shader.h"

class StaticModelCommandList :public ExecuteCommandList
{
	Shader vertex_shader;
	Shader pixel_shader;
protected:
	HRESULT CreatePipeline()override;
};