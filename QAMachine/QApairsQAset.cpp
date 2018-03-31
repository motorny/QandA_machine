#include <algorithm>

#include "QApairsQAset.h"
#include "QAVocabulary.h"

using namespace std;

const string QApairsQAset::delimetrs = " ,.!?";

void QApairsQAset::AddPair(const std::string & question, const std::string & answer)
{
  pairsArr.push_back(QAPair(question, answer));
}

void QApairsQAset::IndexByVocab(QAVocabulary & vocabulary)
{
  string word;

  for (auto &qaP : pairsArr)
  {
    int wordsCnt = 0;
    int wordInd;
    size_t start = qaP.question.find_first_not_of(delimetrs), end = 0;
    while ((end = qaP.question.find_first_of(delimetrs, start)) != string::npos)
    {
      word = qaP.question.substr(start, end - start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      if ((wordInd = vocabulary.GetWordInd(word)) != -1)
          qaP.wordIndeces.push_back(wordInd);

      wordsCnt++;
      start = qaP.question.find_first_not_of(delimetrs, end);
    }
    if (start != std::string::npos)
    {
      word = qaP.question.substr(start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      if ((wordInd = vocabulary.GetWordInd(word)) != -1)
        qaP.wordIndeces.push_back(wordInd);

      wordsCnt++;
    }

    qaP.invEuqlidSize = 1 / sqrt((double)wordsCnt);
  }

}

size_t QApairsQAset::size()
{
  return pairsArr.size();
}

QApairsQAset::QAPair & QApairsQAset::operator[](size_t ind)
{
  return pairsArr[ind];
}

std::vector<QApairsQAset::QAPair>::iterator QApairsQAset::begin(void)
{
  return pairsArr.begin();
}

std::vector<QApairsQAset::QAPair>::iterator QApairsQAset::end(void)
{
  return pairsArr.end();
}

double QApairsQAset::QAPair::GetDistFromQuery(QAVocabulary &vocabulary, std::vector<int>& queryWordIndeces)
{
  double val = 0.0;

  for (size_t iQueryInd = 0; iQueryInd < queryWordIndeces.size(); ++iQueryInd)
  {
    for (size_t iDBQInd = iQueryInd; iDBQInd < wordIndeces.size(); ++iDBQInd)
    {
      if (queryWordIndeces[iQueryInd] == wordIndeces[iDBQInd])
        val += vocabulary[queryWordIndeces[iQueryInd]].idf;
    }
  }
  return val * invEuqlidSize;
}
