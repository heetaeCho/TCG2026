#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooString.h"

#include <string>



class GooStringTest_20 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(GooStringTest_20, DefaultConstructor_20) {

    GooString str;

    EXPECT_EQ(str.toStr(), "");

}



TEST_F(GooStringTest_20, CStyleStringConstructor_20) {

    GooString str("Hello");

    EXPECT_EQ(str.toStr(), "Hello");

}



TEST_F(GooStringTest_20, StdStringConstructor_20) {

    std::string stdStr = "World";

    GooString str(stdStr);

    EXPECT_EQ(str.toStr(), "World");

}



TEST_F(GooStringTest_20, CStyleStringWithLengthConstructor_20) {

    GooString str("Hello", 3);

    EXPECT_EQ(str.toStr(), "Hel");

}



TEST_F(GooStringTest_20, StringViewConstructor_20) {

    std::string_view sv = "Example";

    GooString str(sv);

    EXPECT_EQ(str.toStr(), "Example");

}



TEST_F(GooStringTest_20, SubstringConstructorFromGooStringPointer_20) {

    GooString original("OriginalString");

    GooString sub(&original, 8, 5);

    EXPECT_EQ(sub.toStr(), "String");

}



TEST_F(GooStringTest_20, SubstringConstructorFromString_20) {

    std::string str = "AnotherExample";

    GooString sub(str, 7, 6);

    EXPECT_EQ(sub.toStr(), "Example");

}



TEST_F(GooStringTest_20, CopyConstructorDeleted_20) {

    GooString original("CopyMe");

    // GooString copy(original); // This should not compile

    SUCCEED(); // If the above line is commented out, the test succeeds

}



TEST_F(GooStringTest_20, MoveConstructor_20) {

    GooString original("MoveMe");

    GooString moved(std::move(original));

    EXPECT_EQ(moved.toStr(), "MoveMe");

    // The state of original after move is undefined by std::string's contract

}



TEST_F(GooStringTest_20, GetCharBoundary_20) {

    GooString str("ABC");

    EXPECT_EQ(str.getChar(0), 'A');

    EXPECT_EQ(str.getChar(1), 'B');

    EXPECT_EQ(str.getChar(2), 'C');

}



TEST_F(GooStringTest_20, SetCharBoundary_20) {

    GooString str("XYZ");

    str.setChar(0, 'P');

    str.setChar(1, 'Q');

    str.setChar(2, 'R');

    EXPECT_EQ(str.toStr(), "PQR");

}



TEST_F(GooStringTest_20, FormatStaticFunction_20) {

    std::string formatted = GooString::format("Hello %s", "World");

    EXPECT_EQ(formatted, "Hello World");

}



TEST_F(GooStringTest_20, ToLowerCaseStaticFunction_20) {

    std::string lower = GooString::toLowerCase("HELLO");

    EXPECT_EQ(lower, "hello");



    std::string_view sv = "WORLD";

    std::string lowerView = GooString::toLowerCase(sv);

    EXPECT_EQ(lowerView, "world");

}



TEST_F(GooStringTest_20, AppendfFunction_20) {

    GooString str("Start");

    str.appendf(" %s", "End");

    EXPECT_EQ(str.toStr(), "Start End");

}
