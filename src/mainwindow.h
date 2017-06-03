#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QApplication &app, QWidget *parent = 0);
  ~MainWindow();

  void connectUi();

public slots:

  void quit();

private:
  Ui::MainWindow *ui;

  QApplication *m_app;
};

#endif // MAINWINDOW_H
