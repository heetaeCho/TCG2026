#include <gtest/gtest.h>

#include "prog.h"



namespace re2 {



class ProgTest : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_ReturnsNullWhenSizeLessThanPrefixSize_419) {

    const char* data = "test";

    size_t size = 3; // Assuming prefix_size_ is at least 4

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), nullptr);

}



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_ReturnsNullWhenNoMatchFound_419) {

    const char* data = "abcdefg";

    size_t size = 7; // Assuming prefix_size_ is less than or equal to 7 and no match in data

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), nullptr);

}



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_ReturnsPointerToMatchStart_419) {

    const char* data = "\x00\x00\x00\x00\x00\x00\x00\xC0"; // Assuming prefix_dfa_ is configured to match at the 8th byte

    size_t size = 8; // Assuming prefix_size_ is less than or equal to 8

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), data + 1);

}



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_HandlesBoundaryConditionsWithExactSize_419) {

    const char* data = "\x00\x00\x00\x00\x00\x00\x00\xC0"; // Assuming prefix_dfa_ is configured to match at the 8th byte

    size_t size = 8; // Exact size

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), data + 1);

}



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_HandlesBoundaryConditionsWithSizeLessThanBlock_419) {

    const char* data = "\x00\xC0"; // Assuming prefix_dfa_ is configured to match at the 2nd byte

    size_t size = 2; // Less than block size of 8

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), data + 1);

}



TEST_F(ProgTest_419, PrefixAccel_ShiftDFA_HandlesBoundaryConditionsWithSizeGreaterThanBlock_419) {

    const char* data = "\x00\x00\x00\x00\x00\x00\x00\xC0\x00"; // Assuming prefix_dfa_ is configured to match at the 8th byte

    size_t size = 9; // Greater than block size of 8

    EXPECT_EQ(prog->PrefixAccel_ShiftDFA(data, size), data + 1);

}



} // namespace re2
