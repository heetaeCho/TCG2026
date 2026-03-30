#include <gtest/gtest.h>



namespace re2 {



// Assuming fullrune function signature and behavior based on given code.

int fullrune(const char *str, int n);



class FullRuneTest_207 : public ::testing::Test {};



TEST_F(FullRuneTest_207, SingleByteCharacter_207) {

    const char str[] = {'a'};

    EXPECT_EQ(fullrune(str, 1), 1);

}



TEST_F(FullRuneTest_207, TwoByteCharacterWithinLimit_207) {

    const char str[] = {static_cast<char>(0xC2), static_cast<char>(0x94)};

    EXPECT_EQ(fullrune(str, 2), 1);

}



TEST_F(FullRuneTest_207, ThreeByteCharacterWithinLimit_207) {

    const char str[] = {static_cast<char>(0xE2), static_cast<char>(0x89), static_cast<char>(0xA0)};

    EXPECT_EQ(fullrune(str, 3), 1);

}



TEST_F(FullRuneTest_207, FourByteCharacterWithinLimit_207) {

    const char str[] = {static_cast<char>(0xF0), static_cast<char>(0x9F), static_cast<char>(0x98), static_cast<char>(0x86)};

    EXPECT_EQ(fullrune(str, 4), 1);

}



TEST_F(FullRuneTest_207, SingleByteCharacterWithNZero_207) {

    const char str[] = {'a'};

    EXPECT_EQ(fullrune(str, 0), 0);

}



TEST_F(FullRuneTest_207, TwoByteCharacterWithNSmallerThanRequired_207) {

    const char str[] = {static_cast<char>(0xC2)};

    EXPECT_EQ(fullrune(str, 1), 0);

}



TEST_F(FullRuneTest_207, ThreeByteCharacterWithNSmallerThanRequired_207) {

    const char str[] = {static_cast<char>(0xE2)};

    EXPECT_EQ(fullrune(str, 1), 0);



    const char str2[] = {static_cast<char>(0xE2), static_cast<char>(0x89)};

    EXPECT_EQ(fullrune(str2, 2), 0);

}



TEST_F(FullRuneTest_207, FourByteCharacterWithNSmallerThanRequired_207) {

    const char str[] = {static_cast<char>(0xF0)};

    EXPECT_EQ(fullrune(str, 1), 0);



    const char str2[] = {static_cast<char>(0xF0), static_cast<char>(0x9F)};

    EXPECT_EQ(fullrune(str2, 2), 0);



    const char str3[] = {static_cast<char>(0xF0), static_cast<char>(0x9F), static_cast<char>(0x98)};

    EXPECT_EQ(fullrune(str3, 3), 0);

}



TEST_F(FullRuneTest_207, InvalidTwoByteSequence_207) {

    const char str[] = {static_cast<char>(0xC2), static_cast<char>(0x7F)}; // invalid continuation byte

    EXPECT_EQ(fullrune(str, 2), 1); // The function does not check for valid sequences, only length.

}



TEST_F(FullRuneTest_207, InvalidThreeByteSequence_207) {

    const char str[] = {static_cast<char>(0xE2), static_cast<char>(0x89), static_cast<char>(0x1F)}; // invalid continuation byte

    EXPECT_EQ(fullrune(str, 3), 1); // The function does not check for valid sequences, only length.

}



TEST_F(FullRuneTest_207, InvalidFourByteSequence_207) {

    const char str[] = {static_cast<char>(0xF0), static_cast<char>(0x9F), static_cast<char>(0x98), static_cast<char>(0x01)}; // valid but not checked

    EXPECT_EQ(fullrune(str, 4), 1); // The function does not check for valid sequences, only length.

}



TEST_F(FullRuneTest_207, SingleByteCharacterWithNLargerThanRequired_207) {

    const char str[] = {'a'};

    EXPECT_EQ(fullrune(str, 5), 1);

}



TEST_F(FullRuneTest_207, TwoByteCharacterWithNLargerThanRequired_207) {

    const char str[] = {static_cast<char>(0xC2), static_cast<char>(0x94)};

    EXPECT_EQ(fullrune(str, 5), 1);

}



TEST_F(FullRuneTest_207, ThreeByteCharacterWithNLargerThanRequired_207) {

    const char str[] = {static_cast<char>(0xE2), static_cast<char>(0x89), static_cast<char>(0xA0)};

    EXPECT_EQ(fullrune(str, 5), 1);

}



TEST_F(FullRuneTest_207, FourByteCharacterWithNLargerThanRequired_207) {

    const char str[] = {static_cast<char>(0xF0), static_cast<char>(0x9F), static_cast<char>(0x98), static_cast<char>(0x86)};

    EXPECT_EQ(fullrune(str, 5), 1);

}



} // namespace re2
