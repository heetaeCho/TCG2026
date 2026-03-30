#include <gtest/gtest.h>

#include "catch2/internal/catch_result_type.hpp"



using namespace Catch;

using namespace Catch::ResultDisposition;



class ResultTypeTest_64 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_Normal_64) {

    EXPECT_FALSE(shouldSuppressFailure(Normal));

}



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_ContinueOnFailure_64) {

    EXPECT_FALSE(shouldSuppressFailure(ContinueOnFailure));

}



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_FalseTest_64) {

    EXPECT_FALSE(shouldSuppressFailure(FalseTest));

}



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_SuppressFail_64) {

    EXPECT_TRUE(shouldSuppressFailure(SuppressFail));

}



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_MultipleFlagsIncludingSuppressFail_64) {

    EXPECT_TRUE(shouldSuppressFailure(Normal | SuppressFail));

}



TEST_F(ResultTypeTest_64, ShouldSuppressFailure_MultipleFlagsExcludingSuppressFail_64) {

    EXPECT_FALSE(shouldSuppressFailure(Normal | ContinueOnFailure | FalseTest));

}
