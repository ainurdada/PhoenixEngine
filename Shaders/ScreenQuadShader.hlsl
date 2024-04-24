
struct PS_IN
{
    float4 Position : SV_Position;
    float2 TexCoord : TEXCOORD;
};

struct ConstantData
{
    float3 ViewerPos;
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
Texture2D<float4> WorldPos : register(t1);
Texture2D<float4> NormalTex : register(t2);
Texture2D<float> DepthTex : register(t3);
Texture2D<float3> SpecularTex : register(t4);

float3 doLigt(float3 position, float3 normal, float3 color, PointLightData pointLight, float AmbientKoef, float SpecularPower, float SpecularKoef)
{
    float3 ambient = AmbientKoef * color;
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
    float3 viewDir = normalize(cdata.ViewerPos.xyz - position);
    float3 spec = pow(max(0, dot(-viewDir, refVec)), SpecularPower) * pointLight.intensity * SpecularKoef * attenuationFactor;
    
    float3 col = pointLight.color * (ambient + diffuse + spec);
    return col;
}

PS_IN VSMain(uint id : SV_VertexID)
{
    PS_IN output = (PS_IN)0;
    output.TexCoord = float2(id & 1, (id & 2) >> 1);
    output.Position = float4(output.TexCoord * float2(2, -2) + float2(-1, 1), 0, 1);
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 diffuse = DiffuseTex.Load(input.Position.xyz);
    float4 normal = NormalTex.Load(input.Position.xyz);
    float3 specular = SpecularTex.Load(input.Position.xyz);
    float4 position = WorldPos.Load(input.Position.xyz);
    float depth = DepthTex.Load(input.Position.xyz);
    
    float3 color = doLigt(position.xyz, normal.xyz, diffuse.rgb, pointLight, specular.x, specular.y, specular.z);
    
    return float4(color, 1);
}