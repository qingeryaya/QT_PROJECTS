#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);  //设置QTdesigner里面的ui关联到widget类的私有变量ui里面
    // 虽然上面一行的代码进行了widget和ui的窗口关联，但是如果窗口大小发生了变化，里面布局不会随之变化
    // 通过下面的一行进行显示的说明，让窗口变化时，布局及其子空间随之调整
    this->setLayout(ui->verticalLayout);
    ui->widgetBottom->setLayout(ui->horizontalLayout);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChanged(int)));
    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(onCursorPositionChanged()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnOpen_clicked()
{
    QFileDialog qFileDialog;
    qFileDialog.setFileMode(QFileDialog::ExistingFile);
    qFileDialog.setNameFilters({"Text Files (*.txt)", "C++ Source Files (*.cpp)", "All Files (*.*)"});

    if (qFileDialog.exec() == QDialog::Accepted) {
        QString fileName = qFileDialog.selectedFiles().first();
        qDebug()<<fileName;

        ui->textEdit->clear();

        if(!file.isOpen())
        {
            file.setFileName(fileName);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
        }
        else
            file.seek(0);

        QTextStream out(&file);
        out.setCodec(ui->comboBox->currentText().toStdString().c_str());
//        out.setCodec("UTF-8");
        while (!out.atEnd()) {
            ui->textEdit->append(out.readLine());
        }
//        file.close();
    }
}

void Widget::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("save file"),"./untitled.txt",tr("Text (*.txt)"));
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream toFile(&file);
//    toFile.setCodec("UTF-8");
    toFile.setCodec(ui->comboBox->currentText().toStdString().c_str());

    QString qStringToNewFile = ui->textEdit->toPlainText();
    toFile<<qStringToNewFile;
//    file.close();
}

void Widget::on_btnClose_clicked()
{
    if(file.isOpen())
    {
        file.close();
        ui->textEdit->clear();
    }
}

void Widget::currentIndexChanged(int index)
{
    ui->textEdit->clear();
    if(file.isOpen())
    {
        file.seek(0);
        QTextStream qStream(&file);
        qStream.setCodec(ui->textEdit->toPlainText().toStdString().c_str());
        while (!qStream.atEnd()) {
            ui->textEdit->append(qStream.readLine());
        }
    }
}

void Widget::onCursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QString row = QString::number(cursor.blockNumber()+1);
    QString col = QString::number(cursor.columnNumber()+1);
    const QString msg = "row:" +row+" col:"+col+"    ";
    ui->labelPosition->setText(msg);
}
