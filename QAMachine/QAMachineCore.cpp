/*! \file 
 *  \brief QAMachineCore definitions
 *
 *  This file contains definitions of methods
 *  listed in QAMachineCore class and form base 
 *  functionality of the application.
 *
 *  \authors Oleg Taratukhin
 *           Nikita Motorny
 *
 *  \date 04.04.2018
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "QAMachineCore.h"

using namespace std;



const std::string QAMachineCore::delimetrs = " ,.!?"; //! delimiters
const double threshold = 1e-5; //! threshold used in evaluation relevance 

/*! \brief Core class constructor
 *
 *  Core class aggregates all the nessesary classes needed for the 
 *  application main logic.
 *  \version 1.0
 */
QAMachineCore::QAMachineCore()
{
}

/*! \brief findBest function chooses 5 best options depending on score
 *
 *  Function creates a list of pairs with interger - index in pairsQAset and
 *  double - value, corresponding to closeness of questions. New value
 *  is inserted while maintaining invariant (list is sorted by value).
 *  if no close options were found (irrelevance means that closeness is
 *  less than threshold that is a filed of core class and can be modified
 *  to represent more or less strict cut-plane of closeness). If no 
 *  relevant options were found than function a list of (0, -1). 
 *  \param queryInd - indexes of words in asked question
 *  \returns list of pairs of indexes of questions in pairsQAset with related score
 */
list<pair<int, double>> QAMachineCore::findBest(vector<int> &queryInd)
{
  list<pair<int, double>> bestInd{ pair<int, double>(0, pairsQAset[0].getDistFromQuery(vocabulary, queryInd)) };
  double value = 0.0;

  //! Iterate through the whole pairsQAset to find best options
  for (size_t pairInd = 1; pairInd < pairsQAset.size(); ++pairInd)
  {
    //! cache value of current option
    value = pairsQAset[pairInd].getDistFromQuery(vocabulary, queryInd);
    pair<int, double> curPair(pairInd, value);

    //! insert into list maintaining sort order (sorted by value)
    bestInd.insert(lower_bound(bestInd.begin(), bestInd.end(), curPair, 
      [](const pair<int, double> &left, const pair<int, double> &right)
      {
        return left.second > right.second;
      }),
      curPair);

    //! keep only fixed amount of best options
    bestInd.resize(std::min(static_cast<size_t>(maxOptions), bestInd.size()));
  }

  //! If very best one is so low, than any option is not good enough
  if (bestInd.front().second < threshold)
  {
    list<pair<int, double>> badOptions(maxOptions, pair<int, double>(0, -1));
    return badOptions;
  }

  return bestInd;
}

/*! \brief Function to ask question by user
 *
 *  Generate best options based on the given dataset
 *  for the user defined question based on how close it is to
 *  the question already present in the dataset.
 *  \warning function is used to input user question, to 
 *           get answer refer to getQuestion.
 *  \param question - user defined question
 */
void QAMachineCore::askQuestion(std::string question)
{
  vector<int> queryInds;

  //! Remember current question for furtherer use
  currentQuestion = question;

  //! Get indexes of words in question
  queryInds = vocabulary.parseStrByVocabInds(question);

  //! Find out what best answers are
  bestMatchInd = findBest(queryInds);
}

/*! Function to get answer to user question
 *
 *  Function returnes single processed option as answer
 *  to user defined question, based on current dataset
 *  \warning for meaningful result should be
 *           called after askQuestion
 *  \returns string as answer to the question
 */
std::string QAMachineCore::getAnswer()
{
  if (bestMatchInd.front().second == -1)
    return "Can't find answer";

  return pairsQAset[bestMatchInd.front().first].answer;
}

/*! \brief Contains operation for searching value in iterable
 *
 *  Function iterates through the iterable using std::found
 *  function from algorithm header file and returnes weather
 *  iterable contains value or not.
 *  \param start - iterator to start
 *  \param end - iterator to end
 *  \returns true if value is in iterable, false - otherwise
 */
template <class InputIterator, class T>
inline bool contains(InputIterator start, InputIterator end, const T& element)
{
  return find(start, end, element) != end;
}

/*! \brief Printing answer and some aditional info about options
 *
 *  Function prints best suitable answer to the standart output
 *  using std::cout, or writes a message that no answers are
 *  considered relevant. If compiled in debug configuration there
 *  is some additional information on idf of words in common between
 *  actual questions asked by user and current option in bestMatchInd
 *  list of best options.
 */
void QAMachineCore::printAnswer(void)
{
  //! Check if answer is valid
  if (bestMatchInd.front().second == -1) 
  {
    std::cout << "There is no simular question, so we can't get answer!" << endl;
    
    return;
  }

  //! Present best option as answer
  std::cout << "----------------------------------------------" << endl;
  std::cout << "Closest question: " << pairsQAset[bestMatchInd.front().first].question <<
     " -> " << pairsQAset[bestMatchInd.front().first].answer << "(" << bestMatchInd.front().second << ")" << endl;
  std::cout << std::endl;
  std::cout << ">> Other options: " << endl;

  //! list other options from bestMatch as well
  //! format: >>>> Question: <question> -> <answer> <score>
  for (auto const &option : bestMatchInd)
  {
    //! Do not show results if they are not much relevant
    if (option.second < threshold)
      break;

    std::cout << ">>>> Question: " << pairsQAset[option.first].question << " -> " <<
      pairsQAset[option.first].answer << " (" << option.second << ")" << endl;
  
#ifndef NDEBUG

    vector<int> indWordsQuestion = vocabulary.parseStrByVocabInds(currentQuestion);
    vector<int> indWordsOption = vocabulary.parseStrByVocabInds(pairsQAset[option.first].question);
    vector<int> indWordsCommon;

    for (int wordInd : indWordsOption)
      if (contains(indWordsQuestion.begin(), indWordsQuestion.end(), wordInd))
        indWordsCommon.push_back(wordInd);

    // Print additional debug information
    std::cout << "debug-info: <word>-<idf>"  << endl;
    for (int wordInd : indWordsCommon)
      cout << vocabulary[wordInd].word << " " << vocabulary[wordInd].idf << "| ";

    std::cout << std::endl;
    std::cout << std::endl;
#endif // NDEBUG
  }

  std::cout << "----------------------------------------------" << endl << endl;
}

/*! \brief Learning function from TSV file
 * 
 *  Function loads file (semi-colon separated) in strict 
 *  grammar: <question>; <answer> \r\n
 *  All questions are processed to exclude words listed
 *  in rejected words file
 *  \warning for meaningful results file should be at least 10k 
 *  question-answer pairs long in general.
 *  \param filename - name of the file
 *  \param rejectedWordsFilename - name of the file with rejected words
 */
void QAMachineCore::learnFromFile(const string & fileName, const std::string &rejectedWordsFileName)
{
  vocabulary.generateVocabularyFromQAFile(fileName, rejectedWordsFileName, pairsQAset);
  pairsQAset.getIndexByVocab(vocabulary);
  std::cout << "Vocabulary size: " << vocabulary.size() << endl;
}

/*! \brief Core class destructor
 *
 */
QAMachineCore::~QAMachineCore()
{
}