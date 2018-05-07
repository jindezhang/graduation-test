#include "json.h"
#include <sqlmodel.h>


/*

  {
    "commad":"em_infos",
    "data":[
           {},{}
    ]

  }
  */
json::json()
{
    sql = sqlmodel::get_model();
    net = netmodel::get_net();
}

json::~json()
{

}

void json::em_infos_tojson(QList <Em_infos> &em, QString &json)
{
    Em_infos tmp_em;
    QJsonObject data;//记录对象
    QJsonArray arr;
    QJsonObject obj;//json对象
    QJsonDocument doc;//json文档

   QList <Em_infos>::iterator iter;
   for(iter = em.begin(); iter != em.end(); iter++){
       tmp_em = *iter;
       data.insert("id",tmp_em.id);
       data.insert("name",tmp_em.name);
       data.insert("department",tmp_em.department);
       data.insert("date",tmp_em.date);
       data.insert("amg",tmp_em.amg);
       data.insert("amo",tmp_em.amo);
       data.insert("pmg",tmp_em.pmg);
       data.insert("pmo",tmp_em.pmo);
       data.insert("nmg",tmp_em.nmg);
       data.insert("nmo",tmp_em.nmo);
       data.insert("info",tmp_em.info);

       arr.append(QJsonValue(data));
   }

    obj.insert("command","em_infos");
    obj.insert("data",QJsonValue(arr));

    doc.setObject(obj);
    QByteArray byteArra = doc.toJson(QJsonDocument::Compact);
    json = QString(byteArra);

}

void json::json_toem_infos(QString &json)
{

}

void json::json_toem_info(QString &json, QList<Em_info> &em)
{
    Em_info tmp_em;
    QJsonParseError err;
    QJsonObject obj;
    QJsonValue value;
    QJsonArray arr;
    QJsonObject data;//记录对象
    QByteArray array = json.toLatin1();
    //检测是否json数据
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(doc.isNull() && err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_toem_info() error";
        return ;
    }
    obj = doc.object();
    value = obj.value("data");
    arr = value.toArray();
    int nSize = arr.size();

    for(int i = 0; i<nSize; i++){
        data = arr.at(i).toObject();
        tmp_em.id = data.value("id").toString();
        tmp_em.rfid = data.value("rfid").toString();
        tmp_em.name = data.value("name").toString();
        tmp_em.department = data.value("department").toString();
        tmp_em.icon = data.value("icon").toString();
        tmp_em.info = data.value("info").toString();
       em << tmp_em;
    }

}

void json::em_infotojson(QString &json, QList<Em_info> &em)
{
    Em_info tmp_em;
    QJsonObject data;//记录对象
    QJsonArray arr;
    QJsonObject obj;//json对象
    QJsonDocument doc;//json文档

   QList <Em_info>::iterator iter;
   for(iter = em.begin(); iter != em.end(); iter++){
       tmp_em = *iter;
       data.insert("id",tmp_em.id);
       data.insert("name",tmp_em.name);
       data.insert("department",tmp_em.department);

       data.insert("rfid",tmp_em.rfid);
       data.insert("info",tmp_em.info);
        data.insert("icon",tmp_em.icon);
       arr.append(QJsonValue(data));
   }

    obj.insert("command","em_info");
    obj.insert("data",QJsonValue(arr));

    doc.setObject(obj);
    QByteArray byteArra = doc.toJson(QJsonDocument::Compact);
    json = QString(byteArra);
}

void json::json_torule(QList<Rule> &em, QString &json)
{
    Rule tmp_em;
    QJsonParseError err;
    QJsonObject obj;
    QJsonValue value;
    QJsonArray arr;
    QJsonObject data;//记录对象
    QByteArray array = json.toLatin1();
    //检测是否json数据
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(doc.isNull() && err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_torule() error";
        return ;
    }
    obj = doc.object();
    value = obj.value("data");
    arr = value.toArray();
    int nSize = arr.size();

    for(int i = 0; i<nSize; i++){
        data = arr.at(i).toObject();
        tmp_em.nmo = data.value("nmo").toString();
        tmp_em.nmg = data.value("nmg").toString();
        tmp_em.name = data.value("name").toString();
        tmp_em.amo = data.value("amo").toString();
        tmp_em.amg = data.value("amg").toString();
        tmp_em.pmo = data.value("pmo").toString();
        tmp_em.pmg = data.value("pmg").toString();
       em << tmp_em;
    }
}



void json::rule_tojson(Rule &rule, QString &json)
{
    Rule tmp_em;
    QJsonObject data;//记录对象
    QJsonArray arr;
    QJsonObject obj;//json对象
    QJsonDocument doc;//json文档


       tmp_em = rule;
       data.insert("name",tmp_em.name);
       data.insert("amg",tmp_em.amg);
       data.insert("amo",tmp_em.amo);
       data.insert("pmg",tmp_em.pmg);
       data.insert("pmo",tmp_em.pmo);
       data.insert("nmg",tmp_em.nmg);
       data.insert("nmo",tmp_em.nmo);


       arr.append(QJsonValue(data));

    obj.insert("command","rule ");
    obj.insert("data",QJsonValue(arr));

    doc.setObject(obj);
    QByteArray byteArra = doc.toJson(QJsonDocument::Compact);
    json = QString(byteArra);
}

void json::rule_tojson(QString &json)
{

}

void json::config_tojson(QString &json)
{
    //因为配置文件只有一条，可以直接在这里拿到然后封装就好。

    config tmp_em;
    sql->config_select_all(tmp_em);

    QJsonObject data;//记录对象
    QJsonArray arr;
    QJsonObject obj;//json对象
    QJsonDocument doc;//json文档

   data.insert("rule",tmp_em.rule);
   data.insert("before",tmp_em.before);
   data.insert("after",tmp_em.after);
   data.insert("device",tmp_em.device);
   data.insert("upload",tmp_em.upload);
   arr.append(QJsonValue(data));

    obj.insert("command","config ");
    obj.insert("data",QJsonValue(arr));

    doc.setObject(obj);
    QByteArray byteArra = doc.toJson(QJsonDocument::Compact);
    json = QString(byteArra);
}

void json::json_toconfig(config &tmp_em, QString &json)
{

    QJsonParseError err;
    QJsonObject obj;
    QJsonValue value;
    QJsonArray arr;
    QJsonObject data;//记录对象
    QByteArray array = json.toLatin1();
    //检测是否json数据
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(doc.isNull() && err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_toconfig() error";
        return ;
    }
    obj = doc.object();
    value = obj.value("data");
    arr = value.toArray();
    int nSize = arr.size();

    for(int i = 0; i<nSize; i++){
        data = arr.at(i).toObject();
        tmp_em.rule = data.value("rule").toString();
        tmp_em.before = data.value("before").toString();
        tmp_em.after = data.value("after").toString();
        tmp_em.upload = data.value("upload").toString();

    }
}

void json::authority_tojson(QString &json)
{

}

void json::json_toauthority(QString &json)
{

    QJsonParseError err;
    QJsonObject obj;
    QJsonValue value;
    QJsonArray arr;
    QJsonObject data;//记录对象
    QByteArray array = json.toLatin1();
    //检测是否json数据
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(doc.isNull() && err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_toauthority() error";
        return ;
    }
    obj = doc.object();
    value = obj.value("data");
    arr = value.toArray();
    int nSize = arr.size();
    QString rfid;
    for(int i = 0; i<nSize; i++){
        data = arr.at(i).toObject();
        rfid = data.value("rfid").toString();
        if(json.contains("del")){
            if(sql->authority_delete(rfid))
               net->send_data("ok");
            else
                net->send_data("false");

        }else{
            if(sql->authority_insert(rfid))
                net->send_data("ok");
            else
                net->send_data("false");
        }


    }
}

void json::add_tojson(QString json, QString &value)
{
    QJsonObject obj;//json对象
    QJsonDocument doc;//json文档
    obj.insert("command","rfid_add");
    obj.insert("data",value);
    doc.setObject(obj);
    QByteArray byteArra = doc.toJson(QJsonDocument::Compact);
    json = QString(byteArra);
    qDebug()<<json;
}

void json::json_toadd(QString &json, Em_info &tmp_em)
{

    QJsonParseError err;
    QJsonObject obj;
    QJsonValue value;
    QJsonArray arr;
    QJsonObject data;//记录对象
    QByteArray array = json.toLatin1();
    //检测是否json数据
    QJsonDocument doc = QJsonDocument::fromJson(array,&err);
    if(doc.isNull() && err.error != QJsonParseError::NoError)
    {
        qDebug()<<"json_toem_info() error";
        return ;
    }
    obj = doc.object();
    value = obj.value("data");
    arr = value.toArray();

    data = arr.at(0).toObject();
    tmp_em.id = data.value("id").toString();
    tmp_em.name = data.value("name").toString();
    tmp_em.department = data.value("department").toString();


}
