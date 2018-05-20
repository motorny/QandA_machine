#pragma once
/*! \file
*  \brief QtTests
*
*  This file contains tests of the project
*/
#include <QString>
#include <QtTest>

#include "QAMachineCore.h"
/*! 
* This macro makes the type Type known to QMetaType as long 
* as it provides a public default constructor, a public copy 
* constructor and a public destructor. It is needed to use 
* the type Type as a custom type in QVariant.
*/
Q_DECLARE_METATYPE(std::string);

/*! \brief Class to store all data for QtTests and run them
*
*/
class QAUnitTests : public QObject
{
  Q_OBJECT

public:
  QAUnitTests();

  std::string relPath = "";
  private Q_SLOTS:
  /*! \brief Data for VocabularyTest()
  */
  void VocabularyTest_data();
  /*! \brief Vocabulary addition test
  * 
  * Test that uses small data base to check whether
  * vocabulary generated correctly
  */
  void VocabularyTest();
  /*! \brief Data for VocabularyRejectionTest_data()
  */
  void VocabularyRejectionTest_data();
  /*! \brief Vocabulary rejection test
  * 
  * Test that checks if word rejection unit works correctly. Rejected 
  * words list is given. Test checks wheter listed words were omitted 
  * or not when vocabulary was made up.
  */
  void VocabularyRejectionTest();
  /*! \brief Data for SimilarQuestionTest()
  */
  void SimilarQuestionTest_data();
  /*! \brief Exact question test
  * 
  * Test that asks exactly the same questions as in data base
  */
  void SimilarQuestionTest();
  /*! \brief Data for IdfTest()
  */
  void IdfTest_data();
  /*! \brief Idf mark test
  *
  * Test set up on small data base that compares hand-counted
  * Idf mark and in-programme one
  */
  void IdfTest();
  /*! \brief Data for StrToIndexTest()
  */
  void StrToIndexTest_data();
  /*! \brief Parser string to index test
  */
  void StrToIndexTest();
  /*! \brief Data for StemmerTest()
  */
  void StemmerTest_data();
  /*! \brief Stemmer test
  *
  * Test that compares semmerized words with real expected stems
  */
  void StemmerTest();
};

#include "tst_qaunittests.moc"