#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/ninja/src/string_piece.h"

#include "./TestProjects/ninja/src/hash_map.h"



using namespace std;



TEST(StringPieceTest_73, DefaultConstructorCreatesEmptyString_73) {

    StringPiece sp;

    EXPECT_EQ(sp.str_, nullptr);

    EXPECT_EQ(sp.len_, 0);

}



TEST(StringPieceTest_73, ConstructorFromStdStringInitializesCorrectly_73) {

    std::string test_str = "Hello, World!";

    StringPiece sp(test_str);

    EXPECT_EQ(sp.str_, test_str.data());

    EXPECT_EQ(sp.len_, test_str.size());

}



TEST(StringPieceTest_73, ConstructorFromCStringInitializesCorrectly_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.str_, test_cstr);

    EXPECT_EQ(sp.len_, strlen(test_cstr));

}



TEST(StringPieceTest_73, ConstructorFromCStringAndLengthInitializesCorrectly_73) {

    const char* test_cstr = "Hello, World!";

    size_t len = 5;

    StringPiece sp(test_cstr, len);

    EXPECT_EQ(sp.str_, test_cstr);

    EXPECT_EQ(sp.len_, len);

}



TEST(StringPieceTest_73, OperatorEqualsReturnsTrueForEqualStringPieces_73) {

    std::string test_str1 = "Hello";

    std::string test_str2 = "Hello";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_TRUE(sp1 == sp2);

}



TEST(StringPieceTest_73, OperatorEqualsReturnsFalseForDifferentStringPieces_73) {

    std::string test_str1 = "Hello";

    std::string test_str2 = "World";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_FALSE(sp1 == sp2);

}



TEST(StringPieceTest_73, OperatorNotEqualsReturnsTrueForDifferentStringPieces_73) {

    std::string test_str1 = "Hello";

    std::string test_str2 = "World";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_TRUE(sp1 != sp2);

}



TEST(StringPieceTest_73, OperatorNotEqualsReturnsFalseForEqualStringPieces_73) {

    std::string test_str1 = "Hello";

    std::string test_str2 = "Hello";

    StringPiece sp1(test_str1);

    StringPiece sp2(test_str2);

    EXPECT_FALSE(sp1 != sp2);

}



TEST(StringPieceTest_73, AsStringReturnsCorrectStdString_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.AsString(), std::string(test_cstr));

}



TEST(StringPieceTest_73, BeginReturnsPointerToFirstCharacter_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.begin(), test_cstr);

}



TEST(StringPieceTest_73, EndReturnsPointerToEndOfData_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.end(), test_cstr + strlen(test_cstr));

}



TEST(StringPieceTest_73, OperatorIndexAccessesCharactersCorrectly_73) {

    std::string test_str = "Hello, World!";

    StringPiece sp(test_str);

    for (size_t i = 0; i < test_str.size(); ++i) {

        EXPECT_EQ(sp[i], test_str[i]);

    }

}



TEST(StringPieceTest_73, SizeReturnsCorrectLength_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_EQ(sp.size(), strlen(test_cstr));

}



TEST(StringPieceTest_73, EmptyReturnsTrueForEmptyStringPiece_73) {

    StringPiece sp;

    EXPECT_TRUE(sp.empty());

}



TEST(StringPieceTest_73, EmptyReturnsFalseForNonEmptyStringPiece_73) {

    const char* test_cstr = "Hello, World!";

    StringPiece sp(test_cstr);

    EXPECT_FALSE(sp.empty());

}
