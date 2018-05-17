#ifndef __STEMMER_H__
#define __STEMMER_H__
#pragma once

#include <string>
#include <regex>
/*! \brief Class to find stems of the words
* 
*/
class Stemmer {
public:
/*! \brief Stemmer for words
*
* Function that gets a stem of the word
* \param word Word to get stem of
* \return Stem of the word
*/
  static std::string stem(std::string word);
private:
  static const std::string VOVELS;//!< String of vovels
  static const std::string EMPTY;//!< Empty space to replace parts of words
  static const std::string S1;//!< Special replacement string
  static const std::string S13;//!< Special replacement string
  static const std::string SN;//!< String to replace "нн" with one "н"

  static const std::regex PERFECTIVE;//!< Group that defines perfective gerund
  static const std::regex REFLEXIVE;//!< Group that defines reflexives
  static const std::regex ADJECTIVE;//!< Group that defines adjectives
  static const std::regex PARTICIPLE;//!< Group that defines participles
  static const std::regex VERB;//!< Group that defines verbs
  static const std::regex NOUN;//!< Group that defines nouns
  static const std::regex I;//!< Group that defines noun ending "и"
  static const std::regex P;//!< Group that defines "ь" in case it was not removed
  static const std::regex NN;//!< Group that defines "нн"
  static const std::regex DERIVATIONAL;//!< Group that defines derivationals
  static const std::regex DER;//!< Group to replace derivationals
  static const std::regex SUPERLATIVE;//!< Group to define superalatives

};

#endif // !__STEMMER_H__