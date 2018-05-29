/*! \file 
 *  \brief QAMachineCore declarations
 *
 *  This file contains declarations of methods
 *  associated with QAMachineCore class and form
 *  it's base functionality.
 *
 *  \authors Oleg Taratukhin
 *           Nikita Motorny
 *           Evgeny Korsukov
 *
 *  \date 04.04.2018
 */

#ifndef __QUESTION_ANSWER_MACHINE_CORE__
#define __QUESTION_ANSWER_MACHINE_CORE__

#include <string>
#include <vector>
#include <list>

#include "IMachineCore.h"
#include "Vocabulary.h"
#include "QApairsSet.h"

#define USE_STEMMER

/*! \defgroup Core Application core
 *  \brief This module defines base functionality
 */
///@{

/*! \brief Core application class
 *  
 *  Core application creates basic functionality
 *  for the application. The design of the class
 *  uses defined in IQAMachineCore interface, aggregation
 *  pattern is used to attach Vocabulary class instance
 *  and QAPaisSet instance.
 */
class QAMachineCore : public IQAMachineCore
{
public:

  /*! \brief Core class constructor
  *
  *  Core class aggregates all the nessesary classes needed for the
  *  application main logic.
  *  \version 1.0
  */
  QAMachineCore(void);

  /*! \brief Function to ask question by user
  *
  *  Generate best options based on the given dataset
  *  for the user defined question based on how close it is to
  *  the question already present in the dataset.
  *  \warning function is used to input user question, to
  *           get answer refer to getQuestion.
  *  \param question - user defined question
  */
  void askQuestion(std::string question) override;

  /*! Function to get answer to user question
  *
  *  Function returnes single processed option as answer
  *  to user defined question, based on current dataset
  *  \warning for meaningful result should be
  *           called after askQuestion
  *  \returns string as answer to the question
  */
  std::string getAnswer() override;

  /*! \brief Printing answer and some aditional info about options
  *
  *  Function prints best suitable answer to the standart output
  *  using std::cout, or writes a message that no answers are
  *  considered relevant. If compiled in debug configuration there
  *  is some additional information on idf of words in common between
  *  actual questions asked by user and current option in bestMatchInd
  *  list of best options.
  */
  void printAnswer(void);

  /*! \brief Learning function from TSV file
  *
  *  Function loads file (semi-colon separated) in strict
  *  grammar: \<question\>; \<answer\> \\r\\n
  *  All questions are processed to exclude words listed
  *  in rejected words file
  *  \warning for meaningful results file should be at least 10k
  *  question-answer pairs long in general.
  *  \param fileName - name of the file
  *  \param rejectedWordsFileName - name of the file with rejected words
  */
  void learnFromFile(const std::string & fileName,
    const std::string &rejectedWordsFileName) override;

  /*! \brief Saving processed base to files
  *
  *  Saves Vocabulary and QAPairsSet to temporary files.
  */
  void saveBaseToFile();

  /*! \brief Load processed base from files
  *
  *  Loads Vocabulary and QAPairsSet from temporary files.
  */
  void loadBaseFromFile();

  /*! \brief Core class destructor
  *
  */
  ~QAMachineCore();

private:
  Vocabulary vocabulary; //!< Vocabulary of words
  QAPairsSet pairsQAset; //!< Cached database of question-answer and metainformation
  
  std::string currentQuestion; //!< Current question asked
                               /*!< Is used in analysis that might be needed after
                                *   processing in askQuestion is complete */

  std::vector<int> queryInds; //!< Indeces of question string returned with parseStrByVocabInds funtion

  static const std::string delimetrs;//!< String of delimetrs
                                     /*!< Contains all delimetrs, which are used to
                                     *   split questions to words.*/

  std::list<std::pair<int, double>> bestMatchInd; //!< Array of best options
                                                  /*!< Holds indexes to words in set
                                                   *   pairsQAset, as well as the score  
                                                   *   corresponding to the closeness to 
                                                   *   currently asked question */

  static const size_t maxOptions = 5; //!< Number of top options considered for answer

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
  std::list<std::pair<int, double>> findBest(std::vector<int> &queryInd);
};

///@}

#endif // !__QUESTION_ANSWER_MACHINE_CORE__