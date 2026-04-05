static const float2 positions[3] = {
  float2(0.0, -0.5),
  float2(0.5, 0.5),
  float2(-0.5, 0.5)
};

struct VSOutput
{
  float4 Pos : SV_POSITION;
};

[shader("vertex")]
VSOutput VSMain(uint VertexIndex: SV_VertexID)
{
  VSOutput output = (VSOutput)0;
  output.Pos = float4(positions[VertexIndex], 0.0, 1.0);
  return output;
}

[shader("pixel")]
float4 PSMain() : SV_TARGET
{
  return float4(1.0, 0.0, 0.0, 1.0);
}
