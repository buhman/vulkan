struct VSInput
{
  float3 Position : POSITION0;
  float3 Normal : NORMAL0;
  float2 Texture : TEXCOORD0;
  // per-instance
  int3 BlockPosition : BlockPosition;
  int Blockid : BlockID;
  int Data : Data;
  int TextureID : TextureID;
  int Special : Special;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  output.Position = float4(input.Position.xyz + input.BlockPosition, 1.0);
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  return float4(1, 0, 0, 1);
}
