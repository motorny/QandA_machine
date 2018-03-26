#ifndef __QUESTION_ANSWER_MACHINE_CORE__
#define __QUESTION_ANSWER_MACHINE_CORE__

#include <string>

#include "IQAMachineCore.h"
#include "QADataBase.h"

class QAMachineCore: public IQAMachineCore
{
public:

	QAMachineCore(void);

	void askQuestion(std::string question) override;

	std::string getAnswer() override;

	void setDb(QADatabase userDb) override;

    ~QAMachineCore();
};

#endif // !__QUESTION_ANSWER_MACHINE_CORE__
