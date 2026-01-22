

typedef struct dimensions
{
    int width;
    int height;
}dimensions;
enum Shape{
    TRIANGLE,
    RECTANGLE
};
static const float verticesTri[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f 
};
static const float verticesRect[] = {
     0.5f,  0.5f, 0.0f, 
     0.5f, -0.5f, 0.0f, 
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

