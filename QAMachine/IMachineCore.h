/*! \file
 *  \brief This file contains interface for
 *  the QAMachineCore class, that is base
 *  class for the application.
 *
 *  \authors Oleg Taratukhin
 *
 *  \date 04.04.2018
 */

#ifndef __QUESTION_ANSWER_MACHINE_INTERFACE__
#define __QUESTION_ANSWER_MACHINE_INTERFACE__
#pragma once

#include <string>

/*! \addtogroup Core Application core
    @{
 */

/*! \brief MachineCore interface
 *
 *  Interface defines interaction with application
 *  from outer scope.
 */
class IQAMachineCore
{
public:
  /*! \brief Abstract method to ask question
   */
	virtual void askQuestion(std::string question) = 0;
	
  /*! \brief Abstract method to get answer
   */
	virtual std::string getAnswer(void) = 0;

  /*! \brief Abstract method to display answer
   */
  virtual void printAnswer(void) = 0;

  /*! \brief Abstract method to learn file 
   */
	virtual void learnFromFile(const std::string & fileName, const std::string &rejectedWordsFileName) = 0;

  /*! \brief Abstract destructor
   */
  virtual ~IQAMachineCore() {};
};

/*!  @} 
 */

#endif // !__QUESTION_ANSWER_MACHINE_INTERFACE__