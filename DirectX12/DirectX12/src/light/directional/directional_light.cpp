#include "directional_light.h"

DirectionalLight::DirectionalLight() :
	vector(0.0f, 5.0f, -10.0f, 0.0f)
{}


Float4 DirectionalLight::GetVector()const
{
	return vector;
}

void DirectionalLight::SetVector(const Float4& vec)
{
	vector = vec;
}