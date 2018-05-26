#include "Stemmer.h"
#include <iostream>
#include <fstream>

std::vector<std::string> Stemmer::regArr;
std::string Stemmer::VOVELS;
std::string Stemmer::EMPTY;
std::string Stemmer::S1;
std::string Stemmer::S13;
std::string Stemmer::SN;

std::regex Stemmer::PERFECTIVE;
std::regex Stemmer::REFLEXIVE;
std::regex Stemmer::ADJECTIVE;
std::regex Stemmer::PARTICIPLE;
std::regex Stemmer::VERB;
std::regex Stemmer::NOUN;
std::regex Stemmer::I;
std::regex Stemmer::P;
std::regex Stemmer::NN;
std::regex Stemmer::DERIVATIONAL;
std::regex Stemmer::DER;
std::regex Stemmer::SUPERLATIVE;

bool Stemmer::init()
{

  std::ifstream regStringsIS("../dataset/stemmerStrings.txt");
  if (!regStringsIS.is_open())
     regStringsIS = std::ifstream("../../dataset/stemmerStrings.txt");
  if (!regStringsIS.is_open())
    regStringsIS = std::ifstream("../../../dataset/stemmerStrings.txt");
  std::string str;
  while (std::getline(regStringsIS, str))
  {
    regArr.push_back(str);
  }
  regStringsIS.close();

 VOVELS = regArr[0];
 EMPTY = "";
 S1 = regArr[1];
 S13 = regArr[2];
 SN = regArr[3];


 PERFECTIVE = std::regex(regArr[4]);
 REFLEXIVE = std::regex(regArr[5]);
 ADJECTIVE = std::regex(regArr[6]);
 PARTICIPLE = std::regex(regArr[7]);
 VERB = std::regex(regArr[8]);
 NOUN = std::regex(regArr[9]);
 I = std::regex(regArr[10]);
 P = std::regex(regArr[11]);
 NN = std::regex(regArr[12]);
 DERIVATIONAL = std::regex(regArr[13]);
 DER = std::regex(regArr[14]);
 SUPERLATIVE = std::regex(regArr[15]);
 return true;
}




const bool Stemmer::initInvoker = Stemmer::init();

 std::string Stemmer::stem(std::string word)
{
  // make word lowercase
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  replace(word.begin(), word.end(), '¸', 'å');
  std::string temp = std::regex_replace(word, PERFECTIVE, EMPTY);
  if (word.size() != temp.size())
  {
    word = temp;
  }
  else
  {
    word = std::regex_replace(word, REFLEXIVE, EMPTY);
    temp = std::regex_replace(word, ADJECTIVE, EMPTY);
    if (word.size() != temp.size())
    {
      word = temp;
      word = std::regex_replace(word, PARTICIPLE, S13);
      //word = std::regex_replace(word, PARTICIPLE, EMPTY);
    }
    else
    {
      temp = std::regex_replace(word, VERB, S13);
      if (word.size() != temp.size())
      {
        word = temp;
      }
      else
      {
        word = std::regex_replace(temp, NOUN, EMPTY);
      }
    }
  }
  word = std::regex_replace(word, I, EMPTY);
  if (std::regex_match(word, DERIVATIONAL))
  {
    word = std::regex_replace(word, DER, EMPTY);
  }
  temp = std::regex_replace(word, P, EMPTY);
  if (temp.length() != word.length())
  {
    word = temp;
  }
  else
  {
    word = std::regex_replace(word, SUPERLATIVE, EMPTY);
    word = std::regex_replace(word, NN, SN);
  }
  return word;
}