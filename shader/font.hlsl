struct GlyphBitmap
{
  uint2 Position; // x y, in texels
  uint2 Size; // width height
};

// set 0: constant
[[vk::binding(0, 0)]] SamplerState ClosestSampler;
[[vk::binding(1, 0)]] Texture2D FontTexture;
[[vk::binding(2, 0)]] StructuredBuffer<GlyphBitmap> Glyphs;

struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
  // per-instance
  uint2 InstancePosition : InstancePosition;
  uint InstanceGlyph : InstanceGlyph;
  float4 InstanceColor : InstanceColor;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : NORMAL0;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  float2 inverseTexel = float2(1.0 / 256.0, 1.0 / 256.0);
  float2 inversePixel = float2(1.0 / 1280.0, 1.0 / 720.0);
  int index = input.InstanceGlyph;

  VSOutput output = (VSOutput)0;
  float2 position = (input.Texture * Glyphs[index].Size + input.InstancePosition) * inversePixel;
  output.Position = float4(position * 2.0 - 1.0, 0, 1);
  output.Texture = (input.Texture * Glyphs[index].Size + Glyphs[index].Position) * inverseTexel;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float4 color = FontTexture.Sample(ClosestSampler, input.Texture);
  return float4(color.xxx, 1.0);
}
