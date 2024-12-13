#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("医院诊疗系统 - 患者管理");
    
    // 设置开发者信息
    QString developerInfo = "开发者：[翁卓群] - [2022414040134]";
    ui->developerLabel->setText(developerInfo);
    
    setupModel();
    refreshTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (model) {
        delete model;
    }
}

void MainWindow::setupModel()
{
    model = new QSqlTableModel(this);
    model->setTable("patients");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    
    // 设置表头
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "性别");
    model->setHeaderData(3, Qt::Horizontal, "年龄");
    model->setHeaderData(4, Qt::Horizontal, "联系电话");
    model->setHeaderData(5, Qt::Horizontal, "病历号");
    model->setHeaderData(6, Qt::Horizontal, "诊断结果");
    
    ui->tableView->setModel(model);
}

void MainWindow::refreshTable()
{
    model->select();
}

void MainWindow::on_addButton_clicked()
{
    // 添加一个空行
    int row = model->rowCount();
    model->insertRow(row);
}

void MainWindow::on_editButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择一个患者记录！");
        return;
    }
    
    // 提交更改
    if (model->submitAll()) {
        QMessageBox::information(this, "成功", "患者信息已更新！");
    } else {
        QMessageBox::warning(this, "错误", "更新失败：" + model->lastError().text());
    }
}

void MainWindow::on_deleteButton_clicked()
{
    // 获取选中的行
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (!currentIndex.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择一个患者记录！");
        return;
    }
    
    // 确认删除
    if (QMessageBox::question(this, "确认", "确定要删除这条患者记录吗？") == QMessageBox::Yes) {
        model->removeRow(currentIndex.row());
        if (model->submitAll()) {
            QMessageBox::information(this, "成功", "患者记录已删除！");
        } else {
            QMessageBox::warning(this, "错误", "删除失败：" + model->lastError().text());
        }
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString searchText = ui->searchInput->text().trimmed();
    if (searchText.isEmpty()) {
        model->setFilter("");
    } else {
        // 在姓名和病历号中搜索
        QString filter = QString("name LIKE '%%1%' OR medical_record_number LIKE '%%1%'").arg(searchText);
        model->setFilter(filter);
    }
    model->select();
}

void MainWindow::on_refreshButton_clicked()
{
    ui->searchInput->clear();
    model->setFilter("");
    refreshTable();
}
