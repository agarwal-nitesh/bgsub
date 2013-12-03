from PyQt4 import QtCore, QtGui
import sys
import Image
from matplotlib.backends.backend_qt4agg import FigureCanvasQTAgg as FigureCanvas
import matplotlib.pyplot as plt
from collections import Counter

class imviu(QtGui.QWidget):

  def __init__(self):
    super(imviu,self).__init__()
    self.resize(1600,800)
    self.setWindowTitle('Image Plot')
    self.browse=QtGui.QFileDialog
    self.figure=plt.figure()
    self.canvas =FigureCanvas(self.figure)
    self.btn=QtGui.QPushButton('open image file',self)
    self.btn.clicked.connect(self.openimg)
    self.btn.move(0,50)
    self.btn1=QtGui.QPushButton('plot rgb',self)
    self.btn1.clicked.connect(self.plotimg)
    self.btn1.move(1000,50)
    self.grid=QtGui.QGridLayout()
    self.grid.setSpacing(10)
    self.grid.addWidget(self.canvas,2,2,10,1)
    self.grid.addWidget(self.btn,1,1)
    self.grid.addWidget(self.btn1,1,2)
    self.setLayout(self.grid)
    
  def plotimg(self):
    im=Image.open(self.nameF)
    pix=im.load()
    t=0
    pixelr=[]
    pixelb=[]
    pixelg=[]
    for i in range(im.size[0]):
      for j in range(im.size[1]):
        pixelr.append(pix[i,j][0])
	pixelb.append(pix[i,j][1])
	pixelg.append(pix[i,j][2])
    pixelr=Counter(pixelr)
    pixelry=pixelr.values()
    pixelrx=pixelr.keys()
    pixelb=Counter(pixelb)
    pixelby=pixelb.values()
    pixelbx=pixelb.keys()
    pixelg=Counter(pixelg)
    pixelgy=pixelg.values()
    pixelgx=pixelg.keys()

    ax =self.figure.add_subplot(311)
    ax.hold(False)
    ax.plot(pixelrx,pixelry,'red')
    plt.xticks(range(0,256,10))
    ax1=self.figure.add_subplot(312)
    ax1.hold(False)
    ax1.plot(pixelbx,pixelby,'blue')
    ax2=self.figure.add_subplot(313)
    ax2.hold(False)
    ax2.plot(pixelgx,pixelgy,'green')
    self.canvas.draw()


  def openimg(self):
    filename=self.browse.getOpenFileNames(directory="./")
    self.nameF=str(list(filename)[0])
    pixmap=QtGui.QPixmap(self.nameF)
    lbl=QtGui.QLabel(self)
    lbl.setFixedSize(675,650)
    lbl.setPixmap(pixmap)
    self.grid.addWidget(lbl,2,1,3,1)


def main():
  app=QtGui.QApplication(sys.argv)
  viu=imviu()
  viu.show()
  sys.exit(app.exec_())



if  __name__=='__main__':
  main()
