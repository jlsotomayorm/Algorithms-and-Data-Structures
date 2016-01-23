#ifndef IMAGEVERTEX_H
#define IMAGEVERTEX_H
#include <string>
using namespace std;

class ImageVertex
{
private:
        string path;
public:
    ImageVertex(string p);
    ImageVertex();
    bool operator==(const ImageVertex &otro)const;
    bool operator<(const ImageVertex &otro)const;
    void operator=(const ImageVertex &otro);

    string getPath() const;
};

#endif // IMAGEVERTEX_H
