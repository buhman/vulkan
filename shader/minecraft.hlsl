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

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  VSOutput output = (VSOutput)0;
  float4 Position = float4(input.Position.xyz + input.BlockPosition, 1.0);
  output.Position = mul(Scene.Projection, mul(Scene.View, Position));
  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  return float4(1, 0, 0, 1);
}
