[[vk::binding(0, 0)]] SamplerState ClosestSampler;
[[vk::binding(1, 0)]] Texture2D Texture[];

struct VSInput
{
  float2 Position : POSITION0;
  float2 Texture : TEXCOORD0;
  // per-instance
  int2 Size : Size;
  int2 TopLeft : TopLeft;
  float4 Color : Color;
  int TextureIndex : TextureIndex;
};

struct VSOutput
{
  float4 Position : SV_POSITION;
  float2 Texture : NORMAL0;
  float4 Color : Color;
  int TextureIndex : TextureIndex;
};

[shader("vertex")]
VSOutput VSMain(VSInput input)
{
  float2 inversePixel = float2(1.0 / 1280.0, 1.0 / 720.0);

  float2 size = abs(input.Size);
  float2 texture = float2(input.Size.x < 0 ? 1.0 - input.Texture.x : input.Texture.x,
                          input.Size.y < 0 ? 1.0 - input.Texture.y : input.Texture.y);

  VSOutput output = (VSOutput)0;
  float2 position = (input.Texture * size + input.TopLeft) * inversePixel;
  output.Position = float4(position * 2.0 - 1.0, 0, 1);
  output.Texture = texture;
  output.TextureIndex = input.TextureIndex;
  output.Color = input.Color.zyxw;

  return output;
}

float4 PSGradient1(VSOutput input) : SV_TARGET
{
  float a = smoothstep(0.05, 0.2, input.Texture.x);
  float b = 1.0 - smoothstep(0.8, 0.95, input.Texture.x);
  float c = smoothstep(0.05, 0.2, input.Texture.y);
  float d = a * b * c * input.Color.w;
  float3 color = input.Color.xyz;
  return float4(color, d);
}

float4 PSGradient2(VSOutput input) : SV_TARGET
{
  float a = smoothstep(0.05, 0.2, input.Texture.x);
  float b = 1.0 - smoothstep(0.8, 0.95, input.Texture.x);
  float d = a * b * input.Color.w;
  float3 color = input.Color.xyz;
  return float4(color, d);
}

float4 PSGradient3(VSOutput input) : SV_TARGET
{
  float a = smoothstep(0.02, 0.1, input.Texture.x);
  float b = 1.0 - smoothstep(0.9, 0.98, input.Texture.x);
  float d = a * b * input.Color.w;
  float3 color = input.Color.xyz;
  return float4(color, d);
}

[shader("pixel")]
float4 PSMain(VSOutput input) : SV_TARGET
{
  float4 color;
  if (input.TextureIndex >= 0) {
    color = Texture[input.TextureIndex].Sample(ClosestSampler, input.Texture);
  } else if (input.TextureIndex == -1) {
    color = float4(input.Color.xyz, 1.0);
  } else if (input.TextureIndex == -2) {
    return PSGradient1(input);
  } else if (input.TextureIndex == -3) {
    return PSGradient2(input);
  } else if (input.TextureIndex == -4) {
    return PSGradient2(input);
  } else {
    return float4(1, 0, 0, 1);
  }

  if (color.w == 0.0)
    discard;

  float gamma = 2.2;
  color.xyz = pow(color.xyz, float3(gamma.xxx));

  return float4(color.xyzw);
}
