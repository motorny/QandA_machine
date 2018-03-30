#pragma once

#include "QApairsQAset.h"


#include <string>
#include <vector>


using namespace std;

class QAVocabulary
{
public:
  

  void GenerateVocabularyFromQAset(const string &dataFileName, const string &rejectedWordsFileName, QApairsQAset & pairsQAset);
  int GetWordInd(const string &word);
  size_t size();


  class WordPair {
  public:
    WordPair(const std::string &s, double d)
    {
      str = s;
      idf = d;
    }
    std::string str;
    double idf;
  };

  QAVocabulary::WordPair& operator[](size_t ind);
private:
  std::vector<WordPair> vocabulary;
 
  static const string delimetrs;
};

