/**
 * \class MainWindow
 *
 *
 * \brief MainWindow w;
 *
 * This class can be accessible through the LoginWindow. If the
 * username and password fields are correct then the user can
 * add, remove and update data using the proper ui fields.
 *
 * Also, main tables Users and Books created in that window.
 *
 * \author Ali Emre Çakmakoğlu - Ayberk Zeray
 *
 * \version $Revision: 1.0 $
 *
 * \date $Date: 2015/05/20 22:22:19 $
 *
 * Contact: bilgi@aliemre.co
 *
 * Created on: Wednesday May 22:22:19 2015
 *
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_searchButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;
    void setupModel();
    void refreshTable();
};

#endif // MAINWINDOW_H
