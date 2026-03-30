#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/simplify.h"



namespace re2 {



class RegexpTest_422 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed.

    }



    void TearDown() override {

        // Teardown code, if needed.

    }

};



TEST_F(RegexpTest_422, SimplifyNullInput_ReturnsNull_422) {

    Regexp* input = nullptr;

    EXPECT_EQ(input->Simplify(), nullptr);

}



TEST_F(RegexpTest_422, SimplifyCoalesceWalkerFails_ReturnsNull_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();

    EXPECT_CALL(*input, Walk).WillOnce(testing::Return(nullptr));



    EXPECT_EQ(input->Simplify(), nullptr);



    // Decrement ref count to ensure proper cleanup.

    input->Decref();

}



TEST_F(RegexpTest_422, SimplifyCoalesceWalkerStopsEarly_ReturnsNull_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();

    CoalesceWalker cw;

    EXPECT_CALL(*input, Walk).WillOnce(testing::DoAll(testing::SetArgReferee<1>(nullptr), testing::Return(nullptr)));



    EXPECT_EQ(input->Simplify(), nullptr);



    // Decrement ref count to ensure proper cleanup.

    input->Decref();

}



TEST_F(RegexpTest_422, SimplifySimplifyWalkerFails_ReturnsNull_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();

    CoalesceWalker cw;

    Regexp* cre = cw.Walk(input, nullptr);



    EXPECT_CALL(*cre, Walk).WillOnce(testing::Return(nullptr));



    EXPECT_EQ(input->Simplify(), nullptr);



    // Decrement ref count to ensure proper cleanup.

    input->Decref();

}



TEST_F(RegexpTest_422, SimplifySimplifyWalkerStopsEarly_ReturnsNull_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();

    CoalesceWalker cw;

    Regexp* cre = cw.Walk(input, nullptr);



    EXPECT_CALL(*cre, Walk).WillOnce(testing::DoAll(testing::SetArgReferee<1>(nullptr), testing::Return(nullptr)));



    EXPECT_EQ(input->Simplify(), nullptr);



    // Decrement ref count to ensure proper cleanup.

    input->Decref();

}



TEST_F(RegexpTest_422, SimplifyValidInput_ReturnsNonNull_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();



    EXPECT_NE(input->Simplify(), nullptr);



    // Decrement ref count to ensure proper cleanup.

    input->Decref();

}



TEST_F(RegexpTest_422, SimplifyMultipleCalls_ReturnsConsistentResults_422) {

    auto mockRegexp = std::make_unique<Regexp>(kRegexpNoMatch, kParseFlagsNone);

    Regexp* input = mockRegexp.release();



    Regexp* result1 = input->Simplify();

    Regexp* result2 = input->Simplify();



    EXPECT_EQ(result1, result2);



    // Decrement ref count to ensure proper cleanup.

    if (result1 != nullptr) {

        result1->Decref();

    }

    input->Decref();

}



}  // namespace re2
