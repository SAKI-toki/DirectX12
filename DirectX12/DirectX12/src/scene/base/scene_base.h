#pragma once
#include "../../common/d3d12.h"
#include <memory>
#include <utility>
class SceneBase;
using ScenePtrType = std::shared_ptr<SceneBase>;

class SceneBase
{
public:
	virtual HRESULT Init() = 0;
	virtual ScenePtrType Update(ScenePtrType, HRESULT&) = 0;
	virtual HRESULT Render() = 0;
	virtual HRESULT Destroy() = 0;

	virtual ~SceneBase() {}
};