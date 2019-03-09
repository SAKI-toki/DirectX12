/**
* @file not_equal_separation.h
* @brief ��؂�Ȃ�������I������
* @author �ΎR �I
* @date 2018/12/23
*/
#pragma once
#ifndef SAKI_SPLIT_DETAILS_NOT_EQUAL_SEPARATION_2018_12_23
#define SAKI_SPLIT_DETAILS_NOT_EQUAL_SEPARATION_2018_12_23
#include <vector>

namespace saki
{
	/**
	* @brief split�֐��ŗ��p����A��؂�Ȃ��������w��ł���N���X
	*/
	class NotEqualSeparation
	{
		//��؂�Ȃ��������i�[
		std::vector<char> separation_list;
	public:
		/**
		* @brief �R���X�g���N�^
		* @param t ��؂�Ȃ�����
		*/
		template<typename ...T>
		explicit NotEqualSeparation(const T& ...t) :
			separation_list({ t... })
		{}

		/**
		* @brief �n���ꂽ��������؂�Ȃ��������`�F�b�N����
		* @param c ���肷�镶��
		* @details bool check(char)�Ƃ����`�ɂ��Ȃ���΂Ȃ�Ȃ�
		*/
		bool check(const char c)
		{
			for (auto separation : separation_list)
			{
				if (separation == c)return false;
			}
			return true;
		}
	};
}
#endif //SAKI_SPLIT_DETAILS_NOT_EQUAL_SEPARATION_2018_12_23