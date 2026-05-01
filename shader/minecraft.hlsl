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
  float4 Texture : TEXCOORD0;
};

struct Scene
{
  column_major float4x4 Projection;
  column_major float4x4 View;
  column_major float4x4 ShadowProjection;
  column_major float4x4 ShadowView;
  float4 LightPosition; // view space
};

// set 0: per-frame
[[vk::binding(0, 0)]] ConstantBuffer<Scene> Scene;

// set 1: constant
[[vk::binding(0, 1)]] SamplerState LinearSampler;
[[vk::binding(1, 1)]] Texture2DArray ShadowTexture;
[[vk::binding(2, 1)]] Texture2D TerrainTexture;

float2 yf(float2 v, float scale)
{
  return float2(v.x, 1.0 - v.y) * scale;
}

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  float4 Position = float4(input.Position.xyz + input.BlockPosition, 1.0);
  output.Position = mul(Scene.Projection, mul(Scene.View, Position.xzyw));

  float2 textureOffset = float2(input.TextureID % 8, input.TextureID / 8) * 16;
  output.Texture = float4(yf(input.Texture.xy, 16), textureOffset);
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float2 texture = input.Texture.xy + input.Texture.zw;
  float4 color = TerrainTexture.Load(int3(texture, 0)).xyzw;

  return float4(color.xyz, 1);
}
