#include <gtest/gtest.h>

#include "catch2/catch_approx.hpp"



using namespace Catch;



class ApproxTest_705 : public ::testing::Test {

protected:

    Approx approx1;

    Approx approx2;



    ApproxTest_705() : approx1(1.0), approx2(-1.0) {}

};



TEST_F(ApproxTest_705, ConstructorWithDouble_705) {

    EXPECT_DOUBLE_EQ(approx1.m_value, 1.0);

}



TEST_F(ApproxTest_705, ConstructorWithTemplate_705) {

    Approx approx3 = Approx(2.0f); // float to double conversion

    EXPECT_DOUBLE_EQ(approx3.m_value, 2.0);

}



TEST_F(ApproxTest_705, OperatorNegation_705) {

    Approx negatedApprox1 = -approx1;

    EXPECT_DOUBLE_EQ(negatedApprox1.m_value, -1.0);



    Approx negatedApprox2 = -approx2;

    EXPECT_DOUBLE_EQ(negatedApprox2.m_value, 1.0);

}



TEST_F(ApproxTest_705, SetMargin_705) {

    approx1.margin(0.5);

    EXPECT_DOUBLE_EQ(approx1.m_margin, 0.5);

}



TEST_F(ApproxTest_705, SetEpsilon_705) {

    approx2.epsilon(0.01);

    EXPECT_DOUBLE_EQ(approx2.m_epsilon, 0.01);

}



TEST_F(ApproxTest_705, SetScale_705) {

    approx1.scale(2.0);

    EXPECT_DOUBLE_EQ(approx1.m_scale, 2.0);

}



TEST_F(ApproxTest_705, CustomApprox_705) {

    Approx customApprox = Approx::custom();

    EXPECT_DOUBLE_EQ(customApprox.m_value, 0.0);

}



TEST_F(ApproxTest_705, ToString_705) {

    std::string str1 = approx1.toString();

    std::string expectedStr1 = "Approx( 1 )";

    EXPECT_EQ(str1, expectedStr1);



    std::string str2 = approx2.toString();

    std::string expectedStr2 = "Approx( -1 )";

    EXPECT_EQ(str2, expectedStr2);

}



TEST_F(ApproxTest_705, EqualityComparisonImpl_EqualValues_705) {

    bool isEqual = approx1.equalityComparisonImpl(1.0);

    EXPECT_TRUE(isEqual);



    isEqual = approx2.equalityComparisonImpl(-1.0);

    EXPECT_TRUE(isEqual);

}



TEST_F(ApproxTest_705, EqualityComparisonImpl_NotEqualValues_705) {

    bool isEqual = approx1.equalityComparisonImpl(2.0);

    EXPECT_FALSE(isEqual);



    isEqual = approx2.equalityComparisonImpl(0.0);

    EXPECT_FALSE(isEqual);

}
