#include "gaborextraction.h"
#include "ImageGray.h"
#include "ipFFT2D.h"
#include "ipGabor2D.h"
#include "matrix_addons.h"
#include "DiskXFile.h"
#include "CmdLine.h"


using namespace Torch;
GaborExtraction::GaborExtraction()
{

}

double * GaborExtraction::getFeatureVector(string path,int scale,int orientation)
{
        //char *image_filename= const_cast<char*> (path.c_str());
        bool verbose=false;
//        int scale=5;
//        int orientation=6;
        real Ul=0.05;
        real Uh=0.4;
        int side=12;


        Allocator *allocator = new Allocator;

        // load input image
        Image *image_in = new(allocator) ImageGray();

        image_in->setBOption("verbose", verbose);
        image_in->load(path.c_str());


        if(verbose)
        {
                print("Image info:\n");
                print("   width = %d\n", image_in->width);
                print("   height = %d\n", image_in->height);
                print("   format = %s (%d)\n", image_in->coding, image_in->n_planes);
        }

        Image *image = image_in;

        //
        // Gabor2D

        int size = 2*side+1;

//        print("Gabor filters:\n");
//        print(" scale = %d\n", scale);
//        print(" orientation = %d\n", orientation);
//        print(" highest spatial frequency = %g\n", Uh);
//        print(" lowest spatial frequency = %g\n", Ul);
//        print(" filter dimension = %d -> %dx%d\n", side, size, size);

        //
        // Creates a Gabor filter bank and save them as pgm
        ipGabor2D **gaborFilterBank = NULL;
        gaborFilterBank = (ipGabor2D **)allocator->alloc(scale*orientation*sizeof(ipGabor2D *));

        // allocate output images of Gabor wavelets
        ImageGray *image_r_out = new(allocator) ImageGray(size*orientation, size*scale);
        ImageGray *image_i_out = new(allocator) ImageGray(size*orientation, size*scale);
        Mat *mgabor_r = new(allocator) Mat(size*scale, size*orientation);
        Mat *mgabor_i = new(allocator) Mat(size*scale, size*orientation);
        Mat *tmp_r = new(allocator) Mat(size, size);
        Mat *tmp_i = new(allocator) Mat(size, size);

        mgabor_r->zero();
        mgabor_i->zero();

        int f = 0;

        for(int s=0;s<scale;s++)
           for(int n=0;n<orientation;n++)
           {
                if(verbose) print("Computing Gabor 2D (s=%d o=%d) ...\n", s+1, n+1);

                gaborFilterBank[f] = new(allocator) ipGabor2D(size, size, s+1, n+1, Ul, Uh, scale, orientation);
                gaborFilterBank[f]->setBOption("verbose", verbose);

                if(verbose)
                {
                        // print coefficients
                        real *gabor_r = gaborFilterBank[f]->seq_out->frames[0];
                        real *gabor_i = gaborFilterBank[f]->seq_out->frames[1];

                        print("Gabor 2D:\n");
                        for(int i = 0; i < gaborFilterBank[f]->seq_out->frame_size; i++)
                                print("[%d] = %g (%g)\n", i, gabor_r[i], gabor_i[i]);
                }

                mxCopy(tmp_r, gaborFilterBank[f]->Gr, 0, 0, 0, 0, 2*side, 2*side);
                mxCopy(tmp_i, gaborFilterBank[f]->Gi, 0, 0, 0, 0, 2*side, 2*side);

                mxScale(tmp_r);
                mxScale(tmp_i);

                mxCopy(mgabor_r, tmp_r, s*size, n*size, 0, 0, 2*side, 2*side);
                mxCopy(mgabor_i, tmp_i, s*size, n*size, 0, 0, 2*side, 2*side);

                f++;
           }

        printf("Termine el filtro\n");
        for(int i = 0 ; i < image_r_out->height ; i++)
                        for(int j = 0 ; j < image_r_out->width ; j++)
                        {
                                image_r_out->data[i*image_r_out->width + j] = mgabor_r->ptr[i][j];
                                image_i_out->data[i*image_i_out->width + j] = mgabor_i->ptr[i][j];
                        }

        image_r_out->updatePixmapFromData();
        image_r_out->save("gabor_r.pgm");

        image_i_out->updatePixmapFromData();
        image_i_out->save("gabor_i.pgm");

        allocator->free(mgabor_r);
        allocator->free(mgabor_i);
        allocator->free(image_r_out);
        allocator->free(image_i_out);


        //
        // Filter the input image using the filter bank in the FT domain

        // check if the image if power of 2
        int new_width = (int) pow(2.0, ceil(log2((double)(image_in->width+2.0*side))));
        int new_height = (int) pow(2.0, ceil(log2((double)(image_in->height+2.0*side))));

       // print("Updating image size for FFT\n");
       // print(" width = %d -> new width = %d\n", image_in->width, new_width);
        //print(" height = %d -> new height = %d\n", image_in->height, new_height);

        // allocate the new image
        ImageGray *newimage = new(allocator) ImageGray(new_width, new_height);

        // re-copy the input image into an image of size power of 2
        pasteGray(image_in->data, side, side, image_in->width, image_in->height, newimage->data, new_width, new_height);
        newimage->updatePixmapFromData();

        if(verbose) newimage->save("new.pgm");

        // the image is the new image
        image = newimage;

        // create a FFT ipCore
        ipFFT2D *fft2d = new(allocator) ipFFT2D(image->width, image->height);
        fft2d->setBOption("verbose", verbose);

        // create a FFT ipCore in IFFT mode
        ipFFT2D *ifft2d = new(allocator) ipFFT2D(image->width, image->height, true);
        ifft2d->setBOption("verbose", verbose);

        // allocate snapshot images
        image_r_out = new(allocator) ImageGray(image_in->width*orientation, image_in->height*scale);
        image_i_out = new(allocator) ImageGray(image_in->width*orientation, image_in->height*scale);

        // allocate the FFT of the input image
        Sequence *seqfft = new(allocator) Sequence(2, image->width * image->height);

        // compute the FFT of the input image
        fft2d->process(image);

        // copy the FFT of the input image into a sequence
        seqfft->copy(fft2d->seq_out);


        //Vector que almacena las caracteristicas de la imagen

        double *featureV = new double[scale*orientation*2];
        int indice=0;

        printf("Empiezo convolution\n");
        // loop on Gabor filters of the filter bank
        for(int f=0 ; f < scale*orientation ; f++)
        {
                int s = gaborFilterBank[f]->s-1;
                int n = gaborFilterBank[f]->n-1;

                if(verbose) print("Applying Gabor 2D (s=%d o=%d) ...\n", s+1, n+1);

                // filter the image in the FT domain
                gaborFilterBank[f]->setFFT(fft2d, ifft2d, image_in->width, image_in->height);

                // filter the image
                gaborFilterBank[f]->process(seqfft);

                // scale the outputs (filtered images) both real and imaginary parts


                real * datos1 = gaborFilterBank[f]->seq_out->frames[0];
                real * datos2 = gaborFilterBank[f]->seq_out->frames[1];


                for(int i=0;i<image_in->width*image_in->height;i++)
                {
                    datos2[i]= sqrt(pow(datos1[i],2)+pow(datos2[i],2));

                }

                int tam=image_in->width*image_in->height;
                double meanTmp=mean(datos2,tam);
                featureV[indice++]=meanTmp;
                featureV[indice++]=sDeviation(datos2,tam,meanTmp);

                scaleGray(image_in->width, image_in->height, gaborFilterBank[f]->seq_out->frames[0]);
                scaleGray(image_in->width, image_in->height, gaborFilterBank[f]->seq_out->frames[1]);

                // save individual filtered images if needed
                if(verbose)
                {
                        char str[250];
                        ImageGray *image_out = new ImageGray(image_in->width, image_in->height);



                        image_out->copyFrom(image_in->width, image_in->height, gaborFilterBank[f]->seq_out->frames[0], "gray");
                        sprintf(str, "filter-R-s%d-o%d.pgm", s, n);
                        image_out->save(str);

                        image_out->copyFrom(image_in->width, image_in->height, gaborFilterBank[f]->seq_out->frames[1], "gray");
                        sprintf(str, "filter-I-s%d-o%d.pgm", s, n);
                        image_out->save(str);

                        delete image_out;
                }

                // paste the scaled output images into the snapshot images both real and imaginary parts
                pasteGray(gaborFilterBank[f]->seq_out->frames[0], n*image_in->width, s*image_in->height, image_in->width, image_in->height, image_r_out->data, image_r_out->width, image_r_out->height);
                pasteGray(gaborFilterBank[f]->seq_out->frames[1], n*image_in->width, s*image_in->height, image_in->width, image_in->height, image_i_out->data, image_i_out->width, image_i_out->height);
        }

        printf("Termino convolution\n");
        image_r_out->updatePixmapFromData();
        image_r_out->save("filter_r.pgm");

        image_i_out->updatePixmapFromData();
        image_i_out->save("filter_i.pgm");

//        cout<<"Indice: "<<indice<<endl;
//        for(int i=0;i<scale*orientation*2;i++)
//            cout<<featureV[i]<<" ";

//        cout<<endl;
        delete allocator;

        return featureV;


}

double GaborExtraction::mean(float * data,int tam)
{
    double sum=0;
    for(int i=0;i<tam;i++)
    {
        sum+=data[i];
    }

    return sum/tam;
}
double GaborExtraction::sDeviation(float * data,int tam,double mean)
{
    double variance=0;
    for(int i=0;i<tam;i++)
    {
        variance+=(pow((data[i]-mean),2));
    }

    double sD = sqrt(variance/tam);
    return sD;

}

double GaborExtraction::euclideanDistance(double *v1, double *v2, int tam)
{
    double sum=0;
    for(int i=0;i<tam;i++)
    {
        sum+=(pow((v1[i]-v2[i]),2));
    }

    return sqrt(sum);

}
