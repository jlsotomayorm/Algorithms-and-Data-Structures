#ifndef GABOREXTRACTION_H
#define GABOREXTRACTION_H
#include <string>
using namespace std;
class GaborExtraction
{
private:
    double mean(float * data,int tam);
    double sDeviation(float * data,int tam,double mean);

public:
    GaborExtraction();

    double * getFeatureVector(string path,int scale,int orientation);
    double euclideanDistance(double * v1,double * v2,int tam);
};

#endif // GABOREXTRACTION_H
