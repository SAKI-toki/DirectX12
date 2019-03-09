/**
* @file copy.h
* @brief 既存のcopy関数の簡略化
* @author 石山 悠
* @date 2019/01/24
*/
#pragma once
#ifndef SAKI_ALGORITHM_COPY_2019_01_24
#define SAKI_ALGORITHM_COPY_2019_01_24
#include <iterator>
#include <saki/type_traits/enable_if_nullptr.h>
#include <saki/type_traits/can_range_based_for.h>

namespace saki
{
	/**
	* @brief コンテナとコンテナを渡すcopy
	* @param con1 コピーするコンテナクラス
	* @param con2 ペーストするコンテナクラス
	* @details 片方がendになったらコピー終了
	*/
	template <typename Container1, typename Container2,
		typename saki::enable_if_nullptr_t<
		saki::can_range_based_for_v<Container1>&&	//コンテナ1がbegin,end有効か
		saki::can_range_based_for_v<Container2>		//コンテナ2がbegin,end有効か
	> = nullptr>
		constexpr auto copy(const Container1& con1, Container2& con2)
		->decltype(*std::begin(con2) = *std::begin(con1), std::begin(con2))
	{
		auto con1itr = std::begin(con1);
		auto con1end = std::end(con1);
		auto con2itr = std::begin(con2);
		auto con2end = std::end(con2);
		while (con1itr != con1end && con2itr != con2end)
		{
			*con2itr = *con1itr;
			++con1itr; ++con2itr;
		}
		return con2itr;
	}
}
#endif //SAKI_ALGORITHM_COPY_2019_01_24