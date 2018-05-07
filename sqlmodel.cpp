#include "sqlmodel.h"


sqlmodel* sqlmodel::model = NULL;

sqlmodel* sqlmodel::get_model()
{
    if(NULL == model){
        model = new sqlmodel();
    }
    return model;
}

sqlmodel::~sqlmodel()
{
    db.close();
}

bool sqlmodel::doConnect(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName(dbName);
       if (!db.open()) {
           qDebug() << "Database Error!";
           return false;
       }
       return true;
}

void sqlmodel::doClose()
{
    db.close();
}

sqlmodel::sqlmodel(QObject *parent)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
       db.setDatabaseName("kqj.db");
       if (!db.open()) {
           qDebug() << "Database Error!";
       }
}





int sqlmodel::sql_count(QString table)
{
    QSqlQuery query;
    QString sql = QString("select count(*) from %1;").arg(table);
    qDebug()<<sql;
    if( !query.exec(sql)){
        return -1;
    }
    while(query.next()){
     return query.value(0).toInt();
    }
    return 0;
}

void sqlmodel::net_select()
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM config;");
    Net data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.ip = query.value(0).toString();
        data.port = query.value(1).toString();
        emit sendNet(data);
    }
}

bool sqlmodel::net_insert(Net &data)
{
    QSqlQuery query;
//    QString sql_d = "delete from config;";
//    query.exec(sql_d);
    QString sql_s = QString("update config set ip='%1', port=%2;").arg(data.ip).arg(data.port);
    qDebug()<<sql_s;

    if(!query.exec(sql_s)){
        qDebug() << "update Failed!"<<query.lastError();
        return false;
    }
    return true;
}

void sqlmodel::config_select(QString &rule)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM config;");

    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        rule = query.value(2).toString();
    }
}

bool sqlmodel::config_insert(QString rule)
{
    QSqlQuery query;
//    QString sql_d = "delete from config;";
//    query.exec(sql_d);
    QString sql_s = QString("update config set rule='%1';").arg(rule);

    if(!query.exec(sql_s)){
        qDebug() << "update Failed!"<<query.lastError();
        return false;
    }
    return true;
}

bool sqlmodel::config_insert_time(config &con)
{
    QSqlQuery query;
//    QString sql_d = "delete from config;";
//    query.exec(sql_d);
    QString sql_s = QString("update config set before='%1' , after = '%2', rule = '%3', upload = '%4';").arg(con.before).arg(con.after).arg(con.rule).arg(con.upload);
    qDebug()<<"SQL"<<sql_s;
    if(!query.exec(sql_s)){
        qDebug() << "update Failed!"<<query.lastError();
        return false;
    }
    return true;
}



void sqlmodel::config_select_time(QString &before, QString &after)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM config;");
    qDebug()<<"SQL"<<sql_s;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        before = query.value(3).toString();
        after = query.value(4).toString();
    }
}

bool sqlmodel::config_reset()
{
    QSqlQuery query;
    QString sql_s = QString("insert into config SELECT * FROM reset;");

    if(!query.exec(sql_s)){
        qDebug() << "reset Failed!"<<query.lastError();
        return false;
    }
    sql_s = QString("delete from rule where name not in('DH1');");
    if(!query.exec(sql_s)){
        qDebug() << "reset Failed!"<<query.lastError();
        return false;
    }

    sql_s = QString("delete from em_info ;");
    if(!query.exec(sql_s)){
        qDebug() << "reset Failed!"<<query.lastError();
        return false;
    }

    sql_s = QString("delete from em_infos ;");
    if(!query.exec(sql_s)){
        qDebug() << "reset Failed!"<<query.lastError();
        return false;
    }


    return true;
}

void sqlmodel::config_select_all(config &con)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT rule,before,after,device,upload FROM config;");

    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        con.rule = query.value(0).toString();
        con.before = query.value(1).toString();
        con.after = query.value(2).toString();
        con.device = query.value(3).toString();
        con.upload = query.value(4).toString();
    }
}

void sqlmodel::authority_select(QString rfid)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM authority where rfid = '%1';").arg(rfid);
    QString data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data = query.value(0).toString();

        emit sendAuthority(data);
    }
}

bool sqlmodel::authority_delete(QString rfid)
{
    QSqlQuery query;
    QString sql_s = QString("delete FROM authority where rfid = '%1';").arg(rfid);
    if(!query.exec(sql_s)){
        qDebug() << "delete Failed!"<<query.lastError();
        return false;
    }
    return true;
}

bool sqlmodel::authority_insert(QString rfid)
{
    QSqlQuery query;

    QString sql_s = QString("insert into authority values('%1');").arg(rfid);

    if(!query.exec(sql_s)){
        qDebug() << "insert Failed!"<<query.lastError();
        return false;
    }
    return true;

}

void sqlmodel::em_info_selectAll()
{
    QSqlQuery query;
    QString sql_s = QString("SELECT rfid FROM em_info;");
    Em_info data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.rfid = query.value(0).toString();

        emit sendEm_info(data);
    }
}

void sqlmodel::em_info_selectforid(QString rfid)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM em_info where rfid ='%1';").arg(rfid);
    Em_info data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.id = query.value(0).toString();
        data.rfid = query.value(1).toString();
        data.name = query.value(2).toString();
        data.department = query.value(3).toString();
        data.icon = query.value(4).toString();
        emit sendEm_info(data);
    }
}

bool sqlmodel::em_info_insert(Em_info &info)
{
    QSqlQuery query;
    QString sql_s = QString("insert into em_info values('%1','%2','%3','%4','%5','%6');").arg(info.id).arg(info.rfid).arg(info.name).arg(info.department).arg(info.icon).arg(info.info);

    if(!query.exec(sql_s)){
        qDebug() << "insert Failed!"<<query.lastError();
        return false;
    }
    em_infos_insert(info);
    return true;
}

void sqlmodel::em_info_delete(QString rfid)
{
    QSqlQuery query;
    QString sql_s = QString("delete from em_info where rfid = '%1';").arg(rfid);
    if(!query.exec(sql_s)){
        qDebug() << "delete Failed!"<<query.lastError();

    }

}

void sqlmodel::em_info_deleteAll()
{
    QSqlQuery query;
    QString sql_s = QString("delete from em_info ;");
    if(!query.exec(sql_s)){
        qDebug() << "deleteAll Failed!"<<query.lastError();

    }

}


void sqlmodel::em_infos_selectAll(QString &data)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM em_infos  ;");
    QString tmp;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }
    while(query.next()){
        //获取到数据封装
        for(int i = 0;i < 11;i++){
            tmp = query.value(i).toString();
            for(int ni = tmp.size(); ni < 10;ni++){
                tmp.append(" ");
            }
            data.append(tmp);
            data.append("\n");
        }

    }
}

void sqlmodel::em_infos_select_department(QStringList &list)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT distinct department FROM em_infos  ;");
    QString data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }
    while(query.next()){
        data = query.value(0).toString();

        list<<data;
    }
}

void sqlmodel::em_infos_select_date(QStringList &list_y,QStringList &list_m,QStringList &list_d)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT distinct date FROM em_infos  ;");
    QString data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }
    while(query.next()){
        data = query.value(0).toString();
        QStringList list;
        list = data.split("-");
        if(check_exists(list_y,list[0]))
            list_y<<list[0];
        if(check_exists(list_m,list[1]))
            list_m<<list[1];
        if(check_exists(list_d,list[2]))
            list_d<<list[2];
    }
}

bool sqlmodel::check_exists(QStringList list, QString str)
{
    for(int i = 0;i<list.size();i++){
        if(list[i] == str)
            return false;
    }
    return true;
}

void sqlmodel::em_infos_selectfordate(QString date)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM em_infos where date = '%1';").arg(date);
    Em_infos data;
    if(!query.exec(sql_s)){
        qDebug() << "selectAll Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.id = query.value(0).toString();
        data.name = query.value(1).toString();
        data.department = query.value(2).toString();
        data.date = query.value(3).toString();
        data.amg = query.value(4).toString();
        data.amo = query.value(5).toString();
        data.pmg = query.value(6).toString();
        data.pmo = query.value(7).toString();
        data.nmg = query.value(8).toString();
        data.nmo = query.value(9).toString();
        data.info = query.value(10).toString();

        emit sendEm_infos(data);
    }

}

void sqlmodel::em_infos_selectfor_department(QString department)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM em_infos where department = '%1';").arg(department);
    Em_infos data;
    if(!query.exec(sql_s)){
        qDebug() << "selectAll Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.id = query.value(0).toString();
        data.name = query.value(1).toString();
        data.department = query.value(2).toString();
        data.date = query.value(3).toString();
        data.amg = query.value(4).toString();
        data.amo = query.value(5).toString();
        data.pmg = query.value(6).toString();
        data.pmo = query.value(7).toString();
        data.nmg = query.value(8).toString();
        data.nmo = query.value(9).toString();
        data.info = query.value(10).toString();

        emit sendEm_infos(data);
    }
}

void sqlmodel::em_infos_select_for_date_department(QString department, QString date, QString &sql_data)
{
    QSqlQuery query;
    QString sql_s ;
    QString tmp,tmp_l;

    if(NULL == department && NULL == date){
        sql_s = QString("SELECT * FROM em_infos  ;");
    }else if(NULL == department){
        sql_s = QString("SELECT * FROM em_infos where date = '%1';").arg(date);
    }else if(NULL == date){
        sql_s = QString("SELECT * FROM em_infos where department = '%1';").arg(department);
    }else{
        sql_s = QString("SELECT * FROM em_infos where department = '%1' and date = '%2';").arg(department).arg(date);
    }
    qDebug()<<sql_s;

    Em_infos data;
    if(!query.exec(sql_s)){
        qDebug() << "selectAll Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.id = query.value(0).toString();
        data.name = query.value(1).toString();
        data.department = query.value(2).toString();
        data.date = query.value(3).toString();
        data.amg = query.value(4).toString();
        data.amo = query.value(5).toString();
        data.pmg = query.value(6).toString();
        data.pmo = query.value(7).toString();
        data.nmg = query.value(8).toString();
        data.nmo = query.value(9).toString();
        data.info = query.value(10).toString();

        //获取到数据封装
        tmp_l.clear();
        for(int i = 0;i < 11;i++){
            tmp = query.value(i).toString();
            for(int ni = tmp.size(); ni < 10;ni++){
                tmp.append(" ");
            }
            tmp_l.append(tmp);

        }
        sql_data.append(tmp_l);
        sql_data.append("\n");
        qDebug()<<sql_data;
        //emit sendEm_infos(data);
    }
}

void sqlmodel::em_infos_select_for_date_department_json(QString department, QString date, QList<Em_infos> &json_data)
{
    QSqlQuery query;
    QString sql_s ;

    if(NULL == department && NULL == date){
        sql_s = QString("SELECT * FROM em_infos  ;");
    }else if(NULL == department){
        sql_s = QString("SELECT * FROM em_infos where date = '%1';").arg(date);
    }else if(NULL == date){
        sql_s = QString("SELECT * FROM em_infos where department = '%1';").arg(department);
    }else{
        sql_s = QString("SELECT * FROM em_infos where department = '%1' and date = '%2';").arg(department).arg(date);
    }
    qDebug()<<sql_s;

    Em_infos data;
    if(!query.exec(sql_s)){
        qDebug() << "selectAll Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.id = query.value(0).toString();
        data.name = query.value(1).toString();
        data.department = query.value(2).toString();
        data.date = query.value(3).toString();
        data.amg = query.value(4).toString();
        data.amo = query.value(5).toString();
        data.pmg = query.value(6).toString();
        data.pmo = query.value(7).toString();
        data.nmg = query.value(8).toString();
        data.nmo = query.value(9).toString();
        data.info = query.value(10).toString();

       json_data<<data;
    }
}

bool sqlmodel::em_infos_insert(Em_info &info)
{
    QSqlQuery query;
    QString sql_s = QString("insert into em_infos values('%1','%2','%3');").arg(info.id).arg(info.name).arg(info.department);

    if(!query.exec(sql_s)){
        qDebug() << "insert Failed!"<<query.lastError();
        return false;
    }
    return true;
}

void sqlmodel::em_infos_delete(QString id)
{
    QSqlQuery query;
    QString sql_s = QString("delete from em_info where id='%1' ;").arg(id);
    if(!query.exec(sql_s)){
        qDebug() << "deleteAll Failed!"<<query.lastError();

    }
}

void sqlmodel::em_infos_deleteAll()
{
    QSqlQuery query;
    QString sql_s = QString("delete from em_infos ;");
    if(!query.exec(sql_s)){
        qDebug() << "deleteAll Failed!"<<query.lastError();

    }
}

bool sqlmodel::em_infos_update(QString id, QString col_name, QString value)
{
    QSqlQuery query;
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString sql_s = QString("update em_infos set %1 = '%2' where id = '%3' and date = '%4';").arg(col_name).arg(value).arg(id).arg(date);
    if(!query.exec(sql_s)){
        qDebug() << "update Failed!"<<query.lastError();
        return false;
    }
    return true;
}

void sqlmodel::rule_selectAll(QStringList &list)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT name FROM rule;");
    QString data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }
    while(query.next()){
        data = query.value(0).toString();
        list<<data;
    }
}

void sqlmodel::rule_selectAll()
{
    QSqlQuery query;
    QString sql_s = QString("SELECT name FROM rule;");
    Rule data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.name = query.value(0).toString();

        emit sendRule(data);
    }
}

void sqlmodel::rule_select(QString name)
{
    QSqlQuery query;
    QString sql_s = QString("SELECT * FROM rule where name = '%1';").arg(name);
    Rule data;
    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();
        return;
    }

    while(query.next()){
        data.name = query.value(0).toString();
        data.amg = query.value(1).toString();
        data.amo = query.value(2).toString();
        data.pmg = query.value(3).toString();
        data.pmo = query.value(4).toString();
        data.nmg = query.value(5).toString();
        data.nmo = query.value(6).toString();

        emit sendRule(data);
    }
}

bool sqlmodel::rule_insert(Rule &info)
{
    QSqlQuery query;
    QString sql_s = QString("insert into rule values('%1','%2','%3','%4','%5','%6','%7');").arg(info.name).arg(info.amg).arg(info.amo).arg(info.pmg).arg(info.pmo).arg(info.nmg).arg(info.nmo);


    if(!query.exec(sql_s)){
        qDebug() << "insert Failed!"<<query.lastError();
        return false;
    }
    return true;
}

void sqlmodel::rule_delete(QString name)
{
    QSqlQuery query;
    QString sql_s = QString("delete from rule where name='%1' ;").arg(name);
    if(!query.exec(sql_s)){
        qDebug() << "delete Failed!"<<query.lastError();

    }
}

void sqlmodel::rule_deleteAll()
{
    QSqlQuery query;
    QString sql_s = QString("delete from rule ;");
    if(!query.exec(sql_s)){
        qDebug() << "deleteAll Failed!"<<query.lastError();

    }
}

bool sqlmodel::log_insert(Log &info)
{
    QSqlQuery query;
    QString sql_s = QString("insert into log values('%1','%2','%3','%4');").arg(info.id).arg(info.name).arg(info.time).arg(info.info);


    if(!query.exec(sql_s)){
        qDebug() << "insert Failed!"<<query.lastError();
        return false;
    }
    return true;
}

void sqlmodel::table_select(QString name)
{
    QSqlQuery query;
    QString sql_s = QString("select time from table where name = '%1';").arg(name);

    if(!query.exec(sql_s)){
        qDebug() << "select Failed!"<<query.lastError();

    }
    while(query.next()){
        QString data = query.value(0).toString();
        emit sendTable(data);
    }
}

bool sqlmodel::table_update(QString name, QString time)
{
    QSqlQuery query;
    QString sql_s = QString("update table set time = '%1' where name = '%2';").arg(time).arg(name);

    if(!query.exec(sql_s)){
        qDebug() << "update Failed!"<<query.lastError();
        return false;
    }
    return true;
}


