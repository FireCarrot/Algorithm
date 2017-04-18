#include <iostream>
#include <chrono>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

class Dimension {
public:
    Dimension(int _X, int _Y) { mX = _X; mY = _Y; }
private:
    int mX, mY;
};

class Image {
public:
    virtual void Draw() = 0;
    virtual Dimension GetDimensionInPixels() = 0;
protected:
    int dimensionX;
    int dimensionY;
};

class TiffImage : public Image {
public:
    void Draw() { }
    Dimension GetDimensionInPixels() {
        return Dimension(dimensionX, dimensionY);
    }
};

int main() {
    Image* pImage = new TiffImage;

    auto then = Clock::now();
    for (int i = 0; i < 1000; ++i) {
        pImage->Draw();
    }

    auto now = Clock::now();

    cout << "Time taken: "
         << std::chrono::duration_cast
           <std::chrono::nanoseconds>(now - then).count()
         << " nanoseconds" << endl;

    return 0;
}
