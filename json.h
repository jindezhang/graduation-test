#ifndef JSON_H
#define JSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include <allstruct.h>
#include <sqlmodel.h>
#include <netmodel.h>

class json
{
public:
    json();
    ~json();
    void em_infos_tojson(QList<Em_infos> &em, QString &json);
    void json_toem_infos(QString &json);//留空，直接判断OK就可以

    void json_toem_info(QString &json, QList<Em_info> &em);
    void em_infotojson(QString &json, QList<Em_info> &em);//接收em_info成功的json。

    void json_torule(QList<Rule> &em, QString &json);
    void rule_tojson(Rule &rule, QString &json);
    void rule_tojson(QString &json);//接收rule成功的json

    void config_tojson(QString &json);
    void json_toconfig(config &tmp_em, QString &json);

    void authority_tojson(QString &json);
    void json_toauthority(QString &json);//拿到数据直接插入、或者删除。authority_del,authority_add

    void add_tojson(QString value, QString &json);
    void json_toadd(QString &json, Em_info &tmp_em);

private:
    sqlmodel* sql;
    netmodel* net;
};

#endif // JSON_H
