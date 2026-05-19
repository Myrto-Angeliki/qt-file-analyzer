#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_selectFile_clicked();

    void on_analyzeFile_clicked();

    void on_wordToSearch_returnPressed();

    void on_enterSearch_clicked();

private:
    bool hasSelectedFile();
    QStringList analyzeFile(QString fileContents);
    QList<QPair<int,int>> searchInFile(QString fileContents, QString wordToFind);
    void highLightWordInFile(QList<QPair<int, int> > results);

    Ui::MainWindow *ui;
    QString m_origianlFileHtml;
};
#endif // MAINWINDOW_H
