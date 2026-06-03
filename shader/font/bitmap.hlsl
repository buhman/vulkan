struct GlyphBitmap
{
  uint2 Position; // x y, in texels
  uint2 Size; // width height
};

// set 0: constant
[[vk::binding(0, 0)]] Texture2D FontTexture;

struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
  // per-instance
  uint2 InstancePosition : InstancePosition;
  uint2 InstanceGlyph : InstanceGlyph;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : NORMAL0;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  //float2 inverseTexel = float2(1.0 / 128.0, 1.0 / 64.0);
  float2 inversePixel = float2(1.0 / 1280.0, 1.0 / 720.0);

  float2 Size = float2(6, 12);

  VSOutput output = (VSOutput)0;
  float2 position = (input.Texture * Size + input.InstancePosition) * inversePixel;
  output.Position = float4(position * 2.0 - 1.0, 0, 1);
  output.Texture = (input.Texture * Size + input.InstanceGlyph * Size);

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float4 color = FontTexture.Load(int3(input.Texture, 0));
  float c = (color.x == 0) ? 0 : 1;

  return float4(1, 1, 1, c.x);
}
