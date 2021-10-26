#include "popup1.h"
#include "ui_popup1.h"

PopUp1::PopUp1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopUp1)
{
    ui->setupUi(this);
    this->setWindowTitle("Cadastro");
    ui->AddNome->setFocus();
}

PopUp1::~PopUp1()
{
    delete ui;
}

QString PopUp1::regradeTres(float number, float qnt)
{
    return(QString::number(number/qnt));
}

void PopUp1::on_buttonBox_accepted()
{
    if(ui->AddNome->text() != "" && ui->AddCal->text() != "" && ui->AddCarbo->text() != "" && ui->AddProt->text() != "" && ui->AddGordura->text() != "") {
        QString nome = ui->AddNome->text();
        QString cal = regradeTres(ui->AddCal->text().toFloat(),ui->AddQnt->text().toFloat());
        QString carbo = regradeTres(ui->AddCarbo->text().toFloat(),ui->AddQnt->text().toFloat());
        QString prot = regradeTres(ui->AddProt->text().toFloat(),ui->AddQnt->text().toFloat());
        QString gordura = regradeTres(ui->AddGordura->text().toFloat(),ui->AddQnt->text().toFloat());

        QSqlQuery query;
        query.prepare("insert into table_tst (Nome,Calorias,Carboidratos,Proteinas,Gorduras) values ('"+nome+"',"+cal+","+carbo+","+prot+","+gordura+")");
        query.exec();
    }
    else
        QMessageBox::information(0,"Erro","Campo inválido");
}

void PopUp1::on_buttonBox_rejected()
{

}

