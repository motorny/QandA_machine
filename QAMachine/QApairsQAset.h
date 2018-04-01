#pragma once

#include <vector>
#include <string>

class QAVocabulary;

class QApairsQAset
{
public:
  
  void AddPair(const std::string &question, const std::string &answer);
  

  /*! \brief Assign vector of word's indexes to all questions and calculate idf
   * 
   * Fill wordIndeces wordIndeces vector in each QAPair using ParseStrByVocabInds 
   * function. 
   * Calculate idf (inverse document frequency) for each word in vocabulary
   * \param vocabulary Vocabulary to get words' indeces from
   */
  void IndexByVocab(QAVocabulary &vocabulary);
  
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

    double GetDistFromQuery(QAVocabulary &vocabulary, std::vector<int> &queryWordIndeces);
  };

  QApairsQAset::QAPair& operator[](size_t ind);
  std::vector<QAPair>::iterator begin(void);
  std::vector<QAPair>::iterator end(void);

private:

  static const std::string delimetrs;

  std::vector<QAPair> pairsArr;
};

