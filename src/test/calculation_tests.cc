#include <gtest/gtest.h>
#include "../Model/Model.h"
#include "../Controller/Controller.h"
#include <string>

void my_test(std::string s, double result) {
    s21::Notation no;
    s21::Controller cont(no);
    char * ch = (char*)s.c_str();
    cont.expression_input(&ch);

    ASSERT_EQ(cont.expression_output(0),result);
}

void my_test_incorrect(std::string s) {
    s21::Notation no;
    char * ch = (char*)s.c_str();
    bool che = no.inp(&ch);
    ASSERT_FALSE(che);
}

void my_test_with_x(std::string s, double x, double result) {
    s21::Notation no;
    char * ch = (char*)s.c_str();
    no.inp(&ch);
    ASSERT_EQ(no.polish(x),result);
}

TEST(calc, testNumbers) {
    my_test("1+2",3);
    my_test("-100",-100);
    my_test("10000000",10000000);
    my_test("4",4);
    my_test("+4",4);
    my_test("2 + +4",6);
    my_test("1e-2",0.01);

}

TEST(calc, testExpressions) {
  my_test("1+2", 3);
  my_test("-7 / 5", -7.0 / 5.0);
  my_test("sin44", sin(44));
  my_test("3*sqrt2", 3.0 * sqrt(2.0));
  my_test("cos(sin3)", cos(std::sin(3)));
  my_test("-sin5", -sin(5.0));
  my_test("9mod3", 0);
  my_test("     log     3     ", log10(3));
  my_test("-(1+2)", -3);
  my_test("tan(1)", tan(1));
  my_test("acos(1)", acos(1));

}

TEST(calc, testCompoudExpressionss) {
  my_test("3 * (-4 ^ 2)", 48);
  my_test("(1+2)*(-3/0.5)", -18);
  my_test("1-2-3-4-5-6", 1 - 2 - 3 - 4 - 5 - 6);
  my_test("1-(-2-(3-4/(-7))*(5-6/(7-8)))",
         1 - (-2 - (3 - 4.0 / (-7.0)) * (5 - 6 / (7 - 8))));
  my_test("1-(2-(3-(4/8)*(-1-7))-3) ",
         1.0 - (2.0 - (3.0 - (4.0 / 8.0) * (-1.0 - 7.0)) - 3.0));
}

TEST(calc, TestCorrectX) {
  my_test_with_x("3-x", -7, 10);
  my_test_with_x("asin(x)", sin(3), asin(sin(3)));
  my_test_with_x("asin(1 / ln(x^x))", -2, asin(1 / log(pow(-2, -2))));
  my_test_with_x("(5 * 2 / 70) * atanx", 77.7, (5.0 * 2.0 / 70) * atan(77.7));
}

TEST(calc, TestIncorrect) {
  my_test_incorrect("(1+2");
  my_test_incorrect("13 13");
  my_test_incorrect("sin(x) - f");
  my_test_incorrect("(1+2)2");
  my_test_incorrect("s i n (x)");
  my_test_incorrect("12+3)");
  my_test_incorrect("1+(2+(-3)");
  my_test_incorrect("cossinp");
  my_test_incorrect("1-(2-(3.3.3)-4)");
  my_test_incorrect("sin(X^(cos(x))");
  my_test_incorrect("1e3.4");
  my_test_incorrect("sinnnn");
}