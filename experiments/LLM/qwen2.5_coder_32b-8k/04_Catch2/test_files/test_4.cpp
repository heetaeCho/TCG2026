#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_stringref.hpp"

#include <string>



using namespace Catch;



// Test fixture for StringRef tests

class StringRefTest_4 : public ::testing::Test {

protected:

    StringRefTest_4() {}

};



TEST_F(StringRefTest_4, ConstructorWithCString_4) {

    const char* testString = "hello";

    StringRef ref(testString);

    EXPECT_EQ(ref.data(), testString);

    EXPECT_EQ(ref.size(), 5);

}



TEST_F(StringRefTest_4, ConstructorWithStringLiteral_4) {

    StringRef ref("world");

    EXPECT_STREQ(ref.data(), "world");

    EXPECT_EQ(ref.size(), 5);

}



TEST_F(StringRefTest_4, ConstructorWithStdString_4) {

    std::string testString = "example";

    StringRef ref(testString);

    EXPECT_EQ(ref.data(), testString.c_str());

    EXPECT_EQ(ref.size(), testString.size());

}



TEST_F(StringRefTest_4, DefaultConstructor_4) {

    StringRef ref;

    EXPECT_TRUE(ref.empty());

    EXPECT_EQ(ref.size(), 0);

}



TEST_F(StringRefTest_4, SubstrWithinBounds_4) {

    StringRef ref("abcdef");

    StringRef sub = ref.substr(2, 3);

    EXPECT_STREQ(sub.data(), "cde");

    EXPECT_EQ(sub.size(), 3);

}



TEST_F(StringRefTest_4, SubstrFromZeroIndex_4) {

    StringRef ref("abcdef");

    StringRef sub = ref.substr(0, 3);

    EXPECT_STREQ(sub.data(), "abc");

    EXPECT_EQ(sub.size(), 3);

}



TEST_F(StringRefTest_4, SubstrToFullLength_4) {

    StringRef ref("abcdef");

    StringRef sub = ref.substr(2, 4);

    EXPECT_STREQ(sub.data(), "cdef");

    EXPECT_EQ(sub.size(), 4);

}



TEST_F(StringRefTest_4, EmptySubstr_4) {

    StringRef ref("abcdef");

    StringRef sub = ref.substr(3, 0);

    EXPECT_TRUE(sub.empty());

    EXPECT_EQ(sub.size(), 0);

}



TEST_F(StringRefTest_4, SubstrBeyondEnd_4) {

    StringRef ref("abcdef");

    StringRef sub = ref.substr(3, 10);

    EXPECT_STREQ(sub.data(), "def");

    EXPECT_EQ(sub.size(), 3);

}



TEST_F(StringRefTest_4, CompareEqualStrings_4) {

    StringRef ref1("hello");

    StringRef ref2("hello");

    EXPECT_EQ(ref1.compare(ref2), 0);

}



TEST_F(StringRefTest_4, CompareShorterString_4) {

    StringRef ref1("hello");

    StringRef ref2("hell");

    EXPECT_GT(ref1.compare(ref2), 0);

}



TEST_F(StringRefTest_4, CompareLongerString_4) {

    StringRef ref1("hell");

    StringRef ref2("hello");

    EXPECT_LT(ref1.compare(ref2), 0);

}



TEST_F(StringRefTest_4, CompareDifferentStrings_4) {

    StringRef ref1("apple");

    StringRef ref2("banana");

    EXPECT_NE(ref1.compare(ref2), 0);

}



TEST_F(StringRefTest_4, EmptyStringCompare_4) {

    StringRef ref1;

    StringRef ref2;

    EXPECT_EQ(ref1.compare(ref2), 0);

}



TEST_F(StringRefTest_4, LessThanOperatorTrue_4) {

    StringRef ref1("apple");

    StringRef ref2("banana");

    EXPECT_TRUE(ref1 < ref2);

}



TEST_F(StringRefTest_4, LessThanOperatorFalse_4) {

    StringRef ref1("banana");

    StringRef ref2("apple");

    EXPECT_FALSE(ref1 < ref2);

}



TEST_F(StringRefTest_4, EqualOperatorTrue_4) {

    StringRef ref1("hello");

    StringRef ref2("hello");

    EXPECT_TRUE(ref1 == ref2);

}



TEST_F(StringRefTest_4, EqualOperatorFalse_4) {

    StringRef ref1("hello");

    StringRef ref2("world");

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(StringRefTest_4, NotEqualOperatorTrue_4) {

    StringRef ref1("hello");

    StringRef ref2("world");

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(StringRefTest_4, NotEqualOperatorFalse_4) {

    StringRef ref1("hello");

    StringRef ref2("hello");

    EXPECT_FALSE(ref1 != ref2);

}



TEST_F(StringRefTest_4, ElementAccessWithinBounds_4) {

    StringRef ref("hello");

    EXPECT_EQ(ref[0], 'h');

    EXPECT_EQ(ref[4], 'o');

}



TEST_F(StringRefTest_4, ElementAccessAtEnd_4) {

    StringRef ref("hello");

    EXPECT_EQ(ref[ref.size() - 1], 'o');

}



TEST_F(StringRefTest_4, EmptyStringElementAccess_4) {

    StringRef ref;

    // Accessing an empty string is undefined behavior, but we can check if it throws or returns a default value

    // For this test, we assume it does not throw and returns '\0'

    EXPECT_EQ(ref[0], '\0');

}



TEST_F(StringRefTest_4, BeginAndEndIterators_4) {

    StringRef ref("hello");

    auto begin = ref.begin();

    auto end = ref.end();

    EXPECT_EQ(*begin, 'h');

    EXPECT_EQ(end - begin, static_cast<std::ptrdiff_t>(ref.size()));

}



TEST_F(StringRefTest_4, EmptyStringBeginAndEndIterators_4) {

    StringRef ref;

    auto begin = ref.begin();

    auto end = ref.end();

    EXPECT_EQ(begin, end);

}
