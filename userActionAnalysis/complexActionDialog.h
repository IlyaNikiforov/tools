#pragma once

#include <QtWidgets/QDialog>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include "userAction/complexUserAction/complexUserActionGenerator.h"
#include "propertiesDialog.h"
#include "complexActionNameDialog.h"
#include "widgetItemProperty/widgetItemCustomPropertyList.h"
#include "userAction/complexUserAction/complexUserActionList.h"
#include "ruleElement.h"

namespace Ui {
class ComplexActionDialog;
}

class ComplexActionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ComplexActionDialog(QWidget *parent = 0
			, BaseUserActionList baseUserActions = BaseUserActionList()
			, ComplexUserActionList complexUserActions = ComplexUserActionList());
	~ComplexActionDialog();

	QStringList initComplexActionTreeWidget();
public slots:
	void addActionToRuleList();
	void deleteActionFromRuleList();
	void openProperties(QTreeWidgetItem *item);
	void updateCustomProperties();
	void openNameDialogComplexAction();
	void saveComplexAction();
	void addNewComplexAction(ComplexUserAction *action);

signals:
	void newComplexActionCreated(ComplexUserAction *complexUserAction);

private:
	QStringList initBaseActionListWidget();
	void initComplexAction(ComplexUserAction *complexUserAction, QTreeWidgetItem *item, int const &column);
	void addBaseActionToRuleWidget(QTreeWidgetItem *parent, const QString &name, const QMap<QString, QString> &disabledProperties);
	void addComplexActionToRuleWidget(QTreeWidgetItem *parent, ComplexUserAction *complexUserAction);
	RuleElement *parseRuleTreeItem(QTreeWidgetItem *item);
	void printRuleElements(QList<RuleElement *> ruleElements);

	Ui::ComplexActionDialog *ui;

	BaseUserActionList mBaseUserActions;
	ComplexUserActionList mComplexUserActions;

	PropertiesDialog *mPropertiesDialog;
	ComplexActionNameDialog *mComplexActionNameDialog;
	WidgetItemCustomPropertyList mWidgetItemCustomPropertyList;
	QTreeWidgetItem *mOpenedRuleItem;
	ComplexUserActionGenerator *mComplexUserActionGenerator;

	QMap<QTreeWidgetItem *, QMap<QString, QString>> mDisabledProperties;
};