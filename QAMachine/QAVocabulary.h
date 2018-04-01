#ifndef __QA_VOCABULARY_H__
#define __QA_VOCABULARY_H__
#pragma once

#include <string>
#include <vector>

#include "QApairsQAset.h"

class QAVocabulary
{
public:

  void GenerateVocabularyFromQAset(const std::string &dataFileName, 
    const std::string &rejectedWordsFileName, QApairsQAset & pairsQAset);
  
  int GetWordInd(const std::string &word);
  
  size_t size();

  /*! \class WordPair
   *
   *  Class WordPair holds a word that is present in database and holds it's
   *  IDF (inverse document frequency)
   */
  class WordPair {
  public:
    /*! \brief WordPair class constructor
     *
     *  \param word - word
     *  \param idf - inverse document frequency
     */
    explicit WordPair(const std::string &word, double idf = 0.0)
      : word(word), idf(idf) { }

    /*! \brief Setter for idf value
     *
     *  Allows to set custom idf to wordPair instance
     *  Side-effect: idf changed
     *  \param idf - new idf to set
     */
    void setIdf(double idf_)
    {
      idf = idf_;
    }

    std::string word; //!< word
    double idf; //!< IDF (inverse document frequency)
  };

  WordPair& operator[](size_t ind);
  
  std::vector<WordPair>::iterator begin(void);

  std::vector<WordPair>::iterator end(void);

private:

  std::vector<WordPair> vocabulary;
 
  static const std::string delimetrs;
};

#endif // !__QA_VOCABULARY_H__