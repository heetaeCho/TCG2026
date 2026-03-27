#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_string_manip.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



namespace Catch {



class SplitStringRefTest : public ::testing::Test {

protected:

    std::vector<StringRef> splitStringRef(const StringRef& str, char delimiter) {

        return Catch::splitStringRef(str, delimiter);

    }

};



TEST_F(SplitStringRefTest_595, EmptyStringReturnsEmptyVector_595) {

    StringRef emptyStr("");

    auto result = splitStringRef(emptyStr, ',');

    EXPECT_TRUE(result.empty());

}



TEST_F(SplitStringRefTest_595, SingleCharacterNoDelimiterReturnsSingleElement_595) {

    StringRef singleChar("a");

    auto result = splitStringRef(singleChar, ',');

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(static_cast<std::string>(result[0]), "a");

}



TEST_F(SplitStringRefTest_595, SingleDelimiterReturnsEmptyVector_595) {

    StringRef singleDelim(",");

    auto result = splitStringRef(singleDelim, ',');

    EXPECT_TRUE(result.empty());

}



TEST_F(SplitStringRefTest_595, MultipleCharactersNoDelimiterReturnsSingleElement_595) {

    StringRef multiChars("abc");

    auto result = splitStringRef(multiChars, ',');

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(static_cast<std::string>(result[0]), "abc");

}



TEST_F(SplitStringRefTest_595, DelimiterAtStartReturnsEmptyFirstElement_595) {

    StringRef startDelim(",abc");

    auto result = splitStringRef(startDelim, ',');

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(static_cast<std::string>(result[0]), "abc");

}



TEST_F(SplitStringRefTest_595, DelimiterAtEndReturnsEmptyLastElement_595) {

    StringRef endDelim("abc,");

    auto result = splitStringRef(endDelim, ',');

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(static_cast<std::string>(result[0]), "abc");

}



TEST_F(SplitStringRefTest_595, DelimiterInMiddleReturnsTwoElements_595) {

    StringRef midDelim("ab,c");

    auto result = splitStringRef(midDelim, ',');

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(static_cast<std::string>(result[0]), "ab");

    EXPECT_EQ(static_cast<std::string>(result[1]), "c");

}



TEST_F(SplitStringRefTest_595, MultipleDelimitersReturnsMultipleElements_595) {

    StringRef multiDels("a,b,c,d,e");

    auto result = splitStringRef(multiDels, ',');

    ASSERT_EQ(result.size(), 5);

    EXPECT_EQ(static_cast<std::string>(result[0]), "a");

    EXPECT_EQ(static_cast<std::string>(result[1]), "b");

    EXPECT_EQ(static_cast<std::string>(result[2]), "c");

    EXPECT_EQ(static_cast<std::string>(result[3]), "d");

    EXPECT_EQ(static_cast<std::string>(result[4]), "e");

}



TEST_F(SplitStringRefTest_595, ConsecutiveDelimitersSkipped_595) {

    StringRef consecutiveDels("a,,b,c,");

    auto result = splitStringRef(consecutiveDels, ',');

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(static_cast<std::string>(result[0]), "a");

    EXPECT_EQ(static_cast<std::string>(result[1]), "b");

    EXPECT_EQ(static_cast<std::string>(result[2]), "c");

}



TEST_F(SplitStringRefTest_595, AllDelimitersReturnsEmptyVector_595) {

    StringRef allDels(",,,,,");

    auto result = splitStringRef(allDels, ',');

    EXPECT_TRUE(result.empty());

}



}  // namespace Catch
