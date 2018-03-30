#include <QString>
#include <QtTest>

#include <string>
#include <Windows.h>
#include <iostream>

#include "..\QAMachineCore.h"

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
  QAVocabulary v;
  QApairsQAset pSet;
  v.GenerateVocabularyFromQAset("testFiles/vocabTest.txt", "testFiles/vocabTestRejected_empty.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.GetWordInd(word) != -1), result);
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
  QAVocabulary v;
  QApairsQAset pSet;
  v.GenerateVocabularyFromQAset("testFiles/vocabTest.txt", "testFiles/vocabRejectionTest.txt", pSet);
  QFETCH(std::string, word);
  QFETCH(bool, result);
  QCOMPARE((v.GetWordInd(word) != -1), result);
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
  QAMachineCore core;

  core.LearnFromTSV("testFiles/QA_set.txt", "testFiles/vocabTestRejected_empty.txt");
  QFETCH(std::string, question);
  QFETCH(std::string, result);
  core.askQuestion(question);
  QVERIFY(core.getAnswer() == result);
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
