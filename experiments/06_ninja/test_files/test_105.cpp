#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>



using namespace ::testing;



// Mocking dependencies if needed

struct MockAnsiColorSequenceIterator : public AnsiColorSequenceIterator {

    using AnsiColorSequenceIterator::AnsiColorSequenceIterator;

    MOCK_CONST_METHOD0(HasSequence, bool());

    MOCK_CONST_METHOD0(SequenceStart, size_t());

    MOCK_CONST_METHOD0(SequenceEnd, size_t());

    MOCK_CONST_METHOD0(SequenceSize, size_t());

    MOCK_CONST_METHOD1(SequenceContains, bool(size_t));

    MOCK_METHOD0(NextSequence, bool());

    MOCK_METHOD0(Reset, void());

};



TEST_F(VisibleInputCharsIteratorTest_105, ConstructorInitializesCorrectly_105) {

    std::string input = "test";

    VisibleInputCharsIterator iter(input);

    EXPECT_EQ(iter.InputIndex(), 0u);

}



TEST_F(VisibleInputCharsIteratorTest_105, HasCharReturnsTrueWhenInputIsNotEmpty_105) {

    std::string input = "test";

    VisibleInputCharsIterator iter(input);

    EXPECT_TRUE(iter.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_105, HasCharReturnsFalseWhenAtEndOfInput_105) {

    std::string input = "";

    VisibleInputCharsIterator iter(input);

    EXPECT_FALSE(iter.HasChar());

}



TEST_F(VisibleInputCharsIteratorTest_105, NextCharAdvancesIndex_105) {

    std::string input = "test";

    VisibleInputCharsIterator iter(input);

    iter.NextChar();

    EXPECT_EQ(iter.InputIndex(), 1u);

}



TEST_F(VisibleInputCharsIteratorTest_105, IsVisibleReturnsTrueWhenNotInSequence_105) {

    std::string input = "test";

    MockAnsiColorSequenceIterator mock_iter(input);

    EXPECT_CALL(mock_iter, SequenceContains(0)).WillOnce(Return(false));



    VisibleInputCharsIterator iter(input);

    iter.ansi_iter_ = mock_iter;



    EXPECT_TRUE(iter.IsVisible());

}



TEST_F(VisibleInputCharsIteratorTest_105, IsVisibleReturnsFalseWhenInSequence_105) {

    std::string input = "test";

    MockAnsiColorSequenceIterator mock_iter(input);

    EXPECT_CALL(mock_iter, SequenceContains(0)).WillOnce(Return(true));



    VisibleInputCharsIterator iter(input);

    iter.ansi_iter_ = mock_iter;



    EXPECT_FALSE(iter.IsVisible());

}



TEST_F(VisibleInputCharsIteratorTest_105, BoundaryConditionEmptyString_105) {

    std::string input = "";

    VisibleInputCharsIterator iter(input);



    EXPECT_FALSE(iter.HasChar());

    EXPECT_EQ(iter.InputIndex(), 0u);

    EXPECT_EQ(iter.VisiblePosition(), 0u);

}



TEST_F(VisibleInputCharsIteratorTest_105, BoundaryConditionSingleCharString_105) {

    std::string input = "a";

    VisibleInputCharsIterator iter(input);



    EXPECT_TRUE(iter.HasChar());

    EXPECT_EQ(iter.InputIndex(), 0u);

    EXPECT_EQ(iter.VisiblePosition(), 0u);

}
