#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>

// Test fixture for StringPiece tests
class StringPieceTest_6 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Constructor Tests ===

TEST_F(StringPieceTest_6, DefaultConstructor_6) {
    StringPiece sp;
    EXPECT_EQ(sp.str_, nullptr);
    EXPECT_EQ(sp.len_, 0u);
    EXPECT_EQ(sp.size(), 0u);
    EXPECT_TRUE(sp.empty());
}

TEST_F(StringPieceTest_6, ConstructFromStdString_6) {
    std::string str = "hello";
    StringPiece sp(str);
    EXPECT_EQ(sp.size(), 5u);
    EXPECT_EQ(sp.AsString(), "hello");
    EXPECT_FALSE(sp.empty());
}

TEST_F(StringPieceTest_6, ConstructFromCString_6) {
    const char* cstr = "world";
    StringPiece sp(cstr);
    EXPECT_EQ(sp.size(), 5u);
    EXPECT_EQ(sp.AsString(), "world");
}

TEST_F(StringPieceTest_6, ConstructFromCStringAndLength_6) {
    const char* cstr = "hello world";
    StringPiece sp(cstr, 5);
    EXPECT_EQ(sp.size(), 5u);
    EXPECT_EQ(sp.AsString(), "hello");
}

TEST_F(StringPieceTest_6, ConstructFromEmptyStdString_6) {
    std::string str = "";
    StringPiece sp(str);
    EXPECT_EQ(sp.size(), 0u);
    EXPECT_TRUE(sp.empty());
    EXPECT_EQ(sp.AsString(), "");
}

TEST_F(StringPieceTest_6, ConstructFromEmptyCString_6) {
    const char* cstr = "";
    StringPiece sp(cstr);
    EXPECT_EQ(sp.size(), 0u);
    EXPECT_TRUE(sp.empty());
}

// === Operator[] Tests ===

TEST_F(StringPieceTest_6, SubscriptOperatorFirstChar_6) {
    StringPiece sp("abcdef");
    EXPECT_EQ(sp[0], 'a');
}

TEST_F(StringPieceTest_6, SubscriptOperatorMiddleChar_6) {
    StringPiece sp("abcdef");
    EXPECT_EQ(sp[3], 'd');
}

TEST_F(StringPieceTest_6, SubscriptOperatorLastChar_6) {
    StringPiece sp("abcdef");
    EXPECT_EQ(sp[5], 'f');
}

TEST_F(StringPieceTest_6, SubscriptOperatorWithPartialLength_6) {
    const char* data = "hello world";
    StringPiece sp(data, 5);
    EXPECT_EQ(sp[0], 'h');
    EXPECT_EQ(sp[4], 'o');
}

// === Equality/Inequality Tests ===

TEST_F(StringPieceTest_6, EqualityOperatorSameStrings_6) {
    StringPiece sp1("hello");
    StringPiece sp2("hello");
    EXPECT_TRUE(sp1 == sp2);
    EXPECT_FALSE(sp1 != sp2);
}

TEST_F(StringPieceTest_6, EqualityOperatorDifferentStrings_6) {
    StringPiece sp1("hello");
    StringPiece sp2("world");
    EXPECT_FALSE(sp1 == sp2);
    EXPECT_TRUE(sp1 != sp2);
}

TEST_F(StringPieceTest_6, EqualityOperatorDifferentLengths_6) {
    StringPiece sp1("hello");
    StringPiece sp2("hell");
    EXPECT_FALSE(sp1 == sp2);
    EXPECT_TRUE(sp1 != sp2);
}

TEST_F(StringPieceTest_6, EqualityOperatorBothEmpty_6) {
    StringPiece sp1("");
    StringPiece sp2("");
    EXPECT_TRUE(sp1 == sp2);
    EXPECT_FALSE(sp1 != sp2);
}

TEST_F(StringPieceTest_6, EqualityOperatorFromDifferentSources_6) {
    std::string str = "test";
    const char* cstr = "test";
    StringPiece sp1(str);
    StringPiece sp2(cstr);
    EXPECT_TRUE(sp1 == sp2);
}

TEST_F(StringPieceTest_6, EqualityOperatorSubstring_6) {
    const char* data = "hello world";
    StringPiece sp1(data, 5);
    StringPiece sp2("hello");
    EXPECT_TRUE(sp1 == sp2);
}

// === AsString Tests ===

TEST_F(StringPieceTest_6, AsStringNormal_6) {
    StringPiece sp("testing");
    std::string result = sp.AsString();
    EXPECT_EQ(result, "testing");
}

TEST_F(StringPieceTest_6, AsStringPartialLength_6) {
    const char* data = "hello world";
    StringPiece sp(data, 5);
    EXPECT_EQ(sp.AsString(), "hello");
}

TEST_F(StringPieceTest_6, AsStringEmpty_6) {
    StringPiece sp("");
    EXPECT_EQ(sp.AsString(), "");
}

// === Begin/End Iterator Tests ===

TEST_F(StringPieceTest_6, BeginEndNormal_6) {
    const char* cstr = "hello";
    StringPiece sp(cstr);
    EXPECT_EQ(sp.begin(), cstr);
    EXPECT_EQ(sp.end(), cstr + 5);
}

TEST_F(StringPieceTest_6, BeginEndEmpty_6) {
    const char* cstr = "";
    StringPiece sp(cstr);
    EXPECT_EQ(sp.begin(), sp.end());
}

TEST_F(StringPieceTest_6, BeginEndIterationCorrect_6) {
    StringPiece sp("abc");
    std::string reconstructed;
    for (auto it = sp.begin(); it != sp.end(); ++it) {
        reconstructed += *it;
    }
    EXPECT_EQ(reconstructed, "abc");
}

TEST_F(StringPieceTest_6, IteratorDifferenceMatchesSize_6) {
    StringPiece sp("hello");
    EXPECT_EQ(static_cast<size_t>(sp.end() - sp.begin()), sp.size());
}

// === Size Tests ===

TEST_F(StringPieceTest_6, SizeNormal_6) {
    StringPiece sp("hello");
    EXPECT_EQ(sp.size(), 5u);
}

TEST_F(StringPieceTest_6, SizeEmpty_6) {
    StringPiece sp("");
    EXPECT_EQ(sp.size(), 0u);
}

TEST_F(StringPieceTest_6, SizeWithExplicitLength_6) {
    StringPiece sp("hello world", 3);
    EXPECT_EQ(sp.size(), 3u);
}

// === Empty Tests ===

TEST_F(StringPieceTest_6, EmptyOnEmptyString_6) {
    StringPiece sp("");
    EXPECT_TRUE(sp.empty());
}

TEST_F(StringPieceTest_6, EmptyOnNonEmptyString_6) {
    StringPiece sp("x");
    EXPECT_FALSE(sp.empty());
}

TEST_F(StringPieceTest_6, EmptyOnDefaultConstructed_6) {
    StringPiece sp;
    EXPECT_TRUE(sp.empty());
}

TEST_F(StringPieceTest_6, EmptyOnZeroLength_6) {
    StringPiece sp("hello", 0);
    EXPECT_TRUE(sp.empty());
}

// === Edge Cases ===

TEST_F(StringPieceTest_6, SingleCharacter_6) {
    StringPiece sp("x");
    EXPECT_EQ(sp.size(), 1u);
    EXPECT_EQ(sp[0], 'x');
    EXPECT_EQ(sp.AsString(), "x");
    EXPECT_FALSE(sp.empty());
}

TEST_F(StringPieceTest_6, StringWithNullInMiddle_6) {
    const char data[] = "he\0lo";
    StringPiece sp(data, 5);
    EXPECT_EQ(sp.size(), 5u);
    EXPECT_EQ(sp[2], '\0');
    EXPECT_EQ(sp[3], 'l');
}

TEST_F(StringPieceTest_6, LongString_6) {
    std::string long_str(10000, 'a');
    StringPiece sp(long_str);
    EXPECT_EQ(sp.size(), 10000u);
    EXPECT_EQ(sp[0], 'a');
    EXPECT_EQ(sp[9999], 'a');
    EXPECT_EQ(sp.AsString(), long_str);
}

TEST_F(StringPieceTest_6, InequalityPrefixVsFull_6) {
    StringPiece sp1("abc");
    StringPiece sp2("abcd");
    EXPECT_TRUE(sp1 != sp2);
    EXPECT_FALSE(sp1 == sp2);
}

TEST_F(StringPieceTest_6, EqualityWithSamePointerDifferentLength_6) {
    const char* data = "hello";
    StringPiece sp1(data, 3);
    StringPiece sp2(data, 5);
    EXPECT_FALSE(sp1 == sp2);
    EXPECT_TRUE(sp1 != sp2);
}

TEST_F(StringPieceTest_6, PublicMembersAccessible_6) {
    const char* cstr = "test";
    StringPiece sp(cstr);
    EXPECT_EQ(sp.str_, cstr);
    EXPECT_EQ(sp.len_, 4u);
}
