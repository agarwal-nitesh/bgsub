#ifndef INCLUDE_GUI_HPP
#define INCLUDE_GUI_HPP

#include<QApplication>
#include<QWidget>
#include<QFileDialog>
#include<QPushButton>
#include<QLineEdit>
#include<QGridLayout>
#include<Magick++.h>
#include<vector>
#include<stdint.h>
#include<math.h>

using namespace std;
using namespace Magick;


typedef uint16_t WORD;

class Alg
{
  protected: Image image;//using image class from magick 
  protected: int wvsize;
  protected: int imgwd;
  protected: int imght;
  public:QString path,basenam,basenum,ext;
  typedef struct
  {
    WORD r;
    WORD g;
    WORD b;
  } __attribute__((__packed__))
  rgbs;
  protected: vector<rgbs> mean;
  protected: int count;
  
  public: Alg();
  float wronskian(int, int, WORD, int, int);
  void calcmean(rgbs, rgbs*, int);
  int readimg(int,int);
};


class imviu: public QWidget, public Alg
{
  Q_OBJECT

  public:
    imviu(QWidget *parent=0);
  QLineEdit *qletl=new QLineEdit();
  QGridLayout *gridtl=new QGridLayout();
  QPushButton *btn1tl=new QPushButton("Browse");
  QPushButton *btn2tl=new QPushButton("Train");
  
  public slots: 
    void onbtnclick();
    void ontrain();
};


#endif

