struct VS_IN
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
    float4 TexCoord : TEXCOORD0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 worldPos : WORLD_POS;
    float3 normal : WORLD_NORMAL;
    float2 tex : TEXCOORD;
};

struct GBuffer
{
    float4 DiffuseColor : SV_Target0;
    float4 WorldPos : SV_Target1;
    float3 Normal : SV_Target2;
    float3 Specular : SV_Target3;
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

struct MaterialData
{
    float Ka;
    float SpecPow;
    float Ks;
};
cbuffer MaterialBuffer : register(b1)
{
    MaterialData material;
}

Texture2D txDiffuse : register(t0);
SamplerState sampl : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    output.pos = mul(input.Position, cdata.WorldViewProjection);
    output.worldPos = mul(input.Position, cdata.World);
    output.tex = input.TexCoord.xy;
    output.normal = normalize(mul(input.Normal, cdata.World).xyz);
    return output;
}

GBuffer PSMain(PS_IN input)
{
    GBuffer output = (GBuffer) 0;
    float4 texColor = txDiffuse.Sample(sampl, input.tex);
    output.DiffuseColor = texColor;
    output.WorldPos = input.worldPos;
    input.normal = normalize(input.normal);
    output.Normal = input.normal;
    output.Specular = float3(material.Ka, material.SpecPow, material.Ks);
    return output;
}