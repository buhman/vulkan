[[vk::binding(0, 0)]] SamplerState ClosestSampler;
[[vk::binding(1, 0)]] Texture2D Texture[];

struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
  // per-instance
  uint2 Size : Size;
  uint2 TopLeft : TopLeft;
  uint TextureIndex : TextureIndex;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : NORMAL0;
  uint TextureIndex : TextureIndex;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  output.Position = float4(input.Position, 0, 1);
  output.Texture = input.Texture;
  output.TextureIndex = input.TextureIndex;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float4 color = Texture[input.TextureIndex].Sample(ClosestSampler, input.Texture);
  return float4(color.xyz, 1.0);
}
