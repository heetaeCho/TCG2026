#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JsonBox/Indenter.h"
#include <sstream>
using namespace JsonBox;
using ::testing::_;
using ::testing::Eq;

class IndenterTest_4 : public ::testing::Test {
protected:
    Indenter indenter;
};

TEST_F(IndenterTest_4, PutAtStartOfLineAddsTab_4) {
    std::ostringstream oss;
    auto result = indenter(*oss.rdbuf(), 'a');
    EXPECT_EQ('\t', oss.str()[0]);
    EXPECT_EQ('a', oss.str()[1]);
    EXPECT_EQ(result, static_cast<std::streambuf::int_type>('a'));
}

TEST_F(IndenterTest_4, PutAfterNewLineDoesNotAddTab_4) {
    std::ostringstream oss;
    indenter(*oss.rdbuf(), '\n');
    auto result = indenter(*oss.rdbuf(), 'b');
    EXPECT_EQ('\n', oss.str()[0]);
    EXPECT_EQ('b', oss.str()[1]);
    EXPECT_EQ(result, static_cast<std::streambuf::int_type>('b'));
}

TEST_F(IndenterTest_4, PutMultipleLinesAddTabsCorrectly_4) {
    std::ostringstream oss;
    indenter(*oss.rdbuf(), 'c');
    indenter(*oss.rdbuf(), '\n');
    indenter(*oss.rdbuf(), 'd');
    EXPECT_EQ("\tc\n\td", oss.str());
}

TEST_F(IndenterTest_4, PutNewLineAtStartOfLineDoesNothing_4) {
    std::ostringstream oss;
    auto result = indenter(*oss.rdbuf(), '\n');
    EXPECT_EQ('\n', oss.str()[0]);
    EXPECT_EQ(result, static_cast<std::streambuf::int_type>('\n'));
}

TEST_F(IndenterTest_4, PutNonNewLineAfterNonNewLineDoesNotAddTab_4) {
    std::ostringstream oss;
    indenter(*oss.rdbuf(), 'e');
    auto result = indenter(*oss.rdbuf(), 'f');
    EXPECT_EQ("\tef", oss.str());
    EXPECT_EQ(result, static_cast<std::streambuf::int_type>('f'));
}

TEST_F(IndenterTest_4, PutEOFCharacterReturnsEOF_4) {
    std::ostringstream oss;
    auto result = indenter(*oss.rdbuf(), std::char_traits<char>::eof());
    EXPECT_TRUE(std::char_traits<char>::eq_int_type(result, std::char_traits<char>::eof()));
}