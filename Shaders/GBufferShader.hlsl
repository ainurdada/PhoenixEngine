struct VS_IN
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : WORLD_NORMAL;
    float2 tex : TEXCOORD;
};

struct GBuffer
{
    float4 DiffuseColor : SV_Target0;
    //float3 Normal : SV_Target1;
    //float3 Specular : SV_Target2;
    //float Depth : SV_Target3;
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

Texture2D txDiffuse : register(t0);
SamplerState sampl : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    output.pos = mul(float4(input.Position, 1), cdata.WorldViewProjection);
    output.tex = input.TexCoord;
    output.normal = normalize(mul(float4(input.Normal, 0), cdata.World).xyz);
    return output;
}

GBuffer PSMain(PS_IN input)
{
    GBuffer output = (GBuffer) 0;
    float4 texColor = txDiffuse.Sample(sampl, input.tex);
    output.DiffuseColor = texColor;
    return output;
}