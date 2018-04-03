#include <QString>
#include <QtTest>

#include <string>
#include <list>
#include <vector>
#include <Windows.h>
#include <iostream>

#include "..\MachineCore.h"

Q_DECLARE_METATYPE(std::string);

class QAUnitTests : public QObject
{
  Q_OBJECT

public:
  QAUnitTests();

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
};



QAUnitTests::QAUnitTests()
{
}

void QAUnitTests::VocabularyTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<bool>("result");

  QTest::newRow("vocab_data_1") << std::string("������") << true;
  QTest::newRow("vocab_data_2") << std::string("������") << true;
  QTest::newRow("vocab_data_3") << std::string("���������") << true;
  QTest::newRow("vocab_data_4") << std::string("���������") << true;
  QTest::newRow("vocab_data_5") << std::string("����������������") << true;
  QTest::newRow("vocab_data_6") << std::string("����") << false;
  QTest::newRow("vocab_data_7") << std::string("���") << false;
  QTest::newRow("vocab_data_8") << std::string("����") << false;
  QTest::newRow("vocab_data_9") << std::string("����") << false;
}


void QAUnitTests::VocabularyTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile("testFiles/vocabTest.txt", "testFiles/vocabTestRejected_empty.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.getWordInd(word) != -1), result);
}

void QAUnitTests::VocabularyRejectionTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<bool>("result");

  QTest::newRow("vocab_rej_data_1") << std::string("������") << true;
  QTest::newRow("vocab_rej_data_2") << std::string("���������") << true;
  QTest::newRow("vocab_rej_data_3") << std::string("���������") << true;

  QTest::newRow("vocab_rej_data_4") << std::string("����������������") << false;
  QTest::newRow("vocab_rej_data_5") << std::string("������") << false;
  QTest::newRow("vocab_rej_data_6") << std::string("���") << false;

  QTest::newRow("vocab_rej_data_7") << std::string("�������") << false;
  QTest::newRow("vocab_rej_data_8") << std::string("�������") << false;
}

void QAUnitTests::VocabularyRejectionTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile("testFiles/vocabTest.txt", "testFiles/vocabRejectionTest.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.getWordInd(word) != -1), result);
}

void QAUnitTests::SimilarQuestionTest_data()
{
  QTest::addColumn<std::string>("question");
  QTest::addColumn<std::string>("result");

  QTest::newRow("answer_similar_data_1") << std::string("��� ������� ��������� 2018?") << std::string("��������");
  QTest::newRow("answer_similar_data_2") << std::string("����� ����� ������� ������ � ����?") << std::string("�������");
  QTest::newRow("answer_similar_data_3") << std::string("������ ����� ������?") << std::string("�������");
  QTest::newRow("answer_similar_data_4") << std::string("��� ������ ������� ���������?") << std::string("���� �������");
}

void QAUnitTests::SimilarQuestionTest()
{
  MachineCore core;

  core.learnFromTSV("testFiles/QA_set.txt", "testFiles/vocabTestRejected_empty.txt");
  QFETCH(std::string, question);
  QFETCH(std::string, result);
  core.askQuestion(question);
  QVERIFY(core.getAnswer() == result);
}

void QAUnitTests::IdfTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<double>("expIdf");

  QTest::newRow("idf_data_1") << std::string("���") << (log(4.0 / 2.0));
  QTest::newRow("idf_data_2") << std::string("�������") << (log(4.0 / 1.0));
  QTest::newRow("idf_data_3") << std::string("2018") << (log(4.0 / 1.0));
  QTest::newRow("idf_data_4") << std::string("�") << (log(4.0 / 1.0));
}

void QAUnitTests::IdfTest()
{
  Vocabulary v;
  QAPairsSet pSet;
  v.generateVocabularyFromQAFile("testFiles/QA_Set.txt", "testFiles/vocabTestRejected_empty.txt", pSet);
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
  v.generateVocabularyFromQAFile("testFiles/QA_Set.txt", "testFiles/vocabTestRejected_empty.txt", pSet);
  pSet.getIndexByVocab(v);

  std::list<int> expIndList_data1;  
  expIndList_data1.push_back(v.getWordInd("���"));
  expIndList_data1.push_back(v.getWordInd("�������"));
  expIndList_data1.push_back(v.getWordInd("���������"));
  expIndList_data1.push_back(v.getWordInd("2018"));
  expIndList_data1.sort();

  std::vector<int> res = v.parseStrByVocabInds(pSet[0].question);
  std::list<int> indList_data1(res.begin(), res.end());
  indList_data1.sort();

  QVERIFY(indList_data1 == expIndList_data1);

  std::list<int> expIndList_data2;
  expIndList_data2.push_back(v.getWordInd("������"));
  expIndList_data2.push_back(v.getWordInd("�����"));
  expIndList_data2.push_back(v.getWordInd("������"));
  expIndList_data2.sort();

  res = v.parseStrByVocabInds(pSet[2].question);
  std::list<int> indList_data2(res.begin(), res.end());
  indList_data2.sort();

  QVERIFY(indList_data2 == expIndList_data2);
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
