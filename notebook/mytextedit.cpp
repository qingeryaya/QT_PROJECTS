#include "mytextedit.h"
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) : QTextEdit(parent)
{
    // 可以在这里初始化一些设置
}

void MyTextEdit::wheelEvent(QWheelEvent *e)
{
    // 处理鼠标滚轮事件的自定义逻辑
    qDebug() << "Mouse wheel event";

    // 调用父类的默认行为
    QTextEdit::wheelEvent(e);
}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{
    // 处理键盘按下事件的自定义逻辑
    qDebug() << "Key pressed:" << e->text();

    // 调用父类的默认行为
    QTextEdit::keyPressEvent(e);
}

void MyTextEdit::keyReleaseEvent(QKeyEvent *e)
{
    // 处理键盘释放事件的自定义逻辑
    qDebug() << "Key released:" << e->text();

    // 调用父类的默认行为
    QTextEdit::keyReleaseEvent(e);
}
