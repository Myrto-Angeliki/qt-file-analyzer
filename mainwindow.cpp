#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileanalyzer.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFile_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(
        this,
        tr("Select file"),
        "C:\\Users\\user\\Documents\\",
        "All files (*.*);;Text File (*.txt);;Log File (*.log)"
        );
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"info",file.errorString());
        return;
    }
    const QString str = QString::fromUtf8(file.readAll());
    ui->textBrowser->setText(str);
    ui->selectedFile->setText(fileName);
    m_origianlFileHtml = ui->textBrowser->toHtml();
}



QStringList MainWindow::analyzeFile(QString fileContents)
{
    FileAnalyzer fileAnalyzer;
    QStringList results = (QStringList{fileAnalyzer.countLines(fileContents),
                                       fileAnalyzer.countWords(fileContents)}
                           << fileAnalyzer.findMostCommonWords());

    return results;
}


bool MainWindow::hasSelectedFile()
{
    if(ui->selectedFile->text()=="")
    {
        QMessageBox::information(0,"Warning","You must first select a file!");
        return false;
    }
    return true;
}


void MainWindow::on_analyzeFile_clicked()
{
    if(!hasSelectedFile()) return;

    QFuture<QStringList> future = QtConcurrent::run(&MainWindow::analyzeFile, this, ui->textBrowser->toPlainText());

    auto * watcher = new QFutureWatcher<QStringList>(this);

    connect(watcher, &QFutureWatcher<QStringList>::finished, this,
            [this, watcher]()
            {
                QStringList results = watcher->result();
                ui->numOfLines->setText(results.at(0));
                ui->numOfWords->setText(results.at(1));
                QString str = "";
                for(int i=2; i<results.size(); i++)
                {
                    str += (i!=results.size()-1) ? ("\"" + results.at(i) + "\"" + " ,\t"): ("\"" + results.at(i) + "\"" );
                }
                ui->mostCommonWords->setText(str);
            }
    );

    watcher->setFuture(future);
}


void MainWindow::highLightWordInFile(QList<QPair<int, int> > results)
{
    int begin;
    int end;
    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    QTextCursor cursor(ui->textBrowser->document());
    for(int i=0; i<results.size(); i++)
    {
        begin = results.at(i).first;
        end = results.at(i).second;
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);

    }
}


QList<QPair<int, int> > MainWindow::searchInFile(QString fileContents, QString wordToFind)
{
    FileAnalyzer fileAnalyzer;
    return fileAnalyzer.findWordAppearancesInFile(fileContents, wordToFind);
}



void MainWindow::on_wordToSearch_returnPressed()
{
    if(!hasSelectedFile()) return;

    ui->textBrowser->setHtml(m_origianlFileHtml);


    QFuture<QList<QPair<int, int> >> future = QtConcurrent::run(&MainWindow::searchInFile, this, ui->textBrowser->toPlainText(), ui->wordToSearch->text());
    auto * watcher = new QFutureWatcher<QList<QPair<int, int> >>(this);

    connect(watcher, &QFutureWatcher<QList<QPair<int, int> >>::finished, this,
            [this, watcher]()
            {
                highLightWordInFile(watcher->result());
            }
            );

    watcher->setFuture(future);
}


void MainWindow::on_enterSearch_clicked()
{
    on_wordToSearch_returnPressed();
}