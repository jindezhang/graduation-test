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
    nettimer->start(5000*100);//!!!
    ui->bt_connect->setEnabled(false);
    ui->bt_jump->setEnabled(false);
    ui->tips->setText("连接服务器成功....正在初始化，请稍候。");

    config c;
    sl->config_select_all(c);
    QString com = QString("%1#init").arg(c.device);
    net->send_data(com);



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
    //已经完成初始化。
    if(flag != 0 )
        return;
    qDebug()<<"init json:"<<json;
    //1 初始化权限表
    if(json.contains("authority")){
        jsonc.json_toauthority(json);//该方法完成存储和del。
        return;
    }
//   2 初始化配置信息
    if(json.contains("config")){
        config c;
        jsonc.json_toconfig(c, json);
        if(sl->config_insert_time(c)){
            net->ok();
        }else
            net->false_no();
        return;
    }
//   3 初始化考勤规则
    if(json.contains("rule")){
        QList<Rule> list;
        jsonc.json_torule(list,json);

        QList <Rule>::iterator iter;
        Rule tmp_em;
        for(iter = list.begin(); iter != list.end(); iter++){
            tmp_em = *iter;
            if(!sl->rule_insert(tmp_em))
                net->false_no();
        }
        net->ok();
        return;

    }

    // 4 update time
    if(json.contains("##")){

        QStringList list = json.split("##");
        QString dd = list[0];
        QString tt = list[1];

        QString d = "date -s 2018-12-12";
        QString t = "date -s 14:14";
        system(d.toLatin1().data());
        system(t.toLatin1().data());
    }

    //初始化数据的完成
    flag = 1;
    nettimer->stop();
    MainWindow *main = new MainWindow();
    main->show();
    this->close();
    qDebug()<<"init:"<<json;
}
