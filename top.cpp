#include "top.h"
#include "ui_top.h"

top::top(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::top)
{

    ui->setupUi(this);
    setStyleSheet("selectforid{background-color:rgb(124 ,184 ,254)}");//设置背景颜色
    ui->l_net->setStyleSheet("border-image:url(./wifion.png)");//显示自定义图片
    t = new QTimer();
    connect(t, SIGNAL(timeout()),this,SLOT(myupdate()));
    t->start(1000);
     ui->l_net->setStyleSheet("border-image:url(./wifion.png)");//显示自定义图片
}

top::~top()
{
    delete ui;
    delete t;
}

void top::setDir(QString dir)
{
    ui->l_dir->setText(dir);
}

void top::myupdate()
{
    ui->l_date->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    ui->l_time->setText(QTime::currentTime().toString("hh:mm:ss"));

}

void top::hideButton()
{
        ui->bt_fanhui->hide();
}

void top::on_bt_fanhui_clicked()
{
    emit bt_click();
}
