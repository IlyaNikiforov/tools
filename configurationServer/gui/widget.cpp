#include "widget.h"
#include "ui_widget.h"

#include "preferencesDialog.h"

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
}

Widget::~Widget()
{
	delete ui;
}

void Widget::init()
{
	server = new Server;
	PreferencesDialog * dialog = new PreferencesDialog();
	dialog->init(new QAction(dialog), new QAction(dialog), new QAction(dialog), new QAction(dialog));
	ui->widgetSettings->layout()->addWidget(dialog);
	dialog->setParent(ui->widgetSettings);
	connect(server, SIGNAL(newClient(QString)), this, SLOT(addNewClient(QString)));
	connect(server, SIGNAL(clientDisconnectedSignal(QString)), this, SLOT(deleteClient(QString)));
	setWindowTitle(" Adress: " + QString::number(server->getAdress()));
	QString allIP = server->getIP();
	int i = 0;
//	while (i < allIP.length())
//	{
//		while (allIP[i] != '\n')
//			i++;
//		QString temp;
//		for (int j = 0; j < i; j++)
//			temp[j] = allIP[i + j];
//		ui->widgetListOfIP->addItem(allIP.remove(0, i));
//		i++;
//	}
	for(i = 0; i < allIP.count("\n"); i++)
	{
		QString temp = allIP;
		ui->widgetListOfIP->addItem(temp.remove(temp.indexOf('\n'), temp.length() - temp.indexOf('\n')));
		//ui->widgetListOfIP->addItem(allIP.remove(0, allIP.indexOf('\n') + 1));
		allIP = allIP.remove(0, allIP.indexOf('\n') + 1);
	}
	ui->widgetListOfIP->addItem(allIP.remove(allIP.length() - 1, 1));

	//ui->widgetListOfIP->addItem(server->getIP());
}

void Widget::addNewClient(QString newClient)
{
	ui->widgetListOfNames->addItem(newClient);
}

void Widget::deleteClient(QString clientsIP)
{
	for (int i = 0; i < ui->widgetListOfNames->count(); i++)
		if (ui->widgetListOfNames->item(i)->text() == clientsIP)
		{
			delete ui->widgetListOfNames->item(i);
			return;
		}
}