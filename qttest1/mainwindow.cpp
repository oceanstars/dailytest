#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>
#include <iostream>
using namespace std;

int pats[7*4] = {
    0x0660,0x0660,0x0660,0x0660, 0x4460,0x0740,0x6220,0x02e0,
    0x2260,0x0470,0x6440,0x0e20, 0x0630,0x2640,0x0630,0x2640,
    0x0360,0x4620,0x0360,0x4620, 0x0720,0x2620,0x0270,0x2320,
    0x4444,0x0f00,0x4444,0x0f00
  };
int maps[28] = {0xffff, 0xffff, 0xffff, 0xffff};
int timeCount = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer(this))
{
    curShape = qrand()%28;
    nextShape = qrand()%28;
    score = 0;
    curPos = QPoint(6,0);
    timer->setInterval(500);
    ui->setupUi(this);
    setGeometry(200, 100, 600, 600);
    connect(timer, SIGNAL(timeout()),this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::blue);
    painter.setPen(pen);
    //painter.drawLine(QPoint(20,20), QPoint(100,100));
    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    //painter.drawRect(100, 100, 20, 20);
    //绘制主框架
    for(int y=0; y < 20; y++)
    {
        for(int x=0; x < 10; x++)
        {
            painter.drawRect(20 + x*25, 20 + y*25, 25, 25);
        }
    }
    //绘制预览窗口
    for(int y=0; y < 4; y++)
    {
        for(int x=0; x < 4; x++)
        {
            painter.drawRect(400 + x*25, 20 + y*25, 25, 25);
        }
    }
    brush.setColor(Qt::red);
    painter.setBrush(brush);
    int temp;
    //绘制原先的方块
    temp = 0x1 << 3;
    for(int y=0; y < 20; y++)
    {

        for(int x=0; x < 10; x++)
        {
            if((maps[y+4] & (temp << x)) >1 )
            {
                painter.drawRect(20 + x*25, 20 + y*25, 25, 25);
            }
        }
    }
    //下个方块预览
    for(int y=0; y < 4; y++)
    {
        temp = 0x1 << (y*4);
        for(int x=0; x < 4; x++)
        {
            if( (pats[nextShape] & temp) > 1 )
            {
                //painter.eraseRect(400 + x*25, 20 + y*25, 25, 25);
                painter.drawRect(400 + x*25, 20 + y*25, 25, 25);
            }
            temp = temp << 1;
        }
    }
    //当前方块显示
    for(int y=0; y < 4; y++)
    {
        temp = 0x1 << (y*4);
        if((curPos.ry()+y) < 0)
            continue;
        for(int x=0; x < 4; x++)
        {
            if( (pats[curShape] & temp) >= 1 )
            {
                //painter.eraseRect(400 + x*25, 20 + y*25, 25, 25);
                painter.drawRect(20 + (curPos.rx()+x)*25, 20 + (curPos.ry()+y)*25, 25, 25);
            }

            temp = temp << 1;
        }
    }
    painter.drawText(400, 330, QString("score:%1").arg(score));
    if(timer->isActive())
    {
        painter.drawText(400,300, tr("game start."));
    }
    else
    {
        painter.drawText(400,300, tr("game stop."));
    }
}


bool MainWindow::isValid(int x, int y)
{
    bool bIsValid = true;
    for(int i=0; i<4; i++)
    {
        if((y+i+4) <= 3)
            continue;
        if((maps[y+4+i] & (((pats[curShape] >> 4*i)&0xf) << (x+3)))>=1)
        {
            bIsValid = false;
            break;
        }
    }
    return bIsValid;
}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::ZOrderChange) keyPressEvent(0);
    return QMainWindow::event(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!timer->isActive())
    {
        if(event->key() == Qt::Key_P || event->key() == Qt::Key_Enter || Qt::Key_Return)
        {
            for(int x = 0; x<20; x++)
            {
                maps[x+4] = 0xc007;
            }
            maps[24] = maps[25] = maps[26] = maps[27] = 0xffff;
            qsrand(QTime::currentTime().msec());
            nextShape = qrand()%28;
            blockDrop(false);
            score = 0;
            timer->start();
        }
    }
    if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    {
        if(isValid(curPos.rx(), (curPos.ry()+1)))
        {
            curPos.ry()++;
        }
        else
        {
            blockDrop();
        }
    }
    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    {
        if(isValid((curPos.rx()-1), curPos.ry()))
        {
            curPos.rx()--;
        }
    }
    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    {
        if(isValid((curPos.rx()+1), curPos.ry()))
        {
            curPos.rx()++;
        }
    }
    else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    {
        curShape = (curShape&(~3))|((curShape+1)&3);
        if(!isValid(curPos.rx(), curPos.ry()))
        {
            curShape = (curShape&(~3))|((curShape-1)&3);
        }
    }
}

void MainWindow::blockDrop(bool real)
{
    if(real)
    {
        cout << hex << pats[curShape%28] << endl;
        cout << dec << curPos.rx() << " " << curPos.ry() << endl;
        for(int y=0; y<4; y++)
        {
            cout << hex << maps[curPos.ry()+4+y] << endl;
            maps[curPos.ry()+4+y] |= ((pats[curShape%28] >> 4*y) & 0xf) << (curPos.rx()+3);
            cout << hex << (((pats[curShape%28] >> 4*y) & 0xf) << (curPos.rx()+3)) << endl;
            cout << hex << maps[curPos.ry()+4+y] << endl;
        }
        for(int x=3; x>=0; x--)
        {
            if(maps[curPos.ry()+4+x] == 0xffff)
            {
                memmove(&maps[5], &maps[4], sizeof(int)*(curPos.ry() + x -1));
                score++;
                maps[4] = 0xc007;
            }
        }
    }
    curShape = nextShape;
    nextShape = qrand()%28;
    curPos = QPoint(6,-3);
    if(!isValid(curPos.rx(), curPos.ry()))
    {
        timer->stop();
    }
}

void MainWindow::speed()
{
    if(timeCount >= 2)
    {
        curPos.ry()++;
        timeCount = 0;
    }
    else
        timeCount++;
}
