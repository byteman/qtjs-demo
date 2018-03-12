#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Bridge;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void loadProgress(int prog);
    void loadSuccess(bool result);
    void loadStarted();
private slots:
    void on_pushButton_clicked();

    void on_btnCalljs_clicked();

    void on_btnCalljs2_clicked();

    void on_btnLoad_clicked();

private:
    Ui::MainWindow *ui;
    Bridge *jsBridge;
    void reload();
};

#endif // MAINWINDOW_H
