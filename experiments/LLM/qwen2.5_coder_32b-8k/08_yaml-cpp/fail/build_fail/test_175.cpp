#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/src/stream.h>

#include <sstream>



using namespace YAML;

using ::testing::Eq;



class StreamTest : public ::testing::Test {

protected:

    std::istringstream input_stream_;

    Stream stream_;



    StreamTest() : input_stream_(""), stream_(input_stream_) {}



    void SetInput(const std::string& content) {

        input_stream_.str(content);

        input_stream_.clear();  // Reset the stream state

    }

};



TEST_F(StreamTest_175, GetReturnsCorrectCharacter_175) {

    SetInput("abc");

    EXPECT_EQ('a', stream_.get());

}



TEST_F(StreamTest_175, GetAdvancesColumn_175) {

    SetInput("ab");

    stream_.get();

    EXPECT_EQ(1, stream_.column());

}



TEST_F(StreamTest_175, GetNewLineAdvancesLineResetsColumn_175) {

    SetInput("\nabc");

    stream_.get();

    EXPECT_EQ(1, stream_.line());

    EXPECT_EQ(0, stream_.column());

}



TEST_F(StreamTest_175, GetCarriageReturnFollowedByNewLineAdvancesLineResetsColumn_175) {

    SetInput("\r\nabc");

    stream_.get();  // Consume '\r'

    stream_.get();  // Consume '\n'

    EXPECT_EQ(1, stream_.line());

    EXPECT_EQ(0, stream_.column());

}



TEST_F(StreamTest_175, GetCarriageReturnOnlyAdvancesLineResetsColumn_175) {

    SetInput("\rabc");

    stream_.get();  // Consume '\r'

    EXPECT_EQ(1, stream_.line());

    EXPECT_EQ(0, stream_.column());

}



TEST_F(StreamTest_175, GetEofReturnsEofCharacter_175) {

    SetInput("");

    EXPECT_EQ('\0', stream_.get());  // Assuming get returns '\0' for EOF

}



TEST_F(StreamTest_175, PeekDoesNotAdvanceColumn_175) {

    SetInput("abc");

    stream_.peek();

    EXPECT_EQ(0, stream_.column());

}



TEST_F(StreamTest_175, GetMultipleCharactersAdvancesColumnCorrectly_175) {

    SetInput("abc");

    stream_.get();  // Consume 'a'

    stream_.get();  // Consume 'b'

    EXPECT_EQ(2, stream_.column());

}
