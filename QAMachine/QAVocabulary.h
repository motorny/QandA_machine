#ifndef __QA_VOCABULARY_H__
#define __QA_VOCABULARY_H__
#pragma once

#include <string>
#include <vector>

#include "QApairsQAset.h"

class QAVocabulary
{
public:

  void GenerateVocabularyFromQAset(const std::string &dataFileName, const std::string &rejectedWordsFileName, QApairsQAset & pairsQAset);
  
  int GetWordInd(const std::string &word);
  
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
 
  static const std::string delimetrs;
};

#endif // !__QA_VOCABULARY_H__