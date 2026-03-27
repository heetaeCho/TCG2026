#include <gtest/gtest.h>

#include "catch_result_type.hpp"



namespace Catch {

    namespace ResultDisposition {

        enum Flags { Normal = 1, ContinueOnFailure = 2, FalseTest = 4, SuppressFail = 8 };

    }

}



class ResultTypeTest_63 : public ::testing::Test {

protected:

    // Additional setup can be done here if necessary

};



TEST_F(ResultTypeTest_63, IsFalseTest_ReturnsTrueForFalseTestFlag_63) {

    EXPECT_TRUE(Catch::isFalseTest(Catch::ResultDisposition::FalseTest));

}



TEST_F(ResultTypeTest_63, IsFalseTest_ReturnsFalseForNormalFlag_63) {

    EXPECT_FALSE(Catch::isFalseTest(Catch::ResultDisposition::Normal));

}



TEST_F(ResultTypeTest_63, IsFalseTest_ReturnsTrueForCombinationWithFalseTestFlag_63) {

    int combinedFlags = Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest;

    EXPECT_TRUE(Catch::isFalseTest(combinedFlags));

}



TEST_F(ResultTypeTest_63, IsFalseTest_ReturnsFalseForZeroFlags_63) {

    EXPECT_FALSE(Catch::isFalseTest(0));

}
