#pragma once
#include "d3d12.h"
#include "window_size.h"

constexpr D3D12_RECT scissor_rect[1] = 
{
	{ 0,0,static_cast<LONG>(WINDOW_WIDTH),static_cast<LONG>(WINDOW_HEIGHT) }
};
constexpr D3D12_VIEWPORT viewport[1] = 
{
	{ 0.0f,0.0f,WINDOW_WIDTH,WINDOW_HEIGHT,0.0f,1.0f }
};