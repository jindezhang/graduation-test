#ifndef FIRST_H
#define FIRST_H

#include <QMainWindow>
#include <QDebug>
#include <netmodel.h>
#include <QTime>
#include <windowmain.h>
#include <QMessageBox>
#include <QObject>
#include <sqlmodel.h>
#include <allstruct.h>
#include <json.h>

/*
 *
 *
 * 表格的发送从权限表、config、rule顺序。
 *
 *
 * */
namespace Ui {
class first;
}

class first : public QMainWindow
{
    Q_OBJECT

public:
    explicit first(QWidget *parent = 0);
    ~first();

private slots:
    void del();
    void on_bt_connect_clicked();
    void net_connect_ok();
    void net_timeout();
    void showdata(Net data);
    void on_bt_jump_clicked();
    void init(QString json);
private:
    Ui::first *ui;
    netmodel *net;
    QTimer *nettimer;
    sqlmodel *sl;
    json jsonc;
    int flag;//用于标识是否初始化了。
};

#endif // FIRST_H
