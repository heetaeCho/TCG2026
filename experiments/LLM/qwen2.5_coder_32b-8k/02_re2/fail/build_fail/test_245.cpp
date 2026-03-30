#include <gtest/gtest.h>

#include "re2/re2.h"



namespace re2 {



class RE2Test : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RE2Test_245, ReverseProgramSize_ReturnsMinusOne_WhenProgIsNull_245) {

    RE2 re("(?P<name>\\w+)");

    const_cast<re2::Prog*&>(re.rprog_) = nullptr; // Simulate prog_ being null

    EXPECT_EQ(re.ReverseProgramSize(), -1);

}



TEST_F(RE2Test_245, ReverseProgramSize_ReturnsMinusOne_WhenReverseProgReturnsNull_245) {

    RE2 re("(?P<name>\\w+)");

    const_cast<re2::Prog*&>(re.rprog_) = new Prog(); // Simulate prog_ being valid

    delete re.ReverseProg(); // Simulate ReverseProg() returning null

    EXPECT_EQ(re.ReverseProgramSize(), -1);

}



TEST_F(RE2Test_245, ReverseProgramSize_ReturnsValidSize_WhenReverseProgIsValid_245) {

    RE2 re("(?P<name>\\w+)");

    const_cast<re2::Prog*&>(re.rprog_) = new Prog(); // Simulate prog_ being valid

    EXPECT_GT(re.ReverseProgramSize(), -1);

}



TEST_F(RE2Test_245, ReverseProgramSize_BoundaryCondition_EmptyPattern_245) {

    RE2 re("");

    EXPECT_EQ(re.ReverseProgramSize(), 0); // Assuming empty pattern results in size 0

}



TEST_F(RE2Test_245, ReverseProgramSize_ExceptionalCase_InvalidPattern_245) {

    RE2 re("(?P<name>\\w+"); // Invalid pattern (unmatched parenthesis)

    EXPECT_EQ(re.ReverseProgramSize(), -1); // Assuming invalid pattern results in size -1

}



}  // namespace re2
