/**
* @file static_model_command_list.h
* @brief アニメーションなしのモデルのコマンドリストクラス
* @author 石山　悠
* @date 2019/02/08
*/
#pragma once
#include "../../../command_list/Execute/execute_command_list.h"

/**
* @brief アニメーションなしのモデルのコマンドリストクラス
*/
class StaticModelCommandList :public ExecuteCommandList
{
protected:
	HRESULT CreatePipeline()override;
};