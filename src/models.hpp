
typedef struct dimensions
{
    int width;
    int height;
}dimensions;
enum Shape{
    TRIANGLE,
    RECTANGLE,
    CIRCLE
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

class Cursor{
    float x;
    float y;
    float r;
public: 
    Cursor(float X, float Y, float radius): x(X), y(Y), r(radius){};
    Cursor(): x(0.0f), y(0.0f), r(0.1f){};

    float X(){return x;}
    float Y(){return y;}
    void setRadius(float rad){r = rad;}
};