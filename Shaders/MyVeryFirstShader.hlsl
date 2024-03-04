struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

struct MatrixData
{
    matrix world;
    matrix view;
    matrix projection;
};

cbuffer TransformBuffer : register(b0)
{
    MatrixData mat;
}

PS_IN VSMain( VS_IN input)
{
	PS_IN output = (PS_IN)0;
    output.pos = mul(input.pos, mat.world);
    output.pos = mul(output.pos, mat.view);
    output.pos = mul(output.pos, mat.projection);
	output.col = input.col;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col;
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif
	return col;
}