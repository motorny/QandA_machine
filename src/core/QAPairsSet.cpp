#include <algorithm>

#include "QApairsSet.h"
#include "Vocabulary.h"

using namespace std;

const string QAPairsSet::delimetrs = " ,.!?";

void QAPairsSet::addPair(const std::string & question, const std::string & answer)
{
  pairsArr.push_back(QAPair(question, answer));
}

void QAPairsSet::getIndexByVocab(Vocabulary & vocabulary)
{
  vector<int> questionInds;

  // clear all idf fields for correct df (document frequency) calculating
  for (auto &wP : vocabulary) {
    wP.idf = 0.0;
  }


  for (auto &qaP : pairsArr)
  {
    qaP.wordIndeces = vocabulary.parseStrByVocabInds(qaP.question);

    // increase df for all words, which was met
    for (int wI : qaP.wordIndeces)
    {
      vocabulary[wI].idf += 1.0;
    }

    qaP.invEuqlidSize = 1 / sqrt((double)qaP.wordIndeces.size());
  }

  // calculate idf as log(N/df) where N = document (question) count
  for (auto &wP : vocabulary) {
    wP.idf = log((double)pairsArr.size() / wP.idf);
  }

}

size_t QAPairsSet::size()
{
  return pairsArr.size();
}

QAPairsSet::QAPair & QAPairsSet::operator[](size_t ind)
{
  return pairsArr[ind];
}

std::vector<QAPairsSet::QAPair>::iterator QAPairsSet::begin(void)
{
  return pairsArr.begin();
}

std::vector<QAPairsSet::QAPair>::iterator QAPairsSet::end(void)
{
  return pairsArr.end();
}

double QAPairsSet::QAPair::getDistFromQuery(Vocabulary &vocabulary, std::vector<int>& queryWordIndeces)
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
