#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "stream.h"



using namespace YAML;

using ::testing::_;

using ::testing::Return;



class StreamTest_77 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;



    StreamTest_77() : input(""), stream(input) {}

};



TEST_F(StreamTest_77, ColumnInitialValue_77) {

    EXPECT_EQ(stream.column(), 0);

}



TEST_F(StreamTest_77, LineInitialValue_77) {

    EXPECT_EQ(stream.line(), 0);

}



TEST_F(StreamTest_77, PosInitialValue_77) {

    EXPECT_EQ(stream.mark().pos, 0);

}



TEST_F(StreamTest_77, PeekEmptyStream_77) {

    EXPECT_EQ(stream.peek(), Stream::eof());

}



TEST_F(StreamTest_77, GetEmptyStream_77) {

    EXPECT_TRUE(stream.get() == Stream::eof());

}



TEST_F(StreamTest_77, GetMultipleCharsFromStream_77) {

    input.str("abc");

    EXPECT_EQ(stream.get(), 'a');

    EXPECT_EQ(stream.get(), 'b');

    EXPECT_EQ(stream.get(), 'c');

    EXPECT_TRUE(stream.get() == Stream::eof());

}



TEST_F(StreamTest_77, PeekDoesNotAdvancePosition_77) {

    input.str("abc");

    EXPECT_EQ(stream.peek(), 'a');

    EXPECT_EQ(stream.peek(), 'a');

}



TEST_F(StreamTest_77, EatAdvancesPosition_77) {

    input.str("abc");

    stream.eat(1);

    EXPECT_EQ(stream.get(), 'b');

}



TEST_F(StreamTest_77, ResetColumnResetsToZero_77) {

    input.str("a\nbc");

    stream.get(); // Move to the next line

    stream.eat(2); // Move past b and c

    EXPECT_GT(stream.column(), 0);

    stream.ResetColumn();

    EXPECT_EQ(stream.column(), 0);

}



TEST_F(StreamTest_77, ColumnAdvancesWithGet_77) {

    input.str("abc");

    stream.get(); // 'a'

    EXPECT_EQ(stream.column(), 1);

    stream.get(); // 'b'

    EXPECT_EQ(stream.column(), 2);

}



TEST_F(StreamTest_77, LineAdvancesOnNewline_77) {

    input.str("a\nbc");

    stream.get(); // 'a'

    EXPECT_EQ(stream.line(), 0);

    stream.get(); // '\n'

    EXPECT_EQ(stream.line(), 1);

    stream.get(); // 'b'

    EXPECT_EQ(stream.line(), 1);

}



TEST_F(StreamTest_77, GetMultipleCharsAtOnce_77) {

    input.str("abc");

    EXPECT_EQ(stream.get(3), "abc");

    EXPECT_TRUE(stream.get() == Stream::eof());

}
