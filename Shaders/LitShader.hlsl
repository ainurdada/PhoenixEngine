struct VS_IN
{
    float4 pos : POSITION;
    float4 normal : NORMAL;
    float4 tex : TEXCOORD0;
};
struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 worldPos : WORLD_POS;
    float3 normal : WORLD_NORMAL;
    float4 tex : TEXCOORD0;
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


struct DirLightData
{
    float3 direction;
    float intensity;
    float4 KaSpecPowKsX;
};
cbuffer DirLightBuffer : register(b1)
{
    DirLightData dirLight;
}

struct PointLightData
{
    float3 position;
    float intensity;
};
cbuffer PointLightBuffr : register(b2)
{
    PointLightData pointLight;
}


Texture2D txDiffuse : register(t0);
SamplerState sampl : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    output.pos = mul(input.pos, cdata.WorldViewProjection);
    output.tex = input.tex;
    output.normal = normalize(mul(input.normal, cdata.World).xyz);
    output.worldPos = mul(input.pos, cdata.World);
    
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 diffVal = txDiffuse.Sample(sampl, input.tex.xy);
    clip(diffVal.a - 0.01f);
    
    float3 kd = diffVal.xyz;
    
    float3 viewDir = normalize(cdata.ViewerPos.xyz - input.worldPos.xyz);
    float3 lightDir = -dirLight.direction;
    float3 refVec = normalize(reflect(lightDir, input.normal));
    
    float3 diffuse = kd * dirLight.intensity * max(0, dot(input.normal, lightDir));
    float3 spec = pow(max(0, dot(-viewDir, refVec)), dirLight.KaSpecPowKsX.y) * dirLight.intensity * dirLight.KaSpecPowKsX.z;
    float3 ambient = dirLight.KaSpecPowKsX.x * kd;
    
    float4 col = float4(diffuse + spec + ambient, 1);
    
    lightDir = normalize(pointLight.position - input.worldPos.xyz);
    refVec = normalize(reflect(lightDir, input.normal));
    
    diffuse = kd * pointLight.intensity * max(0, dot(input.normal, lightDir));
    spec = pow(max(0, dot(-viewDir, refVec)), dirLight.KaSpecPowKsX.y) * pointLight.intensity * dirLight.KaSpecPowKsX.z;
    
    col += float4(diffuse + spec, 1);
    
    return col;
}