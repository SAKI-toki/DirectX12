/**
* @file multiple_separation.h
* @brief ��؂蕶������ł������ł��I���ł���悤�ɂ���
* @author �ΎR �I
* @date 2018/12/23
*/
#pragma once
#ifndef SAKI_SPLIT_DETAILS_MULTIPLE_SEPARATION_2018_12_23
#define SAKI_SPLIT_DETAILS_MULTIPLE_SEPARATION_2018_12_23
#include <vector>

namespace saki
{
	/**
	* @brief split�֐��ŗ��p����A��؂蕶���𕡐��w��ł���N���X
	*/
	class MultipleSeparation
	{
		//��؂蕶�����i�[
		std::vector<char> separation_list;
	public:
		/**
		* @brief �R���X�g���N�^
		* @param t ��؂蕶��
		*/
		template<typename ...T>
		explicit MultipleSeparation(const T& ...t) :
			separation_list({ t... })
		{}

		/**
		* @brief �n���ꂽ��������؂蕶�����`�F�b�N����
		* @param c ���肷�镶��
		* @details bool check(char)�Ƃ����`�ɂ��Ȃ���΂Ȃ�Ȃ�
		*/
		bool check(const char c)
		{
			for (auto separation : separation_list)
			{
				if (separation == c)return true;
			}
			return false;
		}
	};
}
#endif //SAKI_SPLIT_DETAILS_MULTIPLE_SEPARATION_2018_12_23