#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPoint curPos;  //当前方块
    int curShape, nextShape;    //方块的种类 28种 0-27
    QTimer* timer;
    int score;
private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent* event);
    bool isValid(int x, int y);
    virtual bool event(QEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    void blockDrop(bool real = true);
public slots:
    void speed();

};

#endif // MAINWINDOW_H
