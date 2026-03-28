#include <gtest/gtest.h>

#include "re2/regexp.h"



namespace re2 {

    class RegexpTest_168 : public ::testing::Test {

    protected:

        // Setup and teardown can be used if needed in the future.

        void SetUp() override {}

        void TearDown() override {}

    };



    TEST_F(RegexpTest_168, ParseFlagsOrOperatorNormalOperation_168) {

        Regexp::ParseFlags flag1 = Regexp::ParseFlagCaseInsensitive;

        Regexp::ParseFlags flag2 = Regexp::ParseFlagMultiline;



        Regexp::ParseFlags combinedFlags = flag1 | flag2;



        EXPECT_EQ(combinedFlags, static_cast<Regexp::ParseFlags>(static_cast<int>(flag1) | static_cast<int>(flag2)));

    }



    TEST_F(RegexpTest_168, ParseFlagsOrOperatorBoundaryConditions_168) {

        Regexp::ParseFlags flagNone = static_cast<Regexp::ParseFlags>(0);

        Regexp::ParseFlags flagAll = static_cast<Regexp::ParseFlags>(~0);



        EXPECT_EQ(flagNone | flagNone, flagNone);

        EXPECT_EQ(flagAll | flagAll, flagAll);

    }



    TEST_F(RegexpTest_168, ParseFlagsOrOperatorExceptionalCases_168) {

        // Assuming no exceptional cases for bitwise OR operator with enums in this context.

        // If there are specific flags that could lead to undefined behavior, they should be tested here.

        Regexp::ParseFlags flag1 = Regexp::ParseFlagCaseInsensitive;

        Regexp::ParseFlags flag2 = static_cast<Regexp::ParseFlags>(~0);



        EXPECT_EQ(flag1 | flag2, flag2); // OR with all bits set should result in all bits set

    }

}
