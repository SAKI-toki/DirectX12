/**
* @file sphere_command_list.h
* @brief スフィア用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"

/**
* @brief スフィア用のコマンドリストクラス
*/
class SphereCommandList :public ExecuteCommandList
{
protected:
	HRESULT CreatePipeline()override;
};