#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/scantag.cpp"

#include "yaml-cpp/src/stream.h"

#include "yaml-cpp/src/regex_yaml.h"



using namespace YAML;

using ::testing::_;

using ::testing::Return;



class StreamMock : public Stream {

public:

    MOCK_METHOD(bool, operator bool, (), (const));

    MOCK_METHOD(char, peek, (), (const));

    MOCK_METHOD(char, get, (), ());

    MOCK_METHOD(std::string, get, (int), ());

    MOCK_METHOD(void, eat, (int), ());

    MOCK_METHOD(Mark, mark, (), (const));



    StreamMock(std::istream &input) : Stream(input) {}

};



class ScanTagSuffixTest_164 : public ::testing::Test {

protected:

    std::istringstream input;

    StreamMock stream;



    ScanTagSuffixTest_164() : input(""), stream(input) {

        ON_CALL(stream, operator bool()).WillByDefault(Return(true));

    }

};



TEST_F(ScanTagSuffixTest_164, NormalOperation_164) {

    EXPECT_CALL(stream, get(_)).WillOnce(Return("suffix"));

    EXPECT_CALL(stream, mark()).Times(0);



    std::string result = ScanTagSuffix(stream);

    EXPECT_EQ(result, "suffix");

}



TEST_F(ScanTagSuffixTest_164, EmptyInput_164) {

    EXPECT_CALL(stream, get(_)).WillOnce(Return(""));

    EXPECT_CALL(stream, mark()).Times(1);



    EXPECT_THROW({

        try {

            ScanTagSuffix(stream);

        } catch (const ParserException& e) {

            EXPECT_STREQ(e.msg(), ErrorMsg::TAG_WITH_NO_SUFFIX);

            throw;

        }

    }, ParserException);

}



TEST_F(ScanTagSuffixTest_164, SingleCharacterInput_164) {

    EXPECT_CALL(stream, get(_)).WillOnce(Return("a"));

    EXPECT_CALL(stream, mark()).Times(0);



    std::string result = ScanTagSuffix(stream);

    EXPECT_EQ(result, "a");

}



TEST_F(ScanTagSuffixTest_164, MultipleCharactersInput_164) {

    EXPECT_CALL(stream, get(_)).WillOnce(Return("suffix"));

    EXPECT_CALL(stream, mark()).Times(0);



    std::string result = ScanTagSuffix(stream);

    EXPECT_EQ(result, "suffix");

}



TEST_F(ScanTagSuffixTest_164, StreamEndsPrematurely_164) {

    ON_CALL(stream, operator bool()).WillByDefault(Return(false));

    EXPECT_CALL(stream, get(_)).WillOnce(Return("partial"));

    EXPECT_CALL(stream, mark()).Times(1);



    EXPECT_THROW({

        try {

            ScanTagSuffix(stream);

        } catch (const ParserException& e) {

            EXPECT_STREQ(e.msg(), ErrorMsg::TAG_WITH_NO_SUFFIX);

            throw;

        }

    }, ParserException);

}



TEST_F(ScanTagSuffixTest_164, StreamDoesNotMatch_164) {

    ON_CALL(stream, operator bool()).WillByDefault(Return(false));

    EXPECT_CALL(stream, get(_)).WillOnce(Return(""));

    EXPECT_CALL(stream, mark()).Times(1);



    EXPECT_THROW({

        try {

            ScanTagSuffix(stream);

        } catch (const ParserException& e) {

            EXPECT_STREQ(e.msg(), ErrorMsg::TAG_WITH_NO_SUFFIX);

            throw;

        }

    }, ParserException);

}
