#include <gtest/gtest.h>



namespace re2 {



// Mocking external collaborators if needed (none required here)



class OnePassTest_564 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(OnePassTest_564, VerifyEmptyFlagsConsistency_564) {

    // This test checks the consistency between kEmptyShift and kEmptyAllFlags

    EXPECT_EQ((1 << kEmptyShift) - 1, kEmptyAllFlags);

}



TEST_F(OnePassTest_564, VerifyMaxCapConsistency_564) {

    // This test checks the consistency between kMaxCap and kMaxOnePassCapture

    EXPECT_EQ(kMaxCap, Prog::kMaxOnePassCapture * 2);

}



// No additional observable behavior from OnePass_Checks function to test directly



}  // namespace re2
