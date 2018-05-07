#ifndef NETMODEL_H
#define NETMODEL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QMap>
#include <QMessageBox>
#include <QDebug>
#include <sqlmodel.h>
#include <allstruct.h>

class netmodel :public QObject
{
    Q_OBJECT
public:

    ~netmodel();
    int get_flag();
    static netmodel* get_net();
    QString get_Ip();
    int get_Port();
    void connect_toserver(QString IP, int port);//连接服务器成功
    void send_data(QString data);
    void ok();
    void false_no();
signals:
    void sendStatus(QString data);
    void Status_add(QString data);
    void rule_sig(QString data);
    void em_sig(QString data);
    void config_sig(QString data);
    void auth_sig(QString data);
    void ems_sig(QString data);

    void connect_ok();
public slots:
    void disconnect_from_server();//断开服务器
    void read_data();//读取服务器返回的数据 
    void connect_again();//重新链接服务器
    void connect_to_server_suc();


private:
    explicit netmodel(QObject *parent = 0);
    netmodel(netmodel& n){}
    QTcpSocket *mSocket;
    QString Ip;
    int port;
    int flag;
    static netmodel *pnet;
    QTimer *connectTimer;
    sqlmodel *sql;
};

#endif // NETMODEL_H
