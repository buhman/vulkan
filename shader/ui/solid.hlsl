struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
  // per-instance
  int2 InstancePosition : InstancePosition;
  int2 InstanceSize : InstanceSize;
  float4 Color : Color;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : Texture;
  float4 Color : Color;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  float2 inversePixel = float2(1.0 / 1280.0, 1.0 / 720.0);

  float2 position = (input.Texture * input.InstanceSize + input.InstancePosition) * inversePixel;

  VSOutput output = (VSOutput)0;
  output.Position = float4(position * 2.0 - 1.0, 0, 1);
  output.Texture = input.Texture;
  output.Color = input.Color.zyxw;

  return output;
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  //return float4(input.Texture, 0, 1);
  return float4(input.Color.xyzw);
}
