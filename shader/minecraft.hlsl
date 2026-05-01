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
  float4 WorldPosition : WorldPosition;
  float3 Normal : NORMAL0;
  float4 Texture : TEXCOORD0;
};

struct Scene
{
  column_major float4x4 Projection;
  column_major float4x4 View;
  column_major float4x4 ShadowProjection;
  column_major float4x4 ShadowView;
  float4 LightPosition; // world space
};

// set 0: per-frame
[[vk::binding(0, 0)]] ConstantBuffer<Scene> Scene;

// set 1: constant
[[vk::binding(0, 1)]] SamplerState ClosestSampler;
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
  float4 Position = float4(input.Position.xyz + input.BlockPosition, 1.0).xzyw;
  output.WorldPosition = Position;
  output.Position = mul(Scene.Projection, mul(Scene.View, Position));
  output.Normal = input.Normal;

  float2 textureOffset = float2(input.TextureID % 8, input.TextureID / 8) * 16;
  output.Texture = float4(yf(input.Texture.xy, 16), textureOffset);
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float2 texture = input.Texture.xy + input.Texture.zw;
  //float4 color = TerrainTexture.Load(int3(texture, 0));
  float4 color = TerrainTexture.Sample(ClosestSampler, texture * 0.0078125);

  if (color.w < 0.5)
    discard;

  float3 light_direction = normalize(Scene.LightPosition.xzy + float3(0, 100, 0) - input.WorldPosition.xyz);
  float diffuse = max(dot(input.Normal, light_direction), 0.0);

  return float4(color.xyz * max(0.1, diffuse), 1.0);
}
