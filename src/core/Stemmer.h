#ifndef __STEMMER_H__
#define __STEMMER_H__
#pragma once

#include <string>
#include <regex>

class Stemmer {
public:
  std::string stem(std::string word);
private:
  static const std::string VOVELS;
  static const std::string EMPTY;
  static const std::string S1;
  static const std::string S13;
  static const std::string SN;

  static const std::regex PERFECTIVE;
  static const std::regex REFLEXIVE;
  static const std::regex ADJECTIVE;
  static const std::regex PARTICIPLE;
  static const std::regex VERB;
  static const std::regex NOUN;
  static const std::regex I;
  static const std::regex P;
  static const std::regex NN;
  static const std::regex DERIVATIONAL;
  static const std::regex DER;
  static const std::regex SUPERLATIVE;

};

#endif // !__STEMMER_H__