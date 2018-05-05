#include "first.h"
#include "ui_first.h"
#include <sqlmodel.h>

first::first(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::first)
{
    ui->setupUi(this);
    setStyleSheet("first{background-color:rgb(124 ,184 ,254)}");//设置背景颜色
    ui->wg_top->hideButton();
//    键盘del
    connect(ui->wg_keys,SIGNAL(click_del()),this,SLOT(del()));

    sl = sqlmodel::get_model();
    connect(sl,SIGNAL(sendNet(Net)), this, SLOT(showdata(Net)));
    sl->net_select();

    net = netmodel::get_net();
    connect(net, SIGNAL(sendStatus(QString)),this,SLOT(init(QString)));
    connect(net, SIGNAL(connect_ok()), this, SLOT(net_connect_ok()));

    nettimer = new QTimer();
    connect(nettimer,SIGNAL(timeout()),this, SLOT(net_timeout()));

    flag = 0;

}

first::~first()
{
    delete nettimer;
    delete ui;
}

void first::del()
{
    QString text;
    if(ui->IP->hasFocus()){
        text = ui->IP->text();
        text.remove(text.size()-1,1);
        ui->IP->setText(text);
    }
    if(ui->PORT->hasFocus()){
        text = ui->PORT->text();
        text.remove(text.size()-1,1);
        ui->PORT->setText(text);
    }
}



void first::on_bt_connect_clicked()
{
    QString ip = ui->IP->text();
    QString port = ui->PORT->text();
    if(ip.isEmpty() || port.isEmpty())
    {
        QMessageBox::warning(this, "提示","请输入服务器IP或端口号");

        return ;
    }
    net->connect_toserver(ip, port.toInt());
    ui->bt_connect->setEnabled(false);
    ui->bt_jump->setEnabled(false);
    ui->tips->setText("请稍后，正在连接.....");
    nettimer->start(5000);
}

void first::net_connect_ok()
{
    nettimer->start(5000);
    ui->bt_connect->setEnabled(false);
    ui->bt_jump->setEnabled(false);
    ui->tips->setText("连接服务器成功....正在初始化，请稍候。");

    //初始化数据的开始。
    MainWindow *main = new MainWindow();
    main->show();
    this->close();
}

void first::net_timeout()
{
    ui->bt_connect->setEnabled(true);
    ui->bt_jump->setEnabled(true);
    ui->tips->setText(" ");
    nettimer->stop();
    QMessageBox::warning(this, "提示","网络出现故障！");
}

void first::showdata(Net data)
{
    ui->IP->setText(data.ip);
    ui->PORT->setText(data.port);
}

void first::on_bt_jump_clicked()
{
    MainWindow *main = new MainWindow();
    main->show();

    this->close();
}

void first::init(QString json)
{
    if(flag != 0 )
        return;

    nettimer->stop();
    ui->bt_connect->setEnabled(true);
    ui->bt_jump->setEnabled(true);
    ui->tips->setText(" ");


    qDebug()<<"init:"<<json;
}
