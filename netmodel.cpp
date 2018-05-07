#include "netmodel.h"

netmodel* netmodel::pnet = NULL;
//采用单例的设计模式
netmodel::netmodel(QObject *parent):QObject(parent)
{
    flag = 0;
    Ip = "0";
    port = 0;
    mSocket = new QTcpSocket();
    connect(mSocket,SIGNAL(connected()),this, SLOT(connect_to_server_suc()));
    connect(mSocket, SIGNAL(disconnected()),this, SLOT(disconnect_from_server()));
    connect(mSocket,SIGNAL(readyRead()),this, SLOT(read_data()));

    connectTimer = new QTimer();
    connect(connectTimer,SIGNAL(timeout()), this, SLOT(connect_again()));

    sql = sqlmodel::get_model();
}

netmodel::~netmodel()
{
//    防止内存泄露，在本类中的new的对象都应该在这个对象销毁的时候，释放对应的空间。
    delete mSocket;
}

int netmodel::get_flag()
{
    qDebug() <<"get_flag()";
    return flag;
}

netmodel *netmodel::get_net()
{
    if(NULL==pnet){
        pnet = new netmodel();
    }
    return pnet;
}

QString netmodel::get_Ip()
{
    return Ip;
}

int netmodel::get_Port()
{
    return port;
}

void netmodel::connect_toserver(QString IP, int port)
{
    this->Ip = IP;
    this->port = port;
    qDebug()<<"port:"<<port;
    mSocket->connectToHost(Ip, port);


}

void netmodel::disconnect_from_server()
{

    qDebug()<<"disconnect_from_server";
    flag = 0;
    connectTimer->start(1000*20);//超过20秒连接一次服务器。
}

//读取服务器传来的数据。
void netmodel::read_data()
{
    QByteArray array = mSocket->readAll();
    QString str = QString(array);
    qDebug()<<"str:"<<str;
    if(str.contains("add", Qt::CaseInsensitive)){
        qDebug()<<"add:"<<str;
        emit Status_add(str);
    }else if(str.contains("rule", Qt::CaseInsensitive)){
        emit rule_sig(str);
    }else if(str.contains("em_infos", Qt::CaseInsensitive)){
        emit ems_sig(str);
    }else if(str.contains("config", Qt::CaseInsensitive)){
        emit config_sig(str);
    }else if(str.contains("authority", Qt::CaseInsensitive)){
        emit auth_sig(str);
    }else if(str.contains("em_info", Qt::CaseInsensitive)){
        emit em_sig(str);
    }
    emit sendStatus(str);
}

void netmodel::send_data(QString data)
{
    QByteArray cstr = data.toLatin1();
    qDebug()<<cstr;
    mSocket->write(cstr);
}

void netmodel::ok()
{
    send_data("ok");
}

void netmodel::false_no()
{
    send_data("false");
}

void netmodel::connect_again()
{
    mSocket->connectToHost(Ip, port);
}

void netmodel::connect_to_server_suc()
{
    flag = 1;
    connectTimer->stop();
    Net data;
    data.ip = Ip;
    data.port = QString("%1").arg(port);
    sql->net_insert(data);
    emit connect_ok();

    qDebug()<<"connect_to_server_suc";
}


