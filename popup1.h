#ifndef POPUP1_H
#define POPUP1_H

#include <QDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>

namespace Ui {
class PopUp1;
}

class PopUp1 : public QDialog
{
    Q_OBJECT

public:
    explicit PopUp1(QWidget *parent = nullptr);
    QString regradeTres(float number, float qnt);
    ~PopUp1();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PopUp1 *ui;
};

#endif // POPUP1_H
