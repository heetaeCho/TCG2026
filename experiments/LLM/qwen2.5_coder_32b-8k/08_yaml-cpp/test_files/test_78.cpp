#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/stream.h"

#include <sstream>



using namespace YAML;

using ::testing::Test;



class StreamTest_78 : public Test {

protected:

    std::istringstream input_;

    Stream stream_;



    StreamTest_78() : input_(""), stream_(input_) {}

};



TEST_F(StreamTest_78, ResetColumnSetsColumnToZero_78) {

    // Arrange

    stream_.ResetColumn();



    // Act & Assert

    EXPECT_EQ(stream_.column(), 0);

}



TEST_F(StreamTest_78, PeekReturnsNextCharacterWithoutAdvancing_78) {

    // Arrange

    input_.str("abc");



    // Act

    char result = stream_.peek();



    // Assert

    EXPECT_EQ(result, 'a');

    EXPECT_EQ(stream_.column(), 0);

}



TEST_F(StreamTest_78, GetReturnsNextCharacterAndAdvancesColumn_78) {

    // Arrange

    input_.str("abc");



    // Act

    char result = stream_.get();



    // Assert

    EXPECT_EQ(result, 'a');

    EXPECT_EQ(stream_.column(), 1);

}



TEST_F(StreamTest_78, GetMultipleCharactersAdvancesColumnCorrectly_78) {

    // Arrange

    input_.str("abc");



    // Act

    std::string result = stream_.get(2);



    // Assert

    EXPECT_EQ(result, "ab");

    EXPECT_EQ(stream_.column(), 2);

}



TEST_F(StreamTest_78, EatAdvancesColumnByGivenAmount_78) {

    // Arrange

    input_.str("abc");



    // Act

    stream_.eat(2);



    // Assert

    EXPECT_EQ(stream_.column(), 2);

}



TEST_F(StreamTest_78, MarkReturnsCurrentMark_78) {

    // Arrange

    input_.str("a\nbc");

    stream_.get(); // Move to 'a'

    stream_.get(); // Move to '\n', which increments line and resets column



    // Act

    Mark mark = stream_.mark();



    // Assert

    EXPECT_EQ(mark.line, 1);

    EXPECT_EQ(mark.column, 0);

}



TEST_F(StreamTest_78, EndOfFileReturnsTrueWhenStreamIsExhausted_78) {

    // Arrange

    input_.str("a");



    // Act & Assert

    stream_.get(); // Move to 'a'

    EXPECT_FALSE(!stream_);

    stream_.get(); // Move to EOF

    EXPECT_TRUE(!stream_);

}



TEST_F(StreamTest_78, ColumnResetsWhenResetColumnIsCalled_78) {

    // Arrange

    input_.str("abc");

    stream_.get(); // Move to 'a'

    stream_.get(); // Move to 'b'



    // Act

    stream_.ResetColumn();



    // Assert

    EXPECT_EQ(stream_.column(), 0);

}
