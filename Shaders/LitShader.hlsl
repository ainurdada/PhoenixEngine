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

struct MaterialData
{
    float Ka;
    float SpecPow;
    float Ks;
    float X;
};
cbuffer DirLightBuffer : register(b1)
{
    MaterialData material;
}

struct DirLightData
{
    float3 direction;
    float intensity;
};
cbuffer DirLightBuffer : register(b2)
{
    DirLightData dirLight;
}

struct PointLightData
{
    float4x4 viewProjection;
    float3 color;
    float intensity;
    float3 position;
    float attenuation_a;
    float attenuation_b;
    float attenuation_c;
};
cbuffer PointLightBuffr : register(b3)
{
    PointLightData pointLight;
}


Texture2D txDiffuse : register(t0);
Texture2D pointLightShadowMap : register(t1);
SamplerState sampl : register(s0);
SamplerComparisonState samplerClamp : register(s1);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    output.pos = mul(input.pos, cdata.WorldViewProjection);
    output.tex = input.tex;
    output.normal = normalize(mul(input.normal, cdata.World).xyz);
    output.worldPos = mul(input.pos, cdata.World);
    
    return output;
}

//float vectorToDepth(float3 vec, float n, float f)
//{
//    float3 AbsVec = abs(vec);
//    float LocalZcomp = max(AbsVec.x, max(AbsVec.y, AbsVec.z));

//    float NormZComp = (f + n) / (f - n) - (2 * f * n) / (f - n) / LocalZcomp;
//    return (NormZComp + 1.0) * 0.5;
//}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 diffVal = txDiffuse.Sample(sampl, input.tex.xy);
    clip(diffVal.a - 0.01f);
    
    float3 kd = diffVal.xyz;
    float3 ambient = material.Ka * kd;
    
    // directional light
    float3 viewDir = normalize(cdata.ViewerPos.xyz - input.worldPos.xyz);
    float3 lightDir = -dirLight.direction;
    float3 refVec = normalize(reflect(lightDir, input.normal));
    
    float3 diffuse = kd * dirLight.intensity * max(0, dot(input.normal, lightDir));
    float3 spec = pow(max(0, dot(-viewDir, refVec)), material.SpecPow) * dirLight.intensity * material.Ks;
    
    float4 col = float4(diffuse + spec + ambient, 1);
    
    // point light
    float4 posInPointLightView = mul(float4(input.worldPos.xyz,1), pointLight.viewProjection);
    posInPointLightView.z = -posInPointLightView.z;
    posInPointLightView.w = -posInPointLightView.w;
    float2 shadowTexCoord = float2
    (
        -posInPointLightView.x / posInPointLightView.w / 2.0f + 0.5f,
        posInPointLightView.y / posInPointLightView.w / 2.0f + 0.5f
    );
    if ((saturate(shadowTexCoord.x) == shadowTexCoord.x) && (saturate(shadowTexCoord.y) == shadowTexCoord.y))
    {
        // compare depth
        float lightDepth = posInPointLightView.z / posInPointLightView.w - 0.001f;
        float depth = pointLightShadowMap.SampleCmp(samplerClamp, shadowTexCoord,lightDepth);
        //return float4(depth, 0, 0, 1);
        if (depth)
        {
            float distanceToLight = distance(pointLight.position, input.worldPos.xyz);
            float attenuationFactor =
            1 /
            (
                pointLight.attenuation_a 
                + pointLight.attenuation_b * distanceToLight
                + pointLight.attenuation_c * distanceToLight * distanceToLight
            );
            lightDir = normalize(pointLight.position - input.worldPos.xyz);
            refVec = normalize(reflect(lightDir, input.normal));
    
            diffuse = attenuationFactor * kd * pointLight.intensity * max(0, dot(input.normal, lightDir));
            spec = pow(max(0, dot(-viewDir, refVec)), material.SpecPow) * pointLight.intensity * material.Ks * attenuationFactor;
    
            col += float4(pointLight.color, 1) * float4(diffuse + spec, 0);
        }
    }
    return col;
}