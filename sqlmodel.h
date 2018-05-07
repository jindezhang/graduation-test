#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <allstruct.h>
#include <QDate>


/*数据库的操作，select到的数据通过信号发送出去
 * insert 之后，注意delete对应的结构体
 *
 *
 * */

class sqlmodel : public QObject
{
    Q_OBJECT

public:
    static sqlmodel* get_model();
    ~sqlmodel();
    bool doConnect(const QString &dbName);
    void doClose();

    int sql_count(QString table);

    //系统配置表的操作，插入前，删除。***转化为对程序配置表的操作config，服务器数据、考勤规则、时间点分开插入。
    void net_select();
    bool net_insert(Net &data);
    void config_select(QString &rule);
    bool config_insert(QString rule);
    bool config_insert_time(config &con);
    void config_select_time(QString &before, QString &after);
    bool config_reset();//重置系统。
    void config_select_all(config &con);

//    权限表，用于进入主菜单的操作。
    void authority_select(QString rfid);//权限
    bool authority_delete(QString rfid);
    bool authority_insert(QString rfid);

//    员工数据，未考勤前的数据
    void em_info_selectAll();//获取员工的rfid信息。
    void em_info_selectforid(QString rfid);
    bool em_info_insert(Em_info &info);
    void em_info_delete(QString rfid);
    void em_info_deleteAll();

//    员工考勤数据
    void em_infos_selectAll(QString &data);
    void em_infos_select_department(QStringList &list);
    void em_infos_select_date(QStringList &list_y,QStringList &list_m,QStringList &list_d);
    bool check_exists(QStringList list, QString str);
//    void em_infos_selectfordepartment(QString department);
    void em_infos_selectfordate(QString date);//发送数据给服务器。
    void em_infos_selectfor_department(QString department);

//    同时查找日期和部门，不需要某一部分的时候，参数为NULL;查找所有的时候，都给NULL；
    void em_infos_select_for_date_department(QString department, QString date, QString &sql_data);//具有特殊性，只为下载数据模块服务。
    void em_infos_select_for_date_department_json(QString department, QString date, QList<Em_infos> &json_data);
    bool em_infos_insert(Em_info &info);//当收到当日的员工数据的时候，就可以立即插入所有员工数据（工号，姓名，部门），所以采用的Em_info 结构体
    void em_infos_delete(QString id);
    void em_infos_deleteAll();
    bool em_infos_update(QString id, QString col_name, QString value);

//    考勤规则
    void rule_selectAll();//获取考勤规则的name；
    void rule_selectAll(QStringList &list);
    void rule_select(QString name);
    bool rule_insert(Rule &info);
    void rule_delete(QString name);
    void rule_deleteAll();

//    日志信息
    bool log_insert(Log &info);
    //void log_delete();
    void table_select(QString name);
    bool table_update(QString name,QString time);

    //接收者：结构体引用
signals:
    void sendNet(Net data);
    void sendEm_infos(Em_infos data);
    void sendEm_info(Em_info data);
    void sendRule(Rule data);
    void sendTable(QString time);
    void sendAuthority(QString rfid);

private:
    explicit sqlmodel(QObject *parent = 0);
    QSqlDatabase db;
    sqlmodel(sqlmodel& s){}
    static sqlmodel *model;


};

#endif // SQLMODEL_H
