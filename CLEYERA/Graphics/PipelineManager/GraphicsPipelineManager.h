#pragma once
#include"LogManager.h"
#include"DirectXCommon.h"
#include"ShaderManager.h"


struct SPSOProperty
{
	ComPtr<ID3D12PipelineState> GraphicsPipelineState = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature = nullptr;
	ComPtr<ID3DBlob> signatureBlob = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;

};

struct  SBlendPSO
{
	SPSOProperty none;
	SPSOProperty Add;
	SPSOProperty Subtruct;
	SPSOProperty Multiply;
	SPSOProperty Screen;

};


struct SPSO
{
	SPSOProperty shape;
	SPSOProperty Line;
	SBlendPSO Sprite2d;
	SBlendPSO Sprite3d;
	SPSOProperty Herf_Lambert;
};

enum  BlendMode
{
	BlendNone,
	BlendAdd,
	BlendSubtruct,
	BlendMultiply,
	BlendScreen,
};

class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	static void Initialize();
    SPSO GetPso() { return pso; }

private:

	static void CreatePSO(SPSO &pso);
	static void Create2dSpritePSO(SPSO &pso);

	static SPSOProperty CreateShape(ComPtr<ID3D12Device>device,Commands command,SShaderMode shader);
	static SPSOProperty CreateLine(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite3dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateSprite2dNone(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dAdd(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dSubtract(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dMultiply(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);
	static SPSOProperty CreateSprite2dScreen(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	static SPSOProperty CreateHerf_Lambert(ComPtr<ID3D12Device>device, Commands commands, SShaderMode shader);

	SPSO pso = {};

};

