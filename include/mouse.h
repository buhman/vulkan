namespace mouse
{
  void normalize(int windowWidth, int windowHeight, float mx, float my, float * mxf, float * myf)
  {
    int canonicalSizeX = 1280;
    int canonicalSizeY = 720;
    int scaleFactor = 1;
    while (canonicalSizeX * (scaleFactor + 1) <= windowWidth && canonicalSizeY * (scaleFactor + 1) <= windowHeight) {
      scaleFactor += 1;
    }
    float scaleFactorInverse = 1.0f / ((float)scaleFactor);
    int offsetX = (windowWidth - (canonicalSizeX * scaleFactor)) / 2;
    int offsetY = (windowHeight - (canonicalSizeY * scaleFactor)) / 2;
    *mxf = ((float)(mx - offsetX)) * scaleFactorInverse;
    *myf = ((float)(my - offsetY)) * scaleFactorInverse;
  }
}
