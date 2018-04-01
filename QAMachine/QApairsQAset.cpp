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
  vector<int> questionInds;

  for (auto &qaP : pairsArr)
  {
    qaP.wordIndeces = vocabulary.ParseStrByVocabInds(qaP.question);

    qaP.invEuqlidSize = 1 / sqrt((double)qaP.wordIndeces.size());
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
