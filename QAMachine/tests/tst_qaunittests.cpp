#include <QString>
#include <QtTest>

class QAUnitTests : public QObject
{
    Q_OBJECT

public:
    QAUnitTests();

private Q_SLOTS:
    void VocabularyTest();
};

QAUnitTests::QAUnitTests()
{
}

void QAUnitTests::VocabularyTest()
{
    QVERIFY2(true, "Failure");
}

int main(int argc, char *argv[]) \
{ 
QAUnitTests tc; 
QTest::setMainSourcePath(__FILE__, ".");
return QTest::qExec(&tc, argc, argv); 
}
#include "tst_qaunittests.moc"
