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
    //output.pos.z = 0.11f;
    //output.pos.z = output.pos.z / output.pos.w;
    return output;
}

//float4 PSMain(VS_OUT input) : SV_Target
//{
//    float depth = input.pos.z / input.pos.w;
//    return float4(depth, depth, depth, 1);
//}

//RasterizerState Depth
//{
//    DepthBias = 10000;
//    DepthBiasClamp = 0.0f;
//    SlopeScaledDepthBias = 1.0f;
//};