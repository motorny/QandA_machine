#ifndef __VOCABULARY_H__
#define __VOCABULARY_H__
#pragma once


#include <string>
#include <vector>
#include "GlobalDefines.h"
#include "QApairsSet.h"
/*! \brief Class to store vocabulary and handle all work with it 
*
*/
class Vocabulary
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
   * \param pairsQAset Object to put in strings of questions and answers
   */
  void generateVocabularyFromQAFile(const std::string &dataFileName, 
    const std::string &rejectedWordsFileName, QAPairsSet & pairsQAset);
  
  
  /*! \brief Find word in vocabulary
   *
   * Get index of word in current vocabulary, returns -1 if vocabulary does not contain 
   * requested word
   * \param word Word to find in vocabulary
   * \return Index of word or -1
   */
  int getWordInd(const std::string &word) const;

  /*! \brief Get current size of vocabulary
  * Size of vocabulary is equal to count of different words in it.
  *  \return Size of vocabulary
  */
  size_t size() const;

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

    ///*! \brief Setter for idf value
    // *
    // *  Allows to set custom idf to wordPair instance
    // *  Side-effect: idf changed
    // *  \param idf - new idf to set
    // */
    //void setIdf(double idf_)
    //{
    //  idf = idf_;
    //}

    std::string word; //!< word
    double idf; //!< IDF (inverse document frequency)
  };

  

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
  std::vector<int> parseStrByVocabInds(std::string & str) const;


  /*!  \brief Load processed vocabulary
  *
  *  Load processed vocabulary, which was saved by core on previous app execution
  *  \param dataFileName Name of file containing vocabulary
  */
  void ReadFromTempFile(const std::string & dataFileName);


  /*! \brief Get an iterator to the beginning of vocabulary
   *
   * Used in range-based loops
   * \return Iterator to the beginning
   */
  std::vector<WordPair>::iterator begin(void);

  /*! \brief Get an iterator to the end of vocabulary
   *
   * Used in range-based loops
   * \return Iterator to the end
   */
  std::vector<WordPair>::iterator end(void);

  /*! \brief Access vocabulary element by index 
  *
  * Access WordPair, specified by word's index
  * \param ind Index
  * \return WordPair with requested index
  */
  WordPair& operator[](size_t ind);

private:

  std::vector<WordPair> vocabulary;//!< Container for WordPairs, main class'es data conatiner

  static const std::string delimetrs;//!< String of delimetrs
                                     /*!< Contains all delimetrs, which are used to
                                     *   split questions to words.*/
};

#endif // !__VOCABULARY_H__