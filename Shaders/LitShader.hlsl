struct VS_IN
{
	float4 pos : POSITION;
    float4 tex : TEXCOORD0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 tex : TEXCOORD0;
};

struct ConstantData
{
    matrix WorldViewProjection;
};

cbuffer ConstantBuffer : register(b0)
{
    ConstantData cdata;
}

Texture2D txDiffuse : register(t0);
SamplerState sampl : register(s0);

PS_IN VSMain( VS_IN input)
{
	PS_IN output = (PS_IN)0;
    output.pos = mul(input.pos, cdata.WorldViewProjection);
    output.tex = input.tex;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
    float4 col = 1;
    col *= txDiffuse.Sample(sampl, input.tex.xy);
	return col;
}