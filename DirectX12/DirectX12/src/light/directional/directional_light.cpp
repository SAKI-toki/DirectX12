#include "directional_light.h"

DirectionalLight::DirectionalLight() :
	vector(0.0f, 40.0f, -70.0f, 1.0f)
{}


Float4 DirectionalLight::GetVector()const
{
	return vector;
}

void DirectionalLight::SetVector(const Float4& vec)
{
	vector = vec;
}