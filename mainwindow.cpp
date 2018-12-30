#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLayout>

/*
 * 主界面
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logPrint=new LogPrint(ui->textEdit);
    server=new FtpServer(this,21,false,logPrint,ui->statusBar);
    connect(server, SIGNAL(newPeerIp(QString)),this,SLOT(onPeerIpChanged(QString)));
    connect(ui->menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));
    connect(this,SIGNAL(start()),server,SLOT(start()));
    connect(this,SIGNAL(stop()),server,SLOT(stop()));
    startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 监听菜单栏
*/
void MainWindow::trigerMenu(QAction* action){
    if(action==ui->actionSetUserGroup){
        setUserGroupWindow=new SetUserGroupWindow(this,sqlConnection);
        setUserGroupWindow->exec();
    }else if(action==ui->actionAbout){
        ftpAbout=new FtpAbout(this);
        ftpAbout->exec();
    }
}

/*
 * 打印连接信息
*/
void MainWindow::onPeerIpChanged(const QString &peerIp)
{
    logPrint->setText("Connected to " + peerIp);
    logPrint->print();
}
