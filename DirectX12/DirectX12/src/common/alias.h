/**
* @file alias.h
* @brief エイリアス宣言
* @author 石山　悠
* @date 2019/03/06
*/
#pragma once
#define NOMINMAX//min,maxのマクロ関数の定義を回避する
#include <wrl.h>
//スマートポインタ
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#include <DirectXMath.h>
//xmfloat2
using Float2 = DirectX::XMFLOAT2;
//xmfloat3
using Float3 = DirectX::XMFLOAT3;
//xmfloat4
using Float4 = DirectX::XMFLOAT4;
//xmvector
using Vector = DirectX::XMVECTOR;
//xmmatrix
using Matrix = DirectX::XMMATRIX;

#include <saki/vector.h>
//vector2
using Vec2 = saki::vector2<float>;
//vector3
using Vec3 = saki::vector3<float>;
//vector4
using Vec4 = saki::vector4<float>;

#include <saki/transform.h>
//transform
using Transform = saki::transform<float>;