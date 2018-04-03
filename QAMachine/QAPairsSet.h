#pragma once

#include <vector>
#include <string>

class Vocabulary;

class QAPairsSet
{
public:
  
  void addPair(const std::string &question, const std::string &answer);
  

  /*! \brief Assign vector of word's indexes to all questions and calculate idf
   * 
   * Fill wordIndeces wordIndeces vector in each QAPair using parseStrByVocabInds 
   * function. 
   * Calculate idf (inverse document frequency) for each word in vocabulary
   * \param vocabulary Vocabulary to get words' indeces from
   */
  void getIndexByVocab(Vocabulary &vocabulary);
  
  size_t size();

  class QAPair 
  {
  public:
    QAPair(const std::string &q, const std::string &a)
    {
      question = q;
      answer = a;
    };
    std::string question;
    std::string answer;
    std::vector<int> wordIndeces;
    double invEuqlidSize;

    double getDistFromQuery(Vocabulary &vocabulary, std::vector<int> &queryWordIndeces);
  };

  QAPairsSet::QAPair& operator[](size_t ind);
  std::vector<QAPair>::iterator begin(void);
  std::vector<QAPair>::iterator end(void);

private:

  static const std::string delimetrs;

  std::vector<QAPair> pairsArr;
};

