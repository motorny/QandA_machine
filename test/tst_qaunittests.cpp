/*! \file
*  \brief QTests
*
*  This file contains tests of the project
*  This description is under reconstruction
*/
#include <QString>
#include <QtTest>

#include <string>
#include <list>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>

#include "QAMachineCore.h"

Q_DECLARE_METATYPE(std::string);

class QAUnitTests : public QObject
{
  Q_OBJECT

public:
  QAUnitTests();

  std::string relPath = "";
  private Q_SLOTS:
  void VocabularyTest_data();
  void VocabularyTest();
  void VocabularyRejectionTest_data();
  void VocabularyRejectionTest();
  void SimilarQuestionTest_data();
  void SimilarQuestionTest();
  void IdfTest_data();
  void IdfTest();
  void StrToIndexTest_data();
  void StrToIndexTest();
  void StemmerTest_data();
  void StemmerTest();
};



QAUnitTests::QAUnitTests()
{
  std::ifstream is("../../dataset/unit_test/vocabTest.txt");
  if (!is.is_open())
    relPath = std::string("../");
  else
    is.close();
}


void QAUnitTests::VocabularyTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<bool>("result");

  //std::cout << Stemmer::stem("переживший");
  QTest::newRow("vocab_data_1") << std::string("привет") << true;
  QTest::newRow("vocab_data_2") << std::string("вопрос") << true;
  QTest::newRow("vocab_data_3") << std::string("компьютер") << true;
  QTest::newRow("vocab_data_4") << std::string("обработк") << true;
  QTest::newRow("vocab_data_5") << std::string("программирован") << true;
  QTest::newRow("vocab_data_6") << std::string("часы") << false;
  QTest::newRow("vocab_data_7") << std::string("рак") << false;
  QTest::newRow("vocab_data_8") << std::string("стул") << false;
  QTest::newRow("vocab_data_9") << std::string("мышь") << false;
}

void QAUnitTests::VocabularyTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile(relPath + "../../dataset/unit_test/vocabTest.txt", relPath + "../../dataset/unit_test/vocabTestRejected_empty.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.getWordInd(word) != -1), result);
}

void QAUnitTests::VocabularyRejectionTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<bool>("result");

  QTest::newRow("vocab_rej_data_1") << std::string("привет") << true;
  QTest::newRow("vocab_rej_data_2") << std::string("компьютер") << true;
  QTest::newRow("vocab_rej_data_3") << std::string("обработк") << true;

  QTest::newRow("vocab_rej_data_4") << std::string("программирован") << true;
  QTest::newRow("vocab_rej_data_5") << std::string("вопрос") << false;
  QTest::newRow("vocab_rej_data_6") << std::string("кот") << false;

  QTest::newRow("vocab_rej_data_7") << std::string("блокнот") << false;
  QTest::newRow("vocab_rej_data_8") << std::string("предлог") << false;
}

void QAUnitTests::VocabularyRejectionTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile(relPath + "../../dataset/unit_test/vocabTest.txt", relPath + "../../dataset/unit_test/vocabRejectionTest.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.getWordInd(word) != -1), result);
}

void QAUnitTests::SimilarQuestionTest_data()
{
  QTest::addColumn<std::string>("question");
  QTest::addColumn<std::string>("result");

  QTest::newRow("answer_similar_data_1") << std::string("Кто выиграл олимпиаду 2018?") << std::string("Норвегия");
  QTest::newRow("answer_similar_data_2") << std::string("Какая самая быстрая машина в мире?") << std::string("Феррари");
  QTest::newRow("answer_similar_data_3") << std::string("Какого цвета солнце?") << std::string("Зеленое");
  QTest::newRow("answer_similar_data_4") << std::string("Кто первый русский космонавт?") << std::string("Юрий Гагарин");
}

