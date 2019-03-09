/**
* @file multiple_separation.h
* @brief 区切り文字を一つでも複数でも選択できるようにする
* @author 石山 悠
* @date 2018/12/23
*/
#pragma once
#ifndef SAKI_SPLIT_DETAILS_MULTIPLE_SEPARATION_2018_12_23
#define SAKI_SPLIT_DETAILS_MULTIPLE_SEPARATION_2018_12_23
#include <vector>

namespace saki
{
	/**
	* @brief split関数で利用する、区切り文字を複数指定できるクラス
	*/
	class MultipleSeparation
	{
		//区切り文字を格納
		std::vector<char> separation_list;
	public:
		/**
		* @brief コンストラクタ
		* @param t 区切り文字
		*/
		template<typename ...T>
		explicit MultipleSeparation(const T& ...t) :
			separation_list({ t... })
		{}

		/**
		* @brief 渡された引数が区切り文字かチェックする
		* @param c 判定する文字
		* @details bool check(char)という形にしなけらばならない
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