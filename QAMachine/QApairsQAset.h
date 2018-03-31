#pragma once

#include <vector>
#include <string>

class QAVocabulary;

class QApairsQAset
{
public:
  
  void AddPair(const std::string &question, const std::string &answer);
  
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

private:

  static const std::string delimetrs;

  std::vector<QAPair> pairsArr;
};

