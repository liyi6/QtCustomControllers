#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->toastLine->setText(QStringLiteral("连接服务器失败."));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    QString toast = ui->toastLine->text();
    //QtCustomToastWidget::instance()->setBackColor(QColor(123,21,45));
    QtCustomToastWidget::instance()->toast(toast, this);
}
