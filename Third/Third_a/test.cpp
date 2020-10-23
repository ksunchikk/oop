#include "pch.h"
#include "pch.h"
#include "../laba 3/BigInt_a.h"
#include "../laba 3/BigInt_a.cpp"

using namespace Prog3a;

TEST(Constructors, Defaultconstructor) {
    BigInt A;
    ASSERT_EQ(0, A.ToInt());
}
TEST(Constructors, String_constructor) {
    char check1[] = "0000";
    BigInt A = BigInt(check1);
    ASSERT_EQ(0, A.ToInt());
    char check2[] = "-000";
    A = BigInt(check2);
    ASSERT_EQ(0, A.ToInt());
    char check3[] = "-34";
    A = BigInt(check3);
    ASSERT_EQ(-34, A.ToInt());
    char check4[] = "-0034";
    A = BigInt(check4);
    ASSERT_EQ(-34, A.ToInt());
    char check5[] = "aaa";
    ASSERT_ANY_THROW(BigInt C(check5));
    char check6[] = "1234567898765432345678998765434567890987654323456789098765434567898765456789";
    ASSERT_ANY_THROW(BigInt D(check6));
}
TEST(Constructors, Int_constructor) {
    BigInt A(9876);
    ASSERT_EQ(9876, A.ToInt());
    BigInt B(-423);
    ASSERT_EQ(-423, B.ToInt());
}
TEST(Methods, Additional_code) {
    BigInt A("0");
    A = A.AddCode();
    ASSERT_EQ(0, A.ToInt());
    BigInt B("11");
    B = B.AddCode();
    ASSERT_EQ(11,B.ToInt());
    BigInt C("-864");
    C = C.AddCode();
    ASSERT_EQ(-136, C.ToInt());
}
TEST(Methods, Sum) {
    BigInt A1("123");
    BigInt B1("768");
    BigInt Sum1 = A1.Sum(B1);
    ASSERT_EQ(891, Sum1.ToInt());
    BigInt A2("-123");
    BigInt B2("7686");
    BigInt Sum2 = A2.Sum(B2);
    ASSERT_EQ(7563, Sum2.ToInt());
    BigInt A3("123");
    BigInt B3("-7687686");
    BigInt Sum3 = A3.Sum(B3);
    ASSERT_EQ(-7687563, Sum3.ToInt());
    BigInt A4("999999999");
    BigInt B4("-7687686");
    BigInt Sum4 = A4.Sum(B4);
    ASSERT_EQ(992312313, Sum4.ToInt());
    BigInt A5("-123");
    BigInt B5("-7686");
    BigInt Sum5 = A5.Sum(B5);
    ASSERT_EQ(-7809, Sum5.ToInt());
    BigInt A6("0");
    BigInt B6("-76");
    BigInt Sum6 = A6.Sum(B6);
    ASSERT_EQ(-76, Sum6.ToInt());
    BigInt A7("1");
    BigInt B7("99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A7.Sum(B7));
}
TEST(Methods, Subtruction) {
    BigInt A1("123");
    BigInt B1("768");
    BigInt Sub1 = A1.Subtraction(B1);
    ASSERT_EQ(-645, Sub1.ToInt());
    BigInt A2("123");
    BigInt B2("123");
    BigInt Sub2 = A2.Subtraction(B2);
    ASSERT_EQ(0, Sub2.ToInt());
    BigInt A3("-123");
    BigInt B3("7686");
    BigInt Sub3 = A3.Subtraction(B3);
    ASSERT_EQ(-7809, Sub3.ToInt());
    BigInt A4("123");
    BigInt B4("-7687686");
    BigInt Sub4 = A4.Subtraction(B4);
    ASSERT_EQ(7687809, Sub4.ToInt());
    BigInt A5("-999999999");
    BigInt B5("-7687686");
    BigInt Sub5 = A5.Subtraction(B5);
    ASSERT_EQ(-992312313, Sub5.ToInt());
    BigInt A6("-123");
    BigInt B6("-7686");
    BigInt Sub6 = A6.Subtraction(B6);
    ASSERT_EQ(7563, Sub6.ToInt());
    BigInt A7("0");
    BigInt B7("-76");
    BigInt Sub7 = A7.Subtraction(B7);
    ASSERT_EQ(76, Sub7.ToInt());
    BigInt A8("1");
    BigInt B8("-99999999999999999999999999999999999999999999999");
    ASSERT_ANY_THROW(A8.Subtraction(B8));
}
TEST(Methods, Increase) {
    BigInt A("0");
    A = A.Inc();
    ASSERT_EQ(0, A.ToInt());
    BigInt B("11");
    B = B.Inc();
    ASSERT_EQ(110, B.ToInt());
    BigInt C("-864");
    C = C.Inc();
    ASSERT_EQ(-8640, C.ToInt());
    BigInt D("11111111111111111111111111111111111111111111111");
    ASSERT_ANY_THROW(D.Inc());
}
TEST(Methods, Decrease) {
    BigInt A("0");
    A = A.Dec();
    ASSERT_EQ(0, A.ToInt());
    BigInt B("1");
    B = B.Dec();
    ASSERT_EQ(0, B.ToInt());
    BigInt C("-864");
    C = C.Dec();
    ASSERT_EQ(-86, C.ToInt());
    BigInt D("111");
    D = D.Dec();
    ASSERT_EQ(11, D.ToInt());
}
int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}