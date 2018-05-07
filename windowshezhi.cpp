#include "windowshezhi.h"
#include "ui_windowshezhi.h"

windowshezhi::windowshezhi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::windowshezhi)
{
    ui->setupUi(this);
    setStyleSheet("windowshezhi{background-color:rgb(124 ,184 ,254)}");//设置背景颜色
    //页面布局的设置
    ui->wg_top->setDir("系统设置");
    connect(ui->wg_top,SIGNAL(bt_click()),this,SLOT(fanhui()));

    w = NULL;
    net = netmodel::get_net();
    sql = sqlmodel::get_model();
}

windowshezhi::~windowshezhi()
{
    delete ui;
}

void windowshezhi::fanhui()
{
    delete w;
    w = NULL;
    this->parentWidget()->show();
    this->close();
}

void windowshezhi::set_Enabled(bool b)
{
    ui->pushButton->setEnabled(b);
    ui->pushButton_2->setEnabled(b);
    ui->pushButton_3->setEnabled(b);


}

void windowshezhi::on_pushButton_2_clicked()
{
    if(NULL == w)
        w= new netwindow(this);//把主界面指针传给灯光控制界面，（返回处理， 使用主界面数据）
    w->show();
    this->hide();
}

void windowshezhi::on_pushButton_clicked()
{
    net->send_data("update time");
}

void windowshezhi::on_bt_reset_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Question"),
                                                  tr("确认重置系统吗?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {

        set_Enabled(false);
        if(sql->config_reset()){

        }
    }
}
