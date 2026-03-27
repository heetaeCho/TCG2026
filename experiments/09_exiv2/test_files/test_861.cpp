#include <gtest/gtest.h>

#include "value.cpp"  // Assuming this is how we include the partial implementation



namespace Exiv2 {

    class LangAltValueTest_861 : public ::testing::Test {

    protected:

        LangAltValue langAltValue;

    };



    TEST_F(LangAltValueTest_861, ToRational_NormalOperation_861) {

        size_t n = 0;

        Rational result = langAltValue.toRational(n);

        EXPECT_EQ(result.first, 0);

        EXPECT_EQ(result.second, 0);

    }



    TEST_F(LangAltValueTest_861, ToRational_BoundaryCondition_861) {

        size_t n = SIZE_MAX;

        Rational result = langAltValue.toRational(n);

        EXPECT_EQ(result.first, 0);

        EXPECT_EQ(result.second, 0);

    }



    TEST_F(LangAltValueTest_861, ToRational_VerifyStateChange_861) {

        size_t n = 0;

        bool initialOk = langAltValue.ok_;

        Rational result = langAltValue.toRational(n);

        EXPECT_FALSE(langAltValue.ok_);

    }

}
