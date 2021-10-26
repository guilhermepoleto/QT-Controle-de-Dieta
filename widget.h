#ifndef WIDGET_H
#define WIDGET_H

#include "popup1.h"
#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>
#include <QVariant>
#include <QVector>
#include <QDate>
#include <QTextStream>
#include <QDir>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QDesktopWidget>
#include <QtXlsx>
#include <QImage>

using namespace QXlsx;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void loadAlimentos();
    void loadEXCEL();
    void setValores();
    void WriteExcel(Document &xls, QString s, QString cal, QString carb, QString prot, QString gord, Format f);

private slots:
    void on_AddButton_clicked();

    void on_EndButton_clicked();

    void on_AddAlimento_clicked();

    void on_Refresh_clicked();

    void on_Remover_clicked();

private:
    Ui::Widget *ui;
    QComboBox *comboadd;
    PopUp1 *form2;
    int n = 0;
    int c;
    int cont = 0;
    int position;
    float caloriasT = 0;
    float carboT = 0;
    float proteinasT = 0;
    float gordurasT = 0;
    float metaCAL = 2000;
    float metaCarb = 186;
    float metaProt = 124;
    float metaGord = 85;
    QVector<float> vetorCal;
    QVector<float> vetorCarbo;
    QVector<float> vetorProt;
    QVector<float> vetorGordura;
    QString desktop = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDate Data = QDate::currentDate();
    QString DataString = Data.toString("dd.MM.yyyy");

};
#endif // WIDGET_H
