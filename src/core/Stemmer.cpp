#include "Stemmer.h"
#include <iostream>
const std::string Stemmer::VOVELS = "аеиоуыэюя";
const std::string Stemmer::EMPTY = "";
const std::string Stemmer::S1 = "$1";
const std::string Stemmer::S13 = "$1$3";
const std::string Stemmer::SN = "н";

const std::regex Stemmer::PERFECTIVE = std::regex("(ив|ивши|ившись|ыв|ывши|ывшись|вши|вшись)$");
const std::regex Stemmer::REFLEXIVE = std::regex("(ся|сь)$");
const std::regex Stemmer::ADJECTIVE = std::regex("(ее|ие|ые|ое|ими|ыми|ей|ий|ый|ой|ем|им|ым|ом|его|ого|ему|ому|их|ых|ую|юю|ая|яя|ою|ею)$");
const std::regex Stemmer::PARTICIPLE = std::regex("(.*)(ивш|ывш|ующ)$|([ая])(ем|нн|вш|ющ|щ)$");
const std::regex Stemmer::VERB = std::regex("(.*)(ила|ыла|ена|ейте|уйте|ите|или|ыли|ей|уй|ил|ыл|им|ым|ен|ило|ыло|ено|ят|ует|уют|ит|ыт|ены|ить|ыть|ишь|ую|ю)$|([ая])(ла|на|ете|йте|ли|й|л|ем|н|ло|но|ет|ют|ны|ть|ешь|нно)$");
const std::regex Stemmer::NOUN = std::regex("(а|ев|ов|ие|ье|е|иями|ями|ами|еи|ии|и|ией|ей|ой|ий|й|иям|ям|ием|ем|ам|ом|о|у|ах|иях|ях|ы|ь|ию|ью|ю|ия|ья|я)$");
const std::regex Stemmer::I = std::regex("и$");
const std::regex Stemmer::P = std::regex("ь$");
const std::regex Stemmer::NN = std::regex("(нн|н)$");
const std::regex Stemmer::DERIVATIONAL = std::regex(".*[^аеиоуыэюя]+[аеиоуыэюя].*ость?$");
const std::regex Stemmer::DER = std::regex("ость?$");
const std::regex Stemmer::SUPERLATIVE = std::regex("(ейше|ейш)$");
std::string Stemmer::stem(std::string word)
{
  transform(word.begin(), word.end(), word.begin(), ::tolower);
  replace(word.begin(), word.end(), 'ё', 'е');
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
    word = std::regex_replace(word, NN, EMPTY);
  }
  std::cout << word << std::endl;
  return word;
}