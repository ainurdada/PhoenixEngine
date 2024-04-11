struct VS_IN
{
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float4 tex : TEXCOORD0;
};
struct VS_OUT
{
    float4 pos : SV_POSITION;
};

struct ConstantData
{
    matrix WorldViewProjection;
    matrix World;
    float4 ViewerPos;
};
cbuffer ConstantBuffer : register(b0)
{
    ConstantData cdata;
}

VS_OUT VSMain(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = mul(input.pos, cdata.WorldViewProjection);
    output.pos = float4(0.f, 0.f, 0.5f, 1);
    //output.pos.z = output.pos.z / output.pos.w;
    return output;
}

float4 PSMain(VS_OUT input) : SV_Target
{
    float depth = input.pos.z / input.pos.w;
    return float4(0, 0, 0, 1);
}

//RasterizerState Depth
//{
//    DepthBias = 10000;
//    DepthBiasClamp = 0.0f;
//    SlopeScaledDepthBias = 1.0f;
//};