#include<Magick++.h>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stdint.h>
#include<math.h>
#include<QString>
#include "gui.hpp"

using namespace std;
using namespace Magick;

typedef uint16_t WORD;

//This function pads zero according to pad value to an int
string zfill(int num,int pad)
{
  stringstream st;
  st<<num;
  string snum;
  st>>snum;
  int nz=pad-snum.length();
  for(int i=0;i<nz;i++)
    snum="0"+snum;
  return snum;
}
//function done END
Alg::Alg()
{
  cout<<"welcome to the big bang"<<endl;
}
//This function here, calculates the wronskian value
  float Alg::wronskian(int row,int col,WORD pxmean,int size,int wofrgb)
  {
    float wronsk=0;
    float temp1=0;
    if(pxmean!=0)
    {
      if(row-size>=0 && (row+size)<imght && col-size>=0 && (col+size)<imgwd)
      {
        PixelPacket *wvect=image.getPixels(col-size,row-size,wvsize,wvsize);
        for(int i=0;i<wvsize;i++)
          for(int j=0;j<wvsize;j++)
	  {
	    if(wofrgb==0)
	      temp1=(wvect->red)/pxmean;
	    else if(wofrgb==1)
	      temp1=(wvect->green)/pxmean;
	    else if(wofrgb==2)
	      temp1=(wvect->blue)/pxmean;
	    temp1=temp1*(temp1-1);
	    wronsk+=temp1;
	  }
        wronsk=fabs(wronsk/(wvsize*wvsize));
      }
      else
      {
        PixelPacket *wvect=image.getPixels(col,row,1,1);
        if(wofrgb==0)
          temp1=(wvect->red)/pxmean;
        else if(wofrgb==1)
          temp1=(wvect->green)/pxmean;
        else if(wofrgb==2)
          temp1=(wvect->blue)/pxmean;
        wronsk=fabs(temp1*(temp1-1));
      }
    }
    return wronsk;
  }
//wronskian function done END



//This function calculates the mean
  void Alg::calcmean(rgbs rgbt,rgbs *meanval,int ct)
  {
    meanval->r=((ct-1)*( meanval->r)+rgbt.r)/ct;
    meanval->g=((ct-1)*( meanval->g)+rgbt.g)/ct;
    meanval->b=((ct-1)*( meanval->b)+rgbt.b)/ct;
  }
//mean calculated done END



//end of the grid function END

//This function does 3 main things 1.reads image 2.manipulates pixels 3. forms new image

  int Alg::readimg(int imgbeg,int imgend)
  {
    count=0;
    wvsize=5;
// Getting name of the image
    stringstream formimg; 
    string imgpath=path.toUtf8().constData();;
    string imginit=basenam.toUtf8().constData();
    string extnsn=ext.toUtf8().constData();
    string imgname;
// name and range of the image recieve END




// Loop that iterates over images 

    
    for(int i=imgbeg;i<=imgend;i++)
    {

//Reading each image
      formimg.str(std::string());//clearing string stream
      formimg <<imgpath<<imginit<<zfill(i,basenum.length())<<extnsn;
      imgname=formimg.str();
      try
        {image.read(imgname);}
      catch(Exception &error_ )
      {
        cout<<"Caught exception: "<<error_.what()<<endl;
        return 1;
      }
//image read and if not exception thrown END



// Getting pixels of each image in rgb triplet form
      imght=image.rows();
      imgwd=image.columns();
      PixelPacket *pix=image.getPixels(0,0,imgwd,imght);
      rgbs rgb;
      count++;
      int pixnum=0;
      for(int j=0;j<imght;j++)//rows columns memberfunc of class Pixel
      {
        for(int k=0;k<imgwd;k++)
        {
	  rgb.r=pix->red;
	  rgb.g=pix->green;
	  rgb.b=pix->blue;
	  *pix++;

//pixels read in rgb form END


//Working with main algorithm for mean, variance and Wronskian calculation

	  if(count==1)
	    mean.push_back(rgb);
	  else
	  {
	    if(wronskian(j,k,mean[pixnum].r,2,0)<1 || wronskian(j,k,mean[pixnum].g,2,1)<1 || wronskian(j,k,mean[pixnum].b,2,2)<1)
	     {
	       calcmean(rgb,&mean[pixnum],count);
	     }
	  }
	  pixnum++;
        }//end of the column loop
      }//end of row loop
    }//end of image loop
    Blob blob(&mean[0],(mean.size()*sizeof(mean[0])));
    Image bg;
    stringstream bgsz;
    bgsz<<imgwd<<"x"<<imght;
    bg.size(bgsz.str());
    bg.magick("RGB");
    bg.read(blob);
    bg.write("bg.bmp");
    cout<<"see you at other end of galaxy"<<endl; 
    return 0;

  }//end of read image function
