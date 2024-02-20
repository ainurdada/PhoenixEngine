#pragma once
class MeshComponent;

#include <vector>

#include "Graphics.h"
#include "GameComponent.h"
#include "MathEngine.h"

class MeshComponent : public GameComponent
{
public:
	MeshComponent(const Graphics& graphics, const std::vector<Vec4>& points, const std::vector<int>& indexes);
	ID3D11Buffer* VB();
	ID3D11Buffer* IB();
public:
	// Inherited via GameComponent
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Reload() override;
	void Update() override;
private:
	std::vector<DirectX::XMFLOAT4> points;
	std::vector<int> indexes;
	ID3D11Buffer* vb; 
	ID3D11Buffer* ib;
};

