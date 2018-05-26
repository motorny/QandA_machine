#include "tst_qaunittests.h"
#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <fstream>

QAUnitTests::QAUnitTests()
{
  std::ifstream is("../../dataset/unit_test/vocabTest.txt");
  if (!is.is_open())
    relPath = std::string("../");
  else
    is.close();

  std::ifstream dataStringsIS(relPath + "../../dataset/unit_test/dataStrings.txt");
  std::string str;
  while (std::getline(dataStringsIS, str))
  {
    dataStrArr.push_back(str);
  }
  dataStringsIS.close();
}


void QAUnitTests::VocabularyTest_data()
{
  QTest::addColumn<std::string>("word");
  QTest::addColumn<bool>("result");

  QTest::newRow("vocab_data_1") << dataStrArr[0] << true;
  QTest::newRow("vocab_data_2") << dataStrArr[1] << true;
  QTest::newRow("vocab_data_3") << dataStrArr[2] << true;
  QTest::newRow("vocab_data_4") << dataStrArr[3] << true;
  QTest::newRow("vocab_data_5") << dataStrArr[4] << true;
  QTest::newRow("vocab_data_6") << dataStrArr[5] << false;
  QTest::newRow("vocab_data_7") << dataStrArr[6] << false;
  QTest::newRow("vocab_data_8") << dataStrArr[7] << false;
  QTest::newRow("vocab_data_9") << dataStrArr[8] << false;
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

  QTest::newRow("vocab_rej_data_1") << dataStrArr[0] << true;
  QTest::newRow("vocab_rej_data_2") << dataStrArr[1] << false;
  QTest::newRow("vocab_rej_data_3") << dataStrArr[2] << true;
  QTest::newRow("vocab_rej_data_4") << dataStrArr[3] << true;
  
  QTest::newRow("vocab_rej_data_5") << dataStrArr[4] << true;
  QTest::newRow("vocab_rej_data_6") << dataStrArr[9] << false;

  QTest::newRow("vocab_rej_data_7") << dataStrArr[10] << false;
  QTest::newRow("vocab_rej_data_8") << dataStrArr[11] << false;
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

  QTest::newRow("answer_similar_data_1") << dataStrArr[12] << dataStrArr[13];
  QTest::newRow("answer_similar_data_2") << dataStrArr[14] << dataStrArr[15];
  QTest::newRow("answer_similar_data_3") << dataStrArr[16] << dataStrArr[17];
  QTest::newRow("answer_similar_data_4") << dataStrArr[18] << dataStrArr[19];
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

  QTest::newRow("idf_data_1") << dataStrArr[20] << (log(4.0 / 2.0));
  QTest::newRow("idf_data_2") << dataStrArr[21] << (log(4.0 / 1.0));
  QTest::newRow("idf_data_3") << dataStrArr[22] << (log(4.0 / 1.0));
  QTest::newRow("idf_data_4") << dataStrArr[23] << (log(4.0 / 1.0));
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
  expIndList_data1.push_back(v.getWordInd(dataStrArr[20]));
  expIndList_data1.push_back(v.getWordInd(dataStrArr[21]));
  expIndList_data1.push_back(v.getWordInd(dataStrArr[22]));
  expIndList_data1.push_back(v.getWordInd(dataStrArr[24]));
  expIndList_data1.sort();

  std::vector<int> res = v.parseStrByVocabInds(pSet[0].question);
  std::list<int> indList_data1(res.begin(), res.end());
  indList_data1.sort();

  QVERIFY(indList_data1 == expIndList_data1);

  std::list<int> expIndList_data2;
  expIndList_data2.push_back(v.getWordInd(dataStrArr[25]));
  expIndList_data2.push_back(v.getWordInd(dataStrArr[26]));
  expIndList_data2.push_back(v.getWordInd(dataStrArr[27]));
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

  QTest::newRow("stemmer_data_1") << dataStrArr[28] << dataStrArr[29];
  QTest::newRow("stemmer_data_2") << dataStrArr[30] << dataStrArr[31];
  QTest::newRow("stemmer_data_3") << dataStrArr[32] << dataStrArr[33];
  QTest::newRow("stemmer_data_4") << dataStrArr[34] << dataStrArr[35];
  QTest::newRow("stemmer_data_5") << dataStrArr[36] << dataStrArr[37];
  QTest::newRow("stemmer_data_6") << dataStrArr[38] << dataStrArr[39];
  QTest::newRow("stemmer_data_7") << dataStrArr[40] << dataStrArr[41];
  QTest::newRow("stemmer_data_8") << dataStrArr[42] << dataStrArr[43];
  QTest::newRow("stemmer_data_9") << dataStrArr[44] << dataStrArr[45];

}

void QAUnitTests::StemmerTest() 
{
  
  QFETCH(std::string, word);
  QFETCH(std::string, stem);
  QCOMPARE(Stemmer::stem(word), stem);
}



int main(int argc, char *argv[]) 
{
  setlocale(LC_ALL, "Russian");
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  QAUnitTests tc;
  QTest::setMainSourcePath(__FILE__, ".");
  return QTest::qExec(&tc, argc, argv);
}

