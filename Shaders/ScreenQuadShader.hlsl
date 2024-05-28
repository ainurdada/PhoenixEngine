
struct PS_IN
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD;
};

struct ConstantData
{
    float4x4 InverseProjection;
    float4x4 InverseView;
    float4 ViewerPos;
    float4 ViewDirection;
    int2 screenResolution;
    float nearPlaneDistance;
    float fov;
};
cbuffer ConstantBuffer : register(b0)
{
    ConstantData cdata;
}

struct PointLightData
{
    float4x4 viewProjection[6];
    float3 color;
    float intensity;
    float3 position;
    float attenuation_a;
    float attenuation_b;
    float attenuation_c;
};
cbuffer PointLightBuffer : register(b1)
{
    PointLightData pointLight;
}

Texture2D<float4> DiffuseTex : register(t0);
Texture2D<float> Depth : register(t1);
Texture2D<float4> NormalTex : register(t2);
Texture2D<float3> SpecularTex : register(t3);

Texture2D pointLightShadowMap[6] : register(t4);
SamplerComparisonState samplerClamp : register(s0);

static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;
float CalcShadowFactor(SamplerComparisonState samShadow,
                       Texture2D shadowMap,
                       float2 TexPos,
                       float depth)
{
    // Texel size.
    const float dx = SMAP_DX;

    float percentLit = 0.0f;
    const float2 offsets[9] =
    {
        float2(-dx, -dx), float2(0.0f, -dx), float2(dx, -dx),
        float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
        float2(-dx, +dx), float2(0.0f, +dx), float2(dx, +dx)
    };
    
    [unroll]
    for (int i = 0; i < 9; ++i)
    {
        percentLit += shadowMap.SampleCmpLevelZero(samShadow,
            TexPos + offsets[i], depth).r;
    }

    return percentLit /= 9.0f;
}

float3 doLigt(float3 position, float3 normal, float3 color, PointLightData pointLight, float AmbientKoef, float SpecularPower, float SpecularKoef)
{
    float3 ambient = AmbientKoef * color;
    float3 col = ambient;
    [unroll]
    for (int i = 0; i < 6; i++)
    {
        float4 posInPointLightView = mul(float4(position, 1), pointLight.viewProjection[i]);
        float2 shadowTexCoord = float2
        (
            posInPointLightView.x / posInPointLightView.w / 2.0f + 0.5f,
            -posInPointLightView.y / posInPointLightView.w / 2.0f + 0.5f
        );
        float lightDepth = posInPointLightView.z / posInPointLightView.w;
        if ((saturate(shadowTexCoord.x) == shadowTexCoord.x) && (saturate(shadowTexCoord.y) == shadowTexCoord.y) && lightDepth >= 0)
        {
            float distanceToLight = distance(pointLight.position, position);
            float attenuationFactor =
                    1 /
                    (
                        pointLight.attenuation_a 
                        + pointLight.attenuation_b * distanceToLight
                        + pointLight.attenuation_c * distanceToLight * distanceToLight
                    );
            float3 lightDir = normalize(pointLight.position - position);
            float3 refVec = normalize(reflect(lightDir, normal));
    
            float3 diffuse = attenuationFactor * color * pointLight.intensity * max(0, dot(normal, lightDir));
            if (diffuse.x || diffuse.y || diffuse.z)
            {
                    // compare depth
                float shadowFactor = CalcShadowFactor(samplerClamp, pointLightShadowMap[i], shadowTexCoord, lightDepth);
                float3 viewDir = normalize(cdata.ViewerPos.xyz - position);
                float3 spec = pow(max(0, dot(-viewDir, refVec)), SpecularPower) * pointLight.intensity * SpecularKoef * attenuationFactor;
                col += shadowFactor * pointLight.color * (diffuse + spec);
            }
        }
    }
    return col;
}

PS_IN VSMain(uint id : SV_VertexID)
{
    PS_IN output = (PS_IN) 0;
    output.TexCoord = float2(id & 1, (id & 2) >> 1);
    output.Position = float4(output.TexCoord * float2(2, -2) + float2(-1, 1), 0, 1);
    return output;
}

float3 CalculateWorldPosition(float4 screenPosition)
{
    float2 texCoord = screenPosition.xy / cdata.screenResolution;
    float4 clip = float4(float2(texCoord.x, 1.0f - texCoord.y) * 2.0f - 1.0f, screenPosition.z, screenPosition.w);
    float4 view = mul(clip, cdata.InverseProjection);
    view = view / view.w;
    float4 world = mul(view, cdata.InverseView);
    return world.xyz;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 diffuse = DiffuseTex.Load(input.Position.xyz);
    float4 normal = NormalTex.Load(input.Position.xyz);
    float3 specular = SpecularTex.Load(input.Position.xyz);
    float depth = Depth.Load(input.Position.xyz);
    
    float3 position = CalculateWorldPosition(float4(input.Position.xy, depth, 1.0f));
    //return float4(position, 1);
  
    float3 color = doLigt(position, normal.xyz, diffuse.rgb, pointLight, specular.x, specular.y, specular.z);
    
    return float4(color, 1);
}