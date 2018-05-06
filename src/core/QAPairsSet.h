#pragma once

#include <vector>
#include <string>
#include "Stemmer.h"
class Vocabulary;



/*! \brief Class to store pairs of Questions/Answers and service information
 *
 * Each pair is added with array of contained words' indeces< gathered from vocabulary.
 * Also, count of words is saved as 1/sqrt(cnt) in order to quickly normalize vector
 */
class QAPairsSet
{
public:
  



  /*! \brief Add new pair to container
  * 
  * Creates a new QAPair instance in container. Indeces array and normalization 
  * multiplier are not filled
  * \param question String with question
  * \param answer String with answer
  */
  void addPair(const std::string &question, const std::string &answer);

  /*! \brief Assign vector of word's indexes to all questions and calculate idf
   * 
   * Fill wordIndeces wordIndeces vector in each QAPair using parseStrByVocabInds 
   * function. 
   * Calculate idf (inverse document frequency) for each word in vocabulary
   * \param vocabulary Vocabulary to get words' indeces from
   */
  void getIndexByVocab(Vocabulary &vocabulary);
  
  /*! \brief Get current count of pairs
  * 
  *  \return Count of question/answer pairs in vocabulary
  */
  size_t size();

  /*! \class QAPair Container for question/answer pair and additional info
  *
  *  Class contains two strings with answer and question,
  *  array of indeces of words, contained in question. Indeces corresponds to
  *  indeces from vocabulary. Multiplier for euqlid normalization is also saved-
  *  it is equal to 1 / sqrt(cnt of words)
  */
  class QAPair 
  {
  public:
    /*! \brief QAPair class constructor
    *
    *  \param q Question string
    *  \param a Answer string
    */
    QAPair(const std::string &q, const std::string &a)
    {
      question = q;
      answer = a;
    };

    std::string question;//!< Question string
    std::string answer;//!< Answer string
    std::vector<int> wordIndeces;//!< Array of words, contained in question.
                                 /*!<Indeces corresponds to
                                  *  indeces of words in vocabulary */
    double invEuqlidSize;//!< Multiplier for euqlid normalization

    /*! \brief Function to get distance in abstract metric between two sentences 
     *
     *  Calculate a value, that represent similarity of question and other sentence,
     *  represented by array of words indeces from vocabulary. 0 is the worst, bgger is better
     *  \param vocabulary Vocabulary to get word's indeces from
     *  \param queryWordIndeces Indeces of words in compaired sentence
     *  \return value of similarity
     */
    double getDistFromQuery(Vocabulary &vocabulary, std::vector<int> &queryWordIndeces);
  };

  /*! \brief Access containers element by index
  *
  * Access QAPair, specified by index
  * \param ind Index
  * \return QAPair with requested index
  */
  QAPairsSet::QAPair& operator[](size_t ind);

  /*! \brief Get an iterator to the beginning of container
  *
  * Used in range-based loops
  * \return Iterator to the beginning
  */
  std::vector<QAPair>::iterator begin(void);

  /*! \brief Get an iterator to the end of container
  *
  * Used in range-based loops
  * \return Iterator to the end
  */
  std::vector<QAPair>::iterator end(void);

private:

  std::vector<QAPair> pairsArr; //<! Main container for question/answer pairs
  
  static const std::string delimetrs;//!< String of delimetrs
                                     /*!< Contains all delimetrs, which are used to
                                     *   split questions to words.*/
};

