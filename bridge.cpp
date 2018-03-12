#include "bridge.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument> 
#include <QMessageBox>
Bridge::Bridge(QObject *parent)
	: QObject(parent)
{

}

Bridge::~Bridge()
{

}

QString Bridge::title()
{
    return m_title;
}

void Bridge::setTitle(QString t)
{
    m_title = t;
}

void Bridge::test_public(QString title, QString text)
{
    QMessageBox::information(NULL,title,text);
}


void Bridge::test(QString title,QString text)
{
    QMessageBox::information(NULL,title,text);
}

void Bridge::testOneData()
{
    addOneData(100);
}

void Bridge::addOneData(int value)
{
    //static QString text = QString("%1").arg(value);
    QJsonObject o;
    o["data"] = value;
    emit addData(o);
}

void Bridge::getDatas()
{
	QJsonArray datacategories;	
	datacategories.push_back("group1");
	datacategories.push_back("group2");
	datacategories.push_back("group3");
	datacategories.push_back("group4");

	QJsonArray dataMatrix;	
	QJsonArray colData;	
			
	colData.push_back(11975); colData.push_back(5871); colData.push_back(8916); colData.push_back(2868);
	dataMatrix.push_back(colData); 
	while (colData.size()) {
		colData.pop_back();
	}

	
	colData.push_back(1951); colData.push_back(10048); colData.push_back(2060); colData.push_back(6171);
	dataMatrix.push_back(colData); 
	while (colData.size()) {
		colData.pop_back();
	}

	
	colData.push_back(8010); colData.push_back(16145); colData.push_back(8090); colData.push_back(8045);
	dataMatrix.push_back(colData);
	while (colData.size()) {
		colData.pop_back();
	}

	colData.push_back(1013); colData.push_back(990); colData.push_back(940); colData.push_back(6907);
	dataMatrix.push_back(colData); 
	while (colData.size()) {
		colData.pop_back();
	}

	QJsonObject dataName; QJsonArray dataNameSet;
	dataName["name"] = datacategories[0]; dataNameSet.push_back(dataName);
	dataName["name"] = datacategories[1]; dataNameSet.push_back(dataName);
	dataName["name"] = datacategories[2]; dataNameSet.push_back(dataName);
	dataName["name"] = datacategories[3]; dataNameSet.push_back(dataName);

	QJsonObject jsonObj;
	jsonObj["categories"] = datacategories;
	jsonObj["dataNames"] = dataNameSet;
	jsonObj["matrix"] = dataMatrix;

	QJsonObject title{
		{"text", QString("test data")},
		{"subtext", "provider: fj_gjx"},
		{"x", "right"},
		{"y", "bottom"},
	};

	QJsonObject restore{
		{"show", true},
		{"title", "refresh"}
	};

	QJsonArray type;
	type.push_back("force");
	type.push_back("chord");

	QJsonObject magicType{
		{"show", true},
		{"type", type}
	};

	QJsonObject saveAsImage{
		{"show", true}
	};

	QJsonObject feature{
		{"restore", restore },
		{"magicType", magicType},
		{"saveAsImage", saveAsImage}
	};

	QJsonObject toolbox{
		{"show", true},
		{"feature", feature }
	};

	QJsonObject legend{
		{"x", "left"},
		{"data", datacategories }
	};

	QJsonObject itemStyle{
		{"normal", QJsonValue(
					QJsonObject {
						{"label", QJsonValue(QJsonObject{{"show", false}}) }
					})}
	};

	QJsonObject serieData{
		{"type", "chord"},
		{"sort", "ascending"},
		{"sortSub", "descending"},
		{"showScale", true},
		{"showScaleText", true},
		{"data", dataNameSet },
		{"itemStyle", itemStyle },
		{"matrix", dataMatrix }
	};
	QJsonArray series; series.push_back(serieData);


	QJsonObject option
	{
		{"title", title },
		{"toolbox", toolbox },
		{"legend", legend },
		{"series", series }
	};

//	QJsonDocument jsonDoc(option);
//	QString str = jsonDoc.toJson().toStdString().c_str();



	updateData(option);
}
