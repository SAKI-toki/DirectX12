#pragma once
#include "../../common/alias.h"
#include <saki/singleton.h>

class DirectionalLight :public saki::singleton<DirectionalLight>
{
	Float4 vector;
public:
	DirectionalLight();
	Float4 GetVector()const;
	void SetVector(const Float4& vec);
};