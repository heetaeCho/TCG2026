#include <gtest/gtest.h>

#include <re2/regexp.h>



namespace re2 {



class CharClassTest_148 : public ::testing::Test {

protected:

    void SetUp() override {

        char_class = CharClass::New(10);

    }



    void TearDown() override {

        char_class->Delete();

    }



    CharClass* char_class;

};



TEST_F(CharClassTest_148, FoldsASCII_ReturnsFalseByDefault_148) {

    EXPECT_FALSE(char_class->FoldsASCII());

}



TEST_F(CharClassTest_148, Empty_ReturnsTrueForNewCharClass_148) {

    EXPECT_TRUE(char_class->empty());

}



TEST_F(CharClassTest_148, Full_ReturnsFalseForNewCharClass_148) {

    EXPECT_FALSE(char_class->full());

}



TEST_F(CharClassTest_148, Size_ReturnsZeroForNewCharClass_148) {

    EXPECT_EQ(char_class->size(), 0);

}



TEST_F(CharClassTest_148, BeginEnd_IteratorsAreEqualForEmptyCharClass_148) {

    EXPECT_EQ(char_class->begin(), char_class->end());

}



TEST_F(CharClassTest_148, Negate_ReturnsNewCharClass_148) {

    CharClass* negated = char_class->Negate();

    EXPECT_NE(negated, nullptr);

    negated->Delete();

}



TEST_F(CharClassTest_148, Contains_ReturnsFalseForArbitraryRuneInEmptyCharClass_148) {

    Rune r = 65; // Example rune 'A'

    EXPECT_FALSE(char_class->Contains(r));

}

}  // namespace re2
