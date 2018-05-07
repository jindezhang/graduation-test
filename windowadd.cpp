#include "windowadd.h"
#include "ui_windowadd.h"

windowadd::windowadd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowadd)
{
    ui->setupUi(this);
    //页面布局的设置
    setStyleSheet("windowadd{background-color:rgb(124 ,184 ,254)}");//设置背景颜色
    ui->wg_top->setDir("添加员工");
//    top事件
    connect(ui->wg_top,SIGNAL(bt_click()),this,SLOT(fanhui()));

    net = netmodel::get_net();
    rfid = QString("0");
    connect(net, SIGNAL(Status_add(QString)),this,SLOT(addstatus(QString)));


}

windowadd::~windowadd()
{
    delete ui;
}

void windowadd::fanhui()
{
    this->parentWidget()->show();
    this->close();
}

void windowadd::addstatus(QString status)
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);

    if(status.contains("ok", Qt::CaseInsensitive)){
         QMessageBox::warning(this,"提示", "添加成功");
         on_pushButton_2_clicked();
    }else if(status.contains("false", Qt::CaseInsensitive)){
        QMessageBox::warning(this,"提示", "添加失败！");
        on_pushButton_2_clicked();
    }else{
        //如果不是状态信息，那么就是员工数据。
        Em_info list;
        jsonc.json_toadd(status, list);

    }
}

void windowadd::on_pushButton_2_clicked()
{
    ui->id->setText("");
    ui->name->setText("");
    ui->depart->setText("");
    ui->l_tip->setText("请刷卡.....");

}

void windowadd::on_pushButton_clicked()
{
    if(!net->get_flag()){
        QMessageBox::warning(this,"提示", "网络未连接，添加失败！");
        return;
    }
//    if(rfid == "0"){
//        QMessageBox::warning(this,"提示", "未获取卡号，请重新刷卡");
//        return;
//    }

    //发送卡号给服务器。
    QString json_data;
    jsonc.add_tojson(rfid,json_data);
    net->send_data(json_data);

    //禁用按钮，发送成功后，可以启用。
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->l_tip->setText("正在添加...请稍候。");

}
