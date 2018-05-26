#ifndef __STEMMER_H__
#define __STEMMER_H__
#pragma once

#include <string>
#include <regex>
#include <vector>
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
  /*! /brief Emulation of static constructor  
  */
  static bool init();
  /*! /brief Static constructor service variable
  */
  static const bool initInvoker;

  /*! /brief Container for strings in cp1251
  */
  static std::vector<std::string> regArr;

  static  std::string VOVELS;//!< String of vovels
  static  std::string EMPTY;//!< Empty space to replace parts of words
  static  std::string S1;//!< Special replacement string
  static  std::string S13;//!< Special replacement string
  static  std::string SN;//!< String to replace "HH" with one "H"

  static  std::regex PERFECTIVE;//!< Group that defines perfective gerund
  static  std::regex REFLEXIVE;//!< Group that defines reflexives
  static  std::regex ADJECTIVE;//!< Group that defines adjectives
  static  std::regex PARTICIPLE;//!< Group that defines participles
  static  std::regex VERB;//!< Group that defines verbs
  static  std::regex NOUN;//!< Group that defines nouns
  static  std::regex I;//!< Group that defines noun ending "N"
  static  std::regex P;//!< Group that defines "b" in case it was not removed
  static  std::regex NN;//!< Group that defines "HH"
  static  std::regex DERIVATIONAL;//!< Group that defines derivationals
  static  std::regex DER;//!< Group to replace derivationals
  static  std::regex SUPERLATIVE;//!< Group to define superalatives

};

#endif // !__STEMMER_H__