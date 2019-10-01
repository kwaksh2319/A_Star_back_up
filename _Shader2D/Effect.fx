cbuffer CB_PerFrame
{
	matrix View;
	matrix Projection;
}
matrix World;



//-----------------------------------------------------------------------------
//Structures
//-----------------------------------------------------------------------------
struct VertexInput
{
	float4 Position : POSITION0;
    float2 UV : UV0;
};

struct VertexOutput
{
	float4 Position : SV_POSITION0;
    float2 UV : UV0;
};

//-----------------------------------------------------------------------------
//Vertex Shader
//-----------------------------------------------------------------------------
VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.Position = mul(input.Position, World); //����->����������� ��ȯ
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	output.UV= input.UV;

	return output;
}

//-----------------------------------------------------------------------------
//Pixel Shader
//-----------------------------------------------------------------------------
Texture2D Map; //uv shader
SamplerState Sampler;

float4 PS(VertexOutput input) : SV_TARGET0
{
    return Map.Sample(Sampler, input.UV);
}
//-----------------------------------------------------------------------------
//Blend state
//-----------------------------------------------------------------------------
RasterizerState Cull
{
    CullMode = None; //�ݽð� ���⵵ ���̰� ����
    DepthClipEnable = false;//z������ �и��� �κ��� �׷���

};

BlendState AlphaBlend 
{
    AlphaToCoverageEnable = false; //���
    BlendEnable[0] = true; //������ Ȱ��ȭ
    DestBlend[0] = INV_SRC_ALPHA; // ���� �����̻��� ���ֹ��� 
    SrcBlend[0] = SRC_ALPHA;//
    BlendOp[0] = Add;//

    SrcBlendAlpha[0] = One;//
    DestBlendAlpha[0] = One;//
    RenderTargetWriteMask[0] = 0x0F;//
};

//-----------------------------------------------------------------------------
//Technique
//-----------------------------------------------------------------------------
technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
        SetRasterizerState(Cull);
        SetBlendState(AlphaBlend, float4(0, 0, 0, 0), 0xFF);
        
    }

}
