/**
* @file singleton.h
* @brief シングルトンクラス
* @author 石山 悠
* @date 2018/10/17
*/
/*
クラスをシングルトンにするとき、このクラスを継承するだけでシングルトンになる
※使い方
class A:public saki::singleton<A>{}
*/
#ifndef SAKI_SINGLETON_SINGLETON_2018_10_17
#define SAKI_SINGLETON_SINGLETON_2018_10_17
#include <memory> //for unique_ptr
namespace saki
{
	/**
	* @brief 継承するとシングルトンクラスになる
	*/
	template<typename T>
	class singleton
	{
	public:
		/**
		* @brief インスタンスを取得
		* @return std::unique_ptr<T> インスタンスを返す
		*/
		static std::unique_ptr<T>& getinstance()
		{
			static auto instance = std::make_unique<T>();
			return instance;
		}

		virtual ~singleton() {}

	protected:
		singleton() {}
	private:
		singleton(const singleton&) = delete;
		singleton& operator=(const singleton&) = delete;
		singleton(singleton&&) = delete;
		singleton& operator=(singleton&&) = delete;
	};
}
#endif //SAKI_SINGLETON_SINGLETON_2018_10_17