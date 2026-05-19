#ifndef FILEANALYZER_H
#define FILEANALYZER_H

#include "fileanalyzer.h"

#include <QObject>
#include <QDebug>
#include <QRegularExpression>


class FileAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit FileAnalyzer(QObject *parent = nullptr);

    QString countLines(QString fileContents);
    QString countWords(QString fileContents);
    QStringList findMostCommonWords(int numOfWords = 3);
    QList<QPair<int, int>> findWordAppearancesInFile(QString fileContents, QString wordTOFInd);

private:
    QStringList findMostCommonWordsFromList(QList<QPair<QString, int>> fromList, int numOfWords);
    QList<QPair<QString, int>> mergeSort(QList<QPair<QString, int>> listToSort);
    QList<QPair<QString, int>> merge(QList<QPair<QString, int>> list1, QList<QPair<QString, int>> list2);
    QPair<bool, int> containsWord(QList<QPair<QString, int>> wordLIst, QString word);
    QStringList m_wordsInFile;
};

#endif // FILEANALYZER_H
