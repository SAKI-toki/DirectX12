/**
* @file static_model_command_list.h
* @brief �A�j���[�V�����Ȃ��̃��f���̃R�}���h���X�g�N���X
* @author �ΎR�@�I
* @date 2019/02/08
*/
#pragma once
#include "../../../command_list/Execute/execute_command_list.h"

/**
* @brief �A�j���[�V�����Ȃ��̃��f���̃R�}���h���X�g�N���X
*/
class StaticModelCommandList :public ExecuteCommandList
{
protected:
	HRESULT CreatePipeline()override;
};