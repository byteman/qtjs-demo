#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebChannel>
#include "bridge.h"
#include <QDebug>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWebChannel *channel = new QWebChannel(this);
    Bridge *jsBridge = new Bridge(this);
    channel->registerObject("bridge", jsBridge);
    ui->widget->page()->setWebChannel(channel);


    connect(ui->widget->page(),SIGNAL(loadProgress(int)),this,SLOT(loadProgress(int)));
    connect(ui->widget->page(),SIGNAL(loadFinished(bool)),this,SLOT(loadSuccess(bool)));
    connect(ui->widget->page(),SIGNAL(loadStarted()),this,SLOT(loadStarted()));
    reload();

}
#include <QDir>
void MainWindow::reload()
{
    qDebug()<<"current applicationDirPath: "<<QCoreApplication::applicationDirPath();
    qDebug()<<"current currentPath: "<<QDir::currentPath();
    QString path = QUrl(QDir::currentPath() + "/html/index.html").toString();
    ui->widget->page()->load(path);
}
void MainWindow::loadStarted()
{
    qDebug() << "load started";
}
void MainWindow::loadProgress(int prog)
{
    qDebug() << "prog=" << prog;
}
void MainWindow::loadSuccess(bool result)
{
    qDebug() << "load finished=" << result;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->widget->page()->runJavaScript("addPoint(1000);");
    jsBridge->addOneData(1000);
    //jsBridge->getDatas();
}

void MainWindow::on_btnCalljs_clicked()
{
    ui->widget->page()->runJavaScript("callJs(100,200);",
                                      0,
        [](const QVariant &var){
        qDebug() << var.toString();}
    );
}
//调用一个js函数，传递参数，并且返回json对象.
void MainWindow::on_btnCalljs2_clicked()
{
    ui->widget->page()->runJavaScript("callJs2(100,200);",
                                      0,
        [](const QVariant &var){
        QJsonObject o = var.toJsonObject();

            qDebug() << o["age"].toInt();
            qDebug() << o["name"].toString();
            qDebug() << o["pass"].toString();
        }
    );
}

void MainWindow::on_btnLoad_clicked()
{
    reload();
}
