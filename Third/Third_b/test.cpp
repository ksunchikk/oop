#include "pch.h"
#include "../laba 3b/BigInt_b.h"
#include "../laba 3b/BigInt_b.cpp"

using namespace Prog3b;

TEST(Constructors, Defaultconstructor) {
    BigInt A;
    ASSERT_EQ(0, (int)A);
}
TEST(Constructors, String_constructor) {
    char check1[] = "0000";
    BigInt A = BigInt(check1);
    ASSERT_EQ(0, (int)A);
    char check2[] = "-000";
    A = BigInt(check2);
    ASSERT_EQ(0, (int)A);
    char check3[] = "-34";
    A = BigInt(check3);
    ASSERT_EQ(-34,(int)A);
    char check4[] = "-0034";
    A = BigInt(check4);
    ASSERT_EQ(-34, (int)A);
    char check5[] = "aaa";
    ASSERT_ANY_THROW(BigInt C(check5));
    char check6[] = "1234567898765432345678998765434567890987654323456789098765434567898765456789";
    ASSERT_ANY_THROW(BigInt D(check6));
}
TEST(Constructors, Int_constructor) {
    BigInt A(9876);
    ASSERT_EQ(9876, (int)A);
    BigInt B(-423);
    ASSERT_EQ(-423, (int)B);
}
TEST(Operators, Operator_invertion) {
    BigInt A("0");
    A = ~A;
    ASSERT_EQ(0, (int)A);
    BigInt B("11");
    B = ~B;
    ASSERT_EQ(11, (int)B);
    BigInt C("-864");
    C = ~C;
    ASSERT_EQ(-136, (int)C);
}
TEST(Operators, Operator_addition) {
    BigInt A1("123");
    BigInt B1("768");
    BigInt Sum1 = A1+B1;
    ASSERT_EQ(891,(int) Sum1);
    BigInt A2("-123");
    BigInt B2("7686");
    BigInt Sum2 = A2+(B2);
    ASSERT_EQ(7563, (int)Sum2);
    BigInt A3("123");
    BigInt B3("-7687686");
    BigInt Sum3 = A3+(B3);
    ASSERT_EQ(-7687563, (int)Sum3);
    BigInt A4("99999999");
    BigInt B4("-7687686");
    BigInt Sum4 = A4+(B4);
    ASSERT_EQ(92312313, (int)Sum4);
    BigInt A5("-123");
    BigInt B5("-7686");
    BigInt Sum5 = A5+(B5);
    ASSERT_EQ(-7809, (int)Sum5);
    BigInt A6("0");
    BigInt B6("-76");
    BigInt Sum6 = A6+(B6);
    ASSERT_EQ(-76, (int)Sum6);
    Sum6 = BigInt(35) + A6 + B6 + BigInt("74") + BigInt(12);
    ASSERT_EQ(45, (int)Sum6);
    BigInt A7("1");
    BigInt B7("99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A7+(B7));
}
TEST(Operators, Operator_subtruction) {
    BigInt A1("123");
    BigInt B1("768");
    BigInt Sub1 = A1-(B1);
    ASSERT_EQ(-645, Sub1);
    BigInt A2("123");
    BigInt B2("123");
    BigInt Sub2 = A2-(B2);
    ASSERT_EQ(0, (int)Sub2);
    BigInt A3("-123");
    BigInt B3("7686");
    BigInt Sub3 = A3-(B3);
    ASSERT_EQ(-7809, (int)Sub3);
    BigInt A4("123");
    BigInt B4("-7687686");
    BigInt Sub4 = A4-(B4);
    ASSERT_EQ(7687809, (int)Sub4);
    BigInt A5("-99999999");
    BigInt B5("-7687686");
    BigInt Sub5 = A5-(B5);
    ASSERT_EQ(-92312313, (int)Sub5);
    BigInt A6("-123");
    BigInt B6("-7686");
    BigInt Sub6 = A6-(B6);
    ASSERT_EQ(7563, (int)Sub6);
    BigInt A7("0");
    BigInt B7("-76");
    BigInt Sub7 = A7-(B7);
    ASSERT_EQ(76, (int)Sub7);
    Sub6 = BigInt(35) - A7 - B7 + BigInt("74") + BigInt(12);
    ASSERT_EQ(197, (int)Sub6);
    BigInt A8("1");
    BigInt B8("-99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A8-(B8));
}
TEST(Operators, Operator_unminus) {
    BigInt A("0");
    ASSERT_EQ(0, (int)(-A));
    BigInt B(11);
    ASSERT_EQ(-11, (int)(-B));
    BigInt C(-1);
    ASSERT_EQ(1, (int)(-C));
}
TEST(Operators, Operator_move_left) {
    BigInt A("0");
    A=A<<=2;
    ASSERT_EQ(0,(int)A);
    BigInt B("11");
    B=B<<=3;
    ASSERT_EQ(11000, (int)B);
    BigInt C("-864");
    C=C <<= 1;
    ASSERT_EQ(-8640, (int)C);
    BigInt D("11111111111111111111111111111111111111111111111");
    ASSERT_ANY_THROW(D<<=5);
}
TEST(Operators, Operator_move_right) {
    BigInt A("0");
    A=A>>=4;
    ASSERT_EQ(0, (int)A);
    BigInt B("1");
    B=B >>=2;
    ASSERT_EQ(0, (int)B);
    BigInt C("-864");
    C=C>>=2;
    ASSERT_EQ(-8,(int)C);
    BigInt D("111");
    D=D>>=1;
    ASSERT_EQ(11, (int)D);
}
TEST(Operators, Operator_compare) {
    BigInt A1("123");
    BigInt B1("141");
    ASSERT_EQ(true, A1<B1);
    ASSERT_EQ(false, A1 > B1);
    ASSERT_EQ(false, A1 == B1);
    BigInt A2("3");
    BigInt B2("-31");
    ASSERT_EQ(true, A2 > B2);
    ASSERT_EQ(false, A2 < B2);
    ASSERT_EQ(false, A2 == B2);
    BigInt A3("-123");
    BigInt B3("-123");
    ASSERT_EQ(true, A3 == B3);
    ASSERT_EQ(false, A3 < B3);
    ASSERT_EQ(false, A3 > B3);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}