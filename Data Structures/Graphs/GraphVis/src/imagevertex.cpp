#include "imagevertex.h"

ImageVertex::ImageVertex(string p)
{
    path =p;
}

ImageVertex::ImageVertex()
{
    path="unknown";
}


bool ImageVertex::operator==(const ImageVertex &otro)const
{
    return path==otro.path;
}

bool ImageVertex::operator<(const ImageVertex &otro)const
{
    return path<otro.path;
}

void ImageVertex::operator=(const ImageVertex &otro)
{
    path = otro.path;
}

string ImageVertex::getPath()const
{
    return path;
}
