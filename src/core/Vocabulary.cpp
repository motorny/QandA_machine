#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Vocabulary.h"

using namespace std;

const std::string Vocabulary::delimetrs = " ,.!?\"()«»"; // delimiters

void Vocabulary::generateVocabularyFromQAFile(const string & dataFileName, const string & rejectedWordsFileName, QAPairsSet & pairsQAset)
{
  ifstream qAPairsIFS(dataFileName);

  if (!qAPairsIFS.is_open())
  {
    cout << "Could not open QuestionsAnswers pairs file: " << dataFileName << endl;
    string dataFileNameTry = "../" + dataFileName;
    qAPairsIFS = ifstream(dataFileNameTry);
    if (!qAPairsIFS.is_open())
    {
      cout << "Could not open QuestionsAnswers pairs file: " << dataFileNameTry << endl;
      return;
    }
    cout << "Opened QuestionsAnswers pairs file: " << dataFileNameTry << endl;
  }

  map<string, int> tempMap; // map used to push words in O(log(n))
  string question;
  string answer;
  string pairStr;
  string word;

  // iterate through lines of dataFile
  cout << "Parsing lines of datafile:" << endl;
  int lineCnt = 1;
  while (std::getline(qAPairsIFS, pairStr))
  {
    cout << '\r';
    cout << lineCnt++;
    //get question and answer strings
    question = pairStr.substr(0, pairStr.find(';'));
    answer = pairStr.substr(pairStr.find(';') + 1);

    // lefttrim answer string
    size_t fNotSp = answer.find_first_not_of(" \t");
    if (fNotSp != -1)
      answer = answer.substr(fNotSp);

    pairsQAset.addPair(question, answer);

    // iterate through words of question
    size_t start = question.find_first_not_of(delimetrs), end = 0;
    while ((end = question.find_first_of(delimetrs, start)) != string::npos)
    {
      word = question.substr(start, end - start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
#ifdef USE_STEMMER
      word = Stemmer::stem(word);
#endif // USE_STEMMER
      tempMap[word]++;
      //find next word's start
      start = question.find_first_not_of(delimetrs, end);
    }
    //proceed last word
    if (start != string::npos)
    {
      word = question.substr(start);
      transform(word.begin(), word.end(), word.begin(), ::tolower);
#ifdef USE_STEMMER
      word = Stemmer::stem(word);
#endif // USE_STEMMER
      tempMap[word]++;
    }
  }
  cout << endl;
  qAPairsIFS.close();
  // File parsing ended

  // delete rejected words from map
  string rWord;
  ifstream rejectedWordsIFS(rejectedWordsFileName);
  if (!rejectedWordsIFS.is_open())
  {
    cout << "Could not open Rejected words file: " << rejectedWordsFileName << endl;
    string rejectedWordsFileNameTry = "../" + rejectedWordsFileName;
    rejectedWordsIFS = ifstream(rejectedWordsFileNameTry);
    if (!rejectedWordsIFS.is_open())
    {
      cout << "Could not open Rejected words file: " << rejectedWordsFileNameTry << endl;
      return;
    }
    cout << "Opened Rejected words file: " << rejectedWordsFileNameTry << endl;
  }

  while (rejectedWordsIFS >> rWord)
  {
    tempMap.erase(rWord);
  }
  rejectedWordsIFS.close();

  // resave as vector 
  cout << "Resaving map as vector:" << endl;
  int wordCnt = 1;
  vocabulary.reserve(tempMap.size());
  for (auto &w : tempMap)
  {
    cout << '\r';
    cout << wordCnt++;
    vocabulary.emplace_back(WordPair(w.first, (double)w.second));
  }
  cout << endl;
}

void Vocabulary::ReadFromTempFile(const string & dataFileName)
{
  ifstream vocabOStream(dataFileName);

  if (!vocabOStream.is_open())
  {
    cout << "Cant open " + dataFileName;
  }
  string str;
  while (getline(vocabOStream, str))
  {
    string word;
    double idf;
    istringstream ss(str);
    ss >> word;
    ss >> idf;
    //cout << word << "--------" << idf << endl;
    vocabulary.emplace_back(WordPair(word, idf));
  }

  /*while (!vocabOStream.eof())
  {

    vocabOStream >> word;
    vocabOStream >> idf;
    cout << word << "--------" << idf << endl;
    vocabulary.emplace_back(WordPair(word, idf));
  }*/
  vocabOStream.close();
  cout << "Loaded Vocabulary with size: " + to_string(vocabulary.size()) << endl;
}

int Vocabulary::getWordInd(const string & word) const
{
  int left = 0, right = vocabulary.size() - 1;

  while (right >= left)
  {
    int middle = left + (right - left) / 2;

    if (vocabulary[middle].word == word)
      return middle;

    if (vocabulary[middle].word > word)
      right = middle - 1;
    else
      left = middle + 1;
  }

  return -1;
}

size_t Vocabulary::size() const
{
  return vocabulary.size();
}

Vocabulary::WordPair & Vocabulary::operator[](size_t ind)
{
  return vocabulary[ind];
}

std::vector<int> Vocabulary::parseStrByVocabInds(std::string & str) const
{
  string word;
  vector<int> res;
  int wordInd;
  bool indRepeat;
  size_t start = str.find_first_not_of(delimetrs), end = 0;

  // iterate by words untill end of string
  while ((end = str.find_first_of(delimetrs, start)) != string::npos)
  {
    word = str.substr(start, end - start);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
#ifdef USE_STEMMER
    word = Stemmer::stem(word);
#endif // USE_STEMMER
    if ((wordInd = this->getWordInd(word)) != -1)
    {
      // check for wordInd uniquenss
      indRepeat = false;
      for (int wInd : res)
        if (wInd == wordInd)
          indRepeat = true;

      if (!indRepeat)
        res.push_back(wordInd);
    }

    // recalculate new word start
    start = str.find_first_not_of(delimetrs, end);
  }

  //proceed last word
  if (start != std::string::npos)
  {
    word = str.substr(start);
    // make word lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);
#ifdef USE_STEMMER
    word = Stemmer::stem(word);
#endif // USE_STEMMER
    if ((wordInd = this->getWordInd(word)) != -1)
    {
      // check for wordInd uniquenss
      indRepeat = false;
      for (int wInd : res)
        if (wInd == wordInd)
          indRepeat = true;

      if (!indRepeat)
        res.push_back(wordInd);
    }
  }

  return res;
}

vector<Vocabulary::WordPair>::iterator Vocabulary::begin(void)
{
  return vocabulary.begin();
}

vector<Vocabulary::WordPair>::iterator Vocabulary::end(void)
{
  return vocabulary.end();
}


