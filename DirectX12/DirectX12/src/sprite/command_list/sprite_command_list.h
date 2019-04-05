/**
* @file sprite_command_list.h
* @brief スプライト用のコマンドリストクラス
* @author 石山　悠
* @date 2019/03/12
*/
#pragma once
#include "../../command_list/Execute/execute_command_list.h"

/**
* @brief スプライト用のコマンドリストクラス
*/
class SpriteCommandList :public ExecuteCommandList
{
protected:
	HRESULT CreatePipeline()override;
};