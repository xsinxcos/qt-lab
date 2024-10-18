#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->num0 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num1 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num2 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num3 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num4 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num5 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num6 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num7 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num8 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));
    connect(ui->num9 ,SIGNAL(clicked()) ,this ,SLOT(btnNumberClicked()));

    connect(ui->plus ,SIGNAL(clicked()) ,this ,SLOT(btnBinaryOperatorClicked()));
    connect(ui->minus ,SIGNAL(clicked()) ,this ,SLOT(btnBinaryOperatorClicked()));
    connect(ui->multiple ,SIGNAL(clicked()) ,this ,SLOT(btnBinaryOperatorClicked()));
    connect(ui->divide ,SIGNAL(clicked()) ,this ,SLOT(btnBinaryOperatorClicked()));
    connect(ui->equal ,SIGNAL(clicked()) ,this ,SLOT(btnEqualClicked()));
    connect(ui->plusOrReduce, SIGNAL(clicked()), this, SLOT(on_plusOrReduce_clicked()));
    connect(ui->reciprocal, SIGNAL(clicked()), this, SLOT(on_reciprocal_clicked()));
    connect(ui->logarithm, SIGNAL(clicked()), this, SLOT(on_logarithm_clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_5_clicked()));
    connect(ui->takeRemainder, SIGNAL(clicked()), this, SLOT(on_takeRemainder_clicked()));
    connect(ui->CE, SIGNAL(clicked()), this, SLOT(on_CE_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if(operands.size() == 2 && opcodes.size() > 0){
        qDebug() << "进来了 ";
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        }else if(op == "-"){
            result = operand1 - operand2;
        }else if(op == "×"){
            result = operand1 * operand2;
        }else if(op == "➗"){
            result = operand1 / operand2;
        }else if(op == "%"){
            result = fmod(operand1, operand2);
        }
    }
    return QString::number(result);
}

void MainWindow::btnNumberClicked()
{
    QString oriStr = ui->lineEdit->text();
    QString str = qobject_cast<QPushButton*>(sender())->text();
    ui->lineEdit->setText(oriStr + str);
}




void MainWindow::on_point_clicked()
{
    QString oriStr = ui->lineEdit->text();
    QString str = qobject_cast<QPushButton*>(sender())->text();
    if(!oriStr.contains("."))
        ui->lineEdit->setText(oriStr + str);
}


void MainWindow::on_del_clicked()
{
    QString oriStr = ui->lineEdit->text();
    if(!oriStr.isEmpty())
        ui->lineEdit->setText(oriStr.left(oriStr.length() - 1));
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString oriStr = ui->lineEdit->text();
    operands.push(oriStr);
    QString op = qobject_cast<QPushButton*>(sender())->text();
    opcodes.push(op);
    ui->lineEdit->clear();

}

void MainWindow::btnEqualClicked()
{
    QString oriStr = ui->lineEdit->text();
    operands.push(oriStr);
    QString result = calculation();
    ui->lineEdit->setText(result);

    qDebug() << "计算结果: " << result;
    qDebug() << "操作数栈: " << operands;
    qDebug() << "操作符栈: " << opcodes;
}


void MainWindow::on_C_clicked()
{
    ui->lineEdit->clear();
    operands.clear();
    opcodes.clear();
}



void MainWindow::on_plusOrReduce_clicked()
{
    QString oriStr = ui->lineEdit->text();
    if (!oriStr.isEmpty()) {
        if (oriStr.startsWith("-")) {
            ui->lineEdit->setText(oriStr.mid(1));
        } else {
            ui->lineEdit->setText("-" + oriStr);
        }
    }
}

void MainWindow::on_reciprocal_clicked()
{
    QString oriStr = ui->lineEdit->text();
    bool ok;
    double value = oriStr.toDouble(&ok);
    if (ok && value != 0) {
        ui->lineEdit->setText(QString::number(1.0 / value));
    }
}

void MainWindow::on_logarithm_clicked()
{
    QString oriStr = ui->lineEdit->text();
    bool ok;
    double value = oriStr.toDouble(&ok);
    if (ok && value >= 0) {
        ui->lineEdit->setText(QString::number(sqrt(value)));
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString oriStr = ui->lineEdit->text();
    bool ok;
    double value = oriStr.toDouble(&ok);
    if (ok) {
        ui->lineEdit->setText(QString::number(value * value));
    }
}

void MainWindow::on_takeRemainder_clicked()
{
    if (operands.size() > 0) {
        QString oriStr = ui->lineEdit->text();
        operands.push(oriStr);
        QString op = "%";
        opcodes.push(op);
        ui->lineEdit->clear();
    }
}

void MainWindow::on_CE_clicked()
{
    ui->lineEdit->clear();
}
