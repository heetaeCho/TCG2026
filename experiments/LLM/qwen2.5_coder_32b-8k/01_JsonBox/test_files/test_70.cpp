#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SolidusEscaper.h"

#include <sstream>



using namespace JsonBox;

using ::testing::Eq;



class SolidusEscaperTest_70 : public ::testing::Test {

protected:

    SolidusEscaper escaper;

    std::ostringstream oss;

};



TEST_F(SolidusEscaperTest_70, NormalCharacterOutsideString_70) {

    std::streambuf::int_type result = escaper(oss, 'a');

    EXPECT_EQ(result, 'a');

    EXPECT_EQ(oss.str(), "a");

}



TEST_F(SolidusEscaperTest_70, QuotationMarkStartsString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, 'a');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"a");

}



TEST_F(SolidusEscaperTest_70, QuotationMarkEndsString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, 'a');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"a");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"a\"");

}



TEST_F(SolidusEscaperTest_70, SolidusInStringNotEscaped_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '/');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"/");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"/\"");

}



TEST_F(SolidusEscaperTest_70, SolidusInStringEscaped_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '\\');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\");



    result = escaper(oss, '/');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\/");

}



TEST_F(SolidusEscaperTest_70, SolidusOutsideStringNotEscaped_70) {

    std::streambuf::int_type result = escaper(oss, '/');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "/");

}



TEST_F(SolidusEscaperTest_70, EscapedSolidusInStringEscaped_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '\\');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\");



    result = escaper(oss, '/');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\/");

}



TEST_F(SolidusEscaperTest_70, DoubleBackslashInString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '\\');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\");



    result = escaper(oss, '\\');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\\\");

}



TEST_F(SolidusEscaperTest_70, EndOfStringAfterBackslash_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '\\');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\\\"");

}



TEST_F(SolidusEscaperTest_70, EdgeCaseEmptyString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"\"");

}



TEST_F(SolidusEscaperTest_70, EdgeCaseSingleCharacterString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, 'a');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"a");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"a\"");

}



TEST_F(SolidusEscaperTest_70, EdgeCaseSingleSolidusInString_70) {

    std::streambuf::int_type result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"");



    result = escaper(oss, '/');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"/");



    result = escaper(oss, '"');

    EXPECT_NE(result, 0);

    EXPECT_EQ(oss.str(), "\"/");

}
