#include <QtTest>
#include <cmath>
#include "expressionParser.h"

// add necessary includes here

class ExpressionParserClass : public QObject
{
    Q_OBJECT

public:
    ExpressionParserClass();
    ~ExpressionParserClass();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
    void test_case5();
    void test_case6();

private:
    ExpressionParser * ex;

};

ExpressionParserClass::ExpressionParserClass()
{

}

ExpressionParserClass::~ExpressionParserClass()
{

}

void ExpressionParserClass::initTestCase()
{
    ex = new ExpressionParser();
}

void ExpressionParserClass::cleanupTestCase()
{
    delete ex;
}

void ExpressionParserClass::test_case1()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "x^2";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (pow(x[0], 2)));
    QCOMPARE(ex->calculate(x[1]), (pow(x[1], 2)));
    QCOMPARE(ex->calculate(x[2]), (pow(x[2], 2)));
    QCOMPARE(ex->calculate(x[3]), (pow(x[3], 2)));
    QCOMPARE(ex->calculate(x[4]), (pow(x[4], 2)));
}

void ExpressionParserClass::test_case2()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "x^3+4*x-5";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (pow(x[0],3)+4*x[0]-5) );
    QCOMPARE(ex->calculate(x[1]), (pow(x[1],3)+4*x[1]-5) );
    QCOMPARE(ex->calculate(x[2]), (pow(x[2],3)+4*x[2]-5) );
    QCOMPARE(ex->calculate(x[3]), (pow(x[3],3)+4*x[3]-5) );
    QCOMPARE(ex->calculate(x[4]), (pow(x[4],3)+4*x[4]-5) );
}

void ExpressionParserClass::test_case3()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "-x^3+4*x-5";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (-1*pow(x[0],3)+4*x[0]-5) );
    QCOMPARE(ex->calculate(x[1]), (-1*pow(x[1],3)+4*x[1]-5) );
    QCOMPARE(ex->calculate(x[2]), (-1*pow(x[2],3)+4*x[2]-5) );
    QCOMPARE(ex->calculate(x[3]), (-1*pow(x[3],3)+4*x[3]-5) );
    QCOMPARE(ex->calculate(x[4]), (-1*pow(x[4],3)+4*x[4]-5) );
}

void ExpressionParserClass::test_case4()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "x+5-2/13";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (x[0]+5-2.0/13) );
    QCOMPARE(ex->calculate(x[1]), (x[1]+5-2.0/13) );
    QCOMPARE(ex->calculate(x[2]), (x[2]+5-2.0/13) );
    QCOMPARE(ex->calculate(x[3]), (x[3]+5-2.0/13) );
    QCOMPARE(ex->calculate(x[4]), (x[4]+5-2.0/13) ) ;
}

void ExpressionParserClass::test_case5()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "4-x^5";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (4-pow(x[0],5)) );
    QCOMPARE(ex->calculate(x[1]), (4-pow(x[1],5)) );
    QCOMPARE(ex->calculate(x[2]), (4-pow(x[2],5)) );
    QCOMPARE(ex->calculate(x[3]), (4-pow(x[3],5)) );
    QCOMPARE(ex->calculate(x[4]), (4-pow(x[4],5)) );
}

void ExpressionParserClass::test_case6()
{
    double x[] = {5, 34, 6, 2, 9};
    std::string input = "x*x*x*x";
    ex->parse(input.data(), input.length());
    QCOMPARE(ex->calculate(x[0]), (x[0]*x[0]*x[0]*x[0]) );
    QCOMPARE(ex->calculate(x[1]), (x[1]*x[1]*x[1]*x[1]) );
    QCOMPARE(ex->calculate(x[2]), (x[2]*x[2]*x[2]*x[2]) );
    QCOMPARE(ex->calculate(x[3]), (x[3]*x[3]*x[3]*x[3]) );
    QCOMPARE(ex->calculate(x[4]), (x[4]*x[4]*x[4]*x[4]) );
}

QTEST_APPLESS_MAIN(ExpressionParserClass)

#include "tst_expressionparserclass.moc"