void QAUnitTests::SimilarQuestionTest()
{
  QAMachineCore core;

  core.learnFromFile(relPath + "../../dataset/unit_test/QA_set.txt", relPath + "../../dataset/unit_test/vocabTestRejected_empty.txt");
  QFETCH(std::string, question);
  QFETCH(std::string, result);
  core.askQuestion(question);
  QVERIFY(core.getAnswer() == result);
}

void QAUnitTests::IdfTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<double>("expIdf");

  QTest::newRow("idf_data_1") << std::string("Кт") << (log(4.0 / 2.0));
  QTest::newRow("idf_data_2") << std::string("выигра") << (log(4.0 / 1.0));
  QTest::newRow("idf_data_3") << std::string("2018") << (log(4.0 / 1.0));
  QTest::newRow("idf_data_4") << std::string("в") << (log(4.0 / 1.0));
}

void QAUnitTests::IdfTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile(relPath + "../../dataset/unit_test/QA_Set.txt", relPath + "../../dataset/unit_test/vocabTestRejected_empty.txt", pSet);
  pSet.getIndexByVocab(v);
  QFETCH(std::string, word);
  QFETCH(double, expIdf);
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  int cInd = v.getWordInd(word);
  QCOMPARE((v[cInd].idf), expIdf);
}

void QAUnitTests::StrToIndexTest_data()
{
}

void QAUnitTests::StrToIndexTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile(relPath + "../../dataset/unit_test/QA_Set.txt", relPath + "../../dataset/unit_test/vocabTestRejected_empty.txt", pSet);
  pSet.getIndexByVocab(v);

  std::list<int> expIndList_data1;  
  expIndList_data1.push_back(v.getWordInd("кт"));
  expIndList_data1.push_back(v.getWordInd("выигра"));
  expIndList_data1.push_back(v.getWordInd("олимпиад"));
  expIndList_data1.push_back(v.getWordInd("2018"));
  expIndList_data1.sort();

  std::vector<int> res = v.parseStrByVocabInds(pSet[0].question);
  std::list<int> indList_data1(res.begin(), res.end());
  indList_data1.sort();

  QVERIFY(indList_data1 == expIndList_data1);

  std::list<int> expIndList_data2;
  expIndList_data2.push_back(v.getWordInd("как"));
  expIndList_data2.push_back(v.getWordInd("цвет"));
  expIndList_data2.push_back(v.getWordInd("солнц"));
  expIndList_data2.sort();

  res = v.parseStrByVocabInds(pSet[2].question);
  std::list<int> indList_data2(res.begin(), res.end());
  indList_data2.sort();

  QVERIFY(indList_data2 == expIndList_data2);
}

void QAUnitTests::StemmerTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<std::string>("stem");

  QTest::newRow("stemmer_data_1") << std::string("важная") << std::string("важн");
  QTest::newRow("stemmer_data_2") << std::string("важничал") << std::string("важнича");
  QTest::newRow("stemmer_data_3") << std::string("валился") << std::string("вал");
  QTest::newRow("stemmer_data_4") << std::string("мывши") << std::string("м");
  QTest::newRow("stemmer_data_5") << std::string("колхоз") << std::string("колхоз");
  QTest::newRow("stemmer_data_6") << std::string("колхозный") << std::string("колхозн");
  QTest::newRow("stemmer_data_7") << std::string("в") << std::string("в");
  QTest::newRow("stemmer_data_8") << std::string("важнейшим") << std::string("важн");
  QTest::newRow("stemmer_data_9") << std::string("вальсе") << std::string("вальс");

}

void QAUnitTests::StemmerTest() 
{
  
  QFETCH(std::string, word);
  QFETCH(std::string, stem);
  QCOMPARE(Stemmer::stem(word), stem);
}

int main(int argc, char *argv[]) \
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  QAUnitTests tc;
  QTest::setMainSourcePath(__FILE__, ".");
  return QTest::qExec(&tc, argc, argv);
}
#include "tst_qaunittests.moc"
