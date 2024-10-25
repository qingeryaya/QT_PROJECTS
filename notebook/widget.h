#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnOpen_clicked();

    void on_btnSave_clicked();

    void on_btnClose_clicked();

    void currentIndexChanged(int index);

    //定位光标
    void onCursorPositionChanged();

private:
    QFile file;
    Ui::Widget *ui;
};
#endif // WIDGET_H
