/**
* @file cube_command_list.h
* @brief キューブ用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/11
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"

/**
* @brief キューブ用のコマンドリストクラス
*/
class CubeCommandList :public ExecuteCommandList
{
protected:
	HRESULT CreatePipeline()override;
};