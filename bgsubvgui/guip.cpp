#include<QApplication>
#include<QWidget>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QSplitter>
#include<QPushButton>
#include<QFileDialog>
#include<QLineEdit>
#include<QTextStream>
#include<QFileInfo>
#include<QPixmap>
#include<QLabel>
#include<iostream>
#include<Magick++.h>
#include "gui.hpp"

using namespace std;
using namespace Magick;

imviu::imviu(QWidget *parent)
  :QWidget(parent)
  {
    this->resize(1360,740);
    this->setWindowTitle("BackGround Subtractor");
    QHBoxLayout *maingrid=new QHBoxLayout(this);
    maingrid->setSpacing(1);
    
    QWidget *topleft=new QWidget(this);
    QWidget *topright=new QWidget(this);
    QWidget *bottomleft=new QWidget(this);
    QWidget *bottomright=new QWidget(this);
    
    //subwidgets for top-left-subwidget
    gridtl->setSpacing(10);
    gridtl->addWidget(qletl,2,1);
    gridtl->addWidget(btn1tl,2,2);
    gridtl->addWidget(btn2tl,2,3);
    topleft->setLayout(gridtl);
    qletl->setFixedSize(200,40);
    qletl->move(600,40);
    topleft->setFixedSize(670,360);
    
    //splitter for 4 main sub-widgets
    
    QSplitter *splitter1=new QSplitter(Qt::Horizontal);
    splitter1->addWidget(topleft);
    splitter1->addWidget(topright);
    
    QSplitter *splitter2=new QSplitter(Qt::Horizontal);
    splitter2->addWidget(bottomleft);
    splitter2->addWidget(bottomright);
    
    QSplitter *splitterv=new QSplitter(Qt::Vertical);
    splitterv->addWidget(splitter1);
    splitterv->addWidget(splitter2);
    
    maingrid->addWidget(splitterv);
    setLayout(maingrid);
    connect(btn1tl,SIGNAL(clicked()),this,SLOT(onbtnclick()));
    connect(btn2tl,SIGNAL(clicked()),this,SLOT(ontrain()));
     
  }
  
void imviu::onbtnclick()
{
   QTextStream out(stdout);
   QString name=QFileDialog::getOpenFileName();
   QFileInfo fi(name);
   QString base=fi.baseName();//tmp0001
   basenum="";
   basenam="";
   for(int i=0;i<base.length();i++)
   {
     if(base[i]>=48 && base[i]<=57)
       basenum+=base[i];
     else
       basenam+=base[i];
   }
   path=fi.path()+"/";///home/erudite/image
   ext="."+fi.suffix();//jpg 
   //out<<path<<endl<<basenam<<endl<<basenum<<endl<<ext<<endl;  
   //try
   //{nameF=name.toUtf8().constData();}//for linux
   //catch(...)
   //{nameF=name.toLocal8Bit().constData();}//for windows
}

void imviu::ontrain()
{
  QString text=qletl->text();
  QStringList tx=text.split("-");
  int beg,end;
  try
  {
    beg=tx[0].toInt();
    end=tx[1].toInt();
  }
  catch(...)
  {
    beg=1;
    end=beg;
  }
  readimg(beg,end);
  QPixmap pixmap("bg.bmp");
  QLabel *lbl=new QLabel();
  lbl->setPixmap(pixmap);
  gridtl->addWidget(lbl,1,1);
}

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);
  imviu window;
  window.show();
  return app.exec();
}


