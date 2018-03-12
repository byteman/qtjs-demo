#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>

class Bridge : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle USER true)
public:
	Bridge(QObject *parent);
	~Bridge();
    QString title();
    void setTitle(QString t);
    //从js调用公共方法必须加入Q_INVOKABLE
    Q_INVOKABLE void test_public(QString title,QString text);
    void addOneData(int value);
public slots:
    //可以在js中直接调用slots中的方法.
	void getDatas();
    void test(QString title,QString text);
    void testOneData();
 signals:
    //一般js中注册该消息，然后c++中产生事件，调用js的代码.
	void updateData(const QJsonObject& jsonData);
    void addData(const QJsonObject& data);

private:
    QString m_title;
};

#endif // BRIDGE_H
