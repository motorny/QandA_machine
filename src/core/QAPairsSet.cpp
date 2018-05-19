#include <algorithm>
#include <fstream>
#include <iostream>

#include <string>
#include <sstream>
#include <iterator>

#include "QApairsSet.h"
#include "Vocabulary.h"

using namespace std;

const std::string QAPairsSet::delimetrs = " ,.!?\"()«»"; // delimiters

void QAPairsSet::addPair(const std::string & question, const std::string & answer)
{
  pairsArr.push_back(QAPair(question, answer));
}

void QAPairsSet::getIndexByVocab(Vocabulary & vocabulary)
{
  //vector<int> questionInds;

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

void QAPairsSet::ReadFromTempFile(const std::string & dataFileName)
{
  ifstream QAPairsOStream(dataFileName);

  if (!QAPairsOStream.is_open())
  {
    cout << "Cant open " + dataFileName;
  }

  string question;
  string answer;
  string euSizeStr;
  string indecesStr;
  

  while (getline(QAPairsOStream, question))
  {
    getline(QAPairsOStream, answer);
    pairsArr.emplace_back(question, answer);
     
    
    getline(QAPairsOStream, euSizeStr);
    istringstream ss(euSizeStr);
    ss >> pairsArr.back().invEuqlidSize;

    getline(QAPairsOStream, indecesStr);
    stringstream indeces(indecesStr);
    copy(istream_iterator<int>(indeces),
      istream_iterator<int>(), back_inserter(pairsArr.back().wordIndeces));

    //cout << pairsArr.back().question << endl << pairsArr.back().answer << endl << pairsArr.back().invEuqlidSize << endl;

    //pairsArr.push_back(qap);
  }
  QAPairsOStream.close();
  cout << "Loaded set of pairsQA with size: " + to_string(pairsArr.size()) << endl;
}

size_t QAPairsSet::size() const
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

double QAPairsSet::QAPair::getDistFromQuery(Vocabulary &vocabulary, std::vector<int>& queryWordIndeces) const
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
  return val;// *invEuqlidSize;
}
