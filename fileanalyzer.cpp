#include "fileanalyzer.h"

FileAnalyzer::FileAnalyzer(QObject *parent)
    : QObject{parent}
{}

QString FileAnalyzer::countWords(QString fileContents)
{
    m_wordsInFile = fileContents.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    int numOfWords = m_wordsInFile.size();

    return QString::number(numOfWords);
}

QStringList FileAnalyzer::findMostCommonWordsFromList(QList<QPair<QString, int> > fromList, int numOfWords)
{
    QStringList mostCommonWords;

    for(int i=fromList.size()-1; i>=fromList.size()-numOfWords; i--)
    {
        mostCommonWords.append(fromList.at(i).first);
    }
    return mostCommonWords;
}

QList<QPair<QString, int> > FileAnalyzer::merge(QList<QPair<QString, int> > list1, QList<QPair<QString, int> > list2)
{
    if(list1.first().second >= list2.last().second)
        return (list2 << list1);
    else if(list1.last().second <= list2.first().second)
        return (list1 << list2);
    else
    {
        QList<QPair<QString, int>> mergedList;
        int i= 0;
        int j=0;
        while(i<list1.size() && j<list2.size())
        {
            if(list1.at(i).second > list2.at(j).second)
            {
                mergedList.append(list2.at(j));
                j++;
            }
            else
            {
                mergedList.append(list1.at(i));
                i++;
            }
        }
        return (i == list1.size()) ? (mergedList << list2.last((list2.size() - j))) : (mergedList << list1.last((list1.size() - i)));
    }
}



QPair<bool, int> FileAnalyzer::containsWord(QList<QPair<QString, int> > wordLIst, QString word)
{
    for(int i=0; i<wordLIst.size(); i++)
    {
        if(wordLIst[i].first == word)
            return qMakePair(true,i);
    }
    return qMakePair(false,-1);
}

QList<QPair<QString, int>> FileAnalyzer::mergeSort(QList<QPair<QString, int>> listToSort)
{
    int listSize = listToSort.size();
    if(listSize > 2)
    {
        int middle1 = ceil(listSize/2.0);
        int middle2 = floor(listSize/2.0);
        QList<QPair<QString, int>> listUpper = mergeSort(listToSort.first(middle1));
        QList<QPair<QString, int>> listLower = mergeSort(listToSort.last(middle2));
        return merge(listUpper, listLower);
    }
    else if(listSize == 2)
        return (listToSort.at(0).second > listToSort.at(1).second) ? QList{listToSort.at(1), listToSort.at(0)} : QList{listToSort.at(0), listToSort.at(1)};
    else
        return listToSort;

}


QString FileAnalyzer::countLines(QString fileContents)
{
    int numOfLines = 1;

    for(int i=0; i<fileContents.size(); i++)
    {
        if(fileContents.at(i)=='\n' || fileContents.at(i)=='\r')
            numOfLines++;
    }
    return QString::number(numOfLines);
}

QStringList FileAnalyzer::findMostCommonWords(int numOfWords)
{
    if(m_wordsInFile.size() < numOfWords){

        return m_wordsInFile;
    }

    QList<QPair<QString, int>> wordCount;

    for(int i=0; i<m_wordsInFile.size(); i++)
    {
        QPair<bool,int> alreadyInList= containsWord(wordCount, m_wordsInFile[i]);
        if(alreadyInList.first)
            wordCount[alreadyInList.second].second += 1;
        else
            wordCount.append(qMakePair(m_wordsInFile[i],1));
    }

    wordCount = mergeSort(wordCount);
    return findMostCommonWordsFromList(wordCount, numOfWords);
}

QList<QPair<int, int> > FileAnalyzer::findWordAppearancesInFile(QString fileContents, QString wordToFInd)
{
    int indx = 0;
    QList<QPair<int, int> > coordinatesToHighlight;
    int wordToFIndLength = wordToFInd.length();

    while ((indx = fileContents.indexOf(wordToFInd, indx)) != -1) {
        //qDebug() << "Found <b> tag at index position" << j;
        coordinatesToHighlight.append(qMakePair(indx, (indx+wordToFIndLength)) );
        ++indx;
    }
    return coordinatesToHighlight;
}
