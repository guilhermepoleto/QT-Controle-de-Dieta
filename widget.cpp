#include "widget.h"
#include "ui_widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->setWindowIcon(QIcon(":/rec/diet.ico"));
    ui->setupUi(this);
    QPixmap pixmap(":/rec/vcsupdaterequired_93493.ico");
    QIcon ButtonIcon(pixmap);
    ui->Refresh->setIcon(ButtonIcon);
    ui->Refresh->setIconSize(QSize(40, 40));
    QSqlDatabase bancoDedados = QSqlDatabase::addDatabase("QSQLITE");

    QString dir = qApp->applicationDirPath();
    QString banco = dir + "/db_Alimentos.db";
    this->setFixedSize(1000,580);

    bancoDedados.setDatabaseName(banco);
    if(!bancoDedados.open()) {
        QMessageBox::information(0,"Erro","Erro ao carregar banco de dados");
    }

    this->setWindowTitle("Controle de Dieta v1.0");
    ui->data->setText(DataString);
    setValores();
    loadAlimentos();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setValores()
{
    caloriasT = 0;
    carboT = 0;
    proteinasT = 0;
    gordurasT = 0;

}

void Widget::loadAlimentos()
{
    ui->combo1->clear();
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM table_tst");

    for (int i = 0; i < model->rowCount(); ++i) {
        vetorCal.append(model->record(i).value("Calorias").toFloat());
        vetorCarbo.append(model->record(i).value("Carboidratos").toFloat());
        vetorProt.append(model->record(i).value("Proteinas").toFloat());
        vetorGordura.append(model->record(i).value("Gorduras").toFloat());
        ui->combo1->addItem(model->record(i).value("Nome").toString());
    }
}

void Widget::WriteExcel(Document &xls, QString s, QString cal, QString carb, QString prot, QString gord, Format f){
    xls.write("C" + s, cal, f);
    xls.write("F" + s, carb, f);
    xls.write("I" + s, prot, f);
    xls.write("L" + s, gord, f);
}

void Widget::loadEXCEL()
{
    QXlsx::Document xlsx("Relatório.xlsx");
    Format formatTopo;
    formatTopo.setHorizontalAlignment(Format::AlignHCenter);
    formatTopo.setFontBold(1);
    formatTopo.setFontSize(12);
    Format formatNum;
    formatNum.setFontSize(12);
    formatNum.setFontItalic(1);
    formatNum.setHorizontalAlignment(Format::AlignHCenter);
    Format colorRed;
    colorRed.setPatternBackgroundColor(Qt::red);
    Format colorGreen;
    colorGreen.setPatternBackgroundColor(Qt::green);
    xlsx.write("A1", "Data", formatTopo);
    xlsx.write("C1", "Calorias", formatTopo);
    xlsx.write("D1", "Meta Cal", formatTopo);
    xlsx.write("F1", "Carboidratos", formatTopo);
    xlsx.write("G1", "Meta Carbo", formatTopo);
    xlsx.write("I1", "Proteínas", formatTopo);
    xlsx.write("J1", "Meta Prot", formatTopo);
    xlsx.write("L1", "Gorduras", formatTopo);
    xlsx.write("M1", "Meta Gord", formatTopo);
    xlsx.setColumnWidth(1,12);
    xlsx.setColumnWidth(4,12);
    xlsx.setColumnWidth(6,13);
    xlsx.setColumnWidth(7,12);
    xlsx.setColumnWidth(9,10);
    xlsx.setColumnWidth(10,12);
    xlsx.setColumnWidth(12,10);
    xlsx.setColumnWidth(13,12);
    for(int row = 3;row < 34;row++)
    {
        QString qrow = "A" + QString::number(row);
        if(!xlsx.read(qrow).isValid()) {
            QString date = xlsx.read("A" + QString::number(row-1)).toString();
            if(DataString == date){
                caloriasT+= xlsx.read("C" + QString::number(row-1)).toFloat();
                carboT+= xlsx.read("F" + QString::number(row-1)).toFloat();
                proteinasT+= xlsx.read("I" + QString::number(row-1)).toFloat();
                gordurasT+= xlsx.read("L" + QString::number(row-1)).toFloat();
                if(caloriasT > metaCAL)
                    xlsx.write("D" + QString::number(row-1), "", colorGreen);
                if(carboT > metaCarb)
                    xlsx.write("G" + QString::number(row-1), "", colorGreen);
                if(proteinasT > metaProt)
                    xlsx.write("J" + QString::number(row-1), "", colorGreen);
                if(gordurasT > metaGord)
                    xlsx.write("M" + QString::number(row-1), "", colorGreen);
                WriteExcel(xlsx, QString::number(row-1), QString::number(caloriasT,'f',2), QString::number(carboT,'f',2),
                     QString::number(proteinasT,'f',2), QString::number(gordurasT,'f',2), formatNum);
            }
            else {
                if(caloriasT > metaCAL)
                    xlsx.write("D" + QString::number(row), "", colorGreen);
                else {
                    xlsx.write("D" + QString::number(row), "", colorRed);
                }
                if(carboT > metaCarb)
                    xlsx.write("G" + QString::number(row), "", colorGreen);
                else
                    xlsx.write("G" + QString::number(row), "", colorRed);
                if(proteinasT > metaProt)
                    xlsx.write("J" + QString::number(row), "", colorGreen);
                else
                    xlsx.write("J" + QString::number(row), "", colorRed);
                if(gordurasT > metaGord)
                    xlsx.write("M" + QString::number(row), "", colorGreen);
                else
                    xlsx.write("M" + QString::number(row), "", colorRed);
                xlsx.write("A" + QString::number(row), DataString);
                WriteExcel(xlsx, QString::number(row), QString::number(caloriasT,'f',2), QString::number(carboT,'f',2),
                     QString::number(proteinasT,'f',2), QString::number(gordurasT,'f',2), formatNum);
            }
            xlsx.save();
            QFile file(desktop + "/Relatório.xlsx");
            QString exe = QCoreApplication::applicationDirPath();
            if(file.exists()) {
                file.remove();
            }
            QFile::copy(exe + "/Relatório.xlsx", desktop + "/Relatório.xlsx");
            break;
        }
    }
}

void Widget::on_AddButton_clicked()
{
    if(ui->peso->text() != "" && ui->combo1->currentIndex() != -1){
        if(cont!=0)
            ui->painelMaior->setText("");
        ui->painelMaior->setText((ui->painelMaior->toPlainText() + ui->combo1->currentText() + " - " + QString(ui->peso->text()) + " g" + "\n"));
        position = ui->combo1->currentIndex();

        caloriasT +=((vetorCal.at(position))) * ui->peso->text().toFloat();
        gordurasT +=((vetorGordura.at(position))) * ui->peso->text().toFloat();
        proteinasT+=((vetorProt.at(position))) * ui->peso->text().toFloat();
        carboT +=((vetorCarbo.at(position))) * ui->peso->text().toFloat();

        ui->peso->setText("");
        ui->combo1->setCurrentIndex(-1);
    }
}

void Widget::on_EndButton_clicked()
{
    if(ui->painelMaior->toPlainText() != "") {
        cont+=1;
        ui->painelMaior->setText("Total da Refeição \n \nCalorias: " + QString::number(caloriasT) + "\n" + "Carboidratos: " + QString::number(carboT) + "\n" + "Proteínas: " +
                                 QString::number(proteinasT) + "\n" + "Gorduras: " + QString::number(gordurasT));
        loadEXCEL();
        setValores();
    }
}

void Widget::on_AddAlimento_clicked()
{
    form2 = new PopUp1(this);
    form2->show();
}

void Widget::on_Refresh_clicked()
{
    loadAlimentos();
}

void Widget::on_Remover_clicked()
{
    if(ui->combo1->currentIndex() != -1){
    QSqlQuery query;
    query.exec("DELETE FROM table_tst WHERE Nome='" + ui->combo1->currentText() + "'");
    loadAlimentos();
    }
}
