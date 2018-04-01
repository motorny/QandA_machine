#ifndef __QA_VOCABULARY_H__
#define __QA_VOCABULARY_H__
#pragma once

#include <string>
#include <vector>

#include "QApairsQAset.h"

class QAVocabulary
{
public:

  /*! \brief Fill vocabulary and QApairs from file
   *
   * Parse file dataFileName, take question and answer from each line and
   * save it to pairsQAset. Question is divided by words and they are saved
   * to vocabulary. Words from rejectedWordsFileName are not saved to vocabulary.
   * Side-effect: field idf will conatin count of times this word met in full dataset. 
   * \param dataFileName File with questions and answers
   * \param rejectedWordsFileName File with words to avoid in vocabulary
   * \pairsQAset Object to put in strings of questions and answers
   */
  void GenerateVocabularyFromQAFile(const std::string &dataFileName, 
    const std::string &rejectedWordsFileName, QApairsQAset & pairsQAset);
  
  
  int GetWordInd(const std::string &word) const;
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
  

  /*! \brief Parser for strings to get its' words indeces
   *
   * Function used to get a set of indeces of words, which 
   * are contained in string. Indeces are taken from current instance.
   * If there is no some specific word
   * in vocabulary, no index is appended. If some word appears more than 1 time,
   * it's index is appended only one time. So all indeces are unique.
   * All words are transformed to lowercase before finding.
   * \param str String to parse
   * \return Vector of contained words' indeces
   */
  std::vector<int> ParseStrByVocabInds(std::string & str) const;

  std::vector<WordPair>::iterator begin(void);

  std::vector<WordPair>::iterator end(void);

private:

  std::vector<WordPair> vocabulary;
 

  static const std::string delimetrs;
};

#endif // !__QA_VOCABULARY_H__