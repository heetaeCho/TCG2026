#include <gtest/gtest.h>

#include "TestProjects/poppler/goo/GooString.h"



class GooStringTest_21 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(GooStringTest_21, DefaultConstructorCreatesEmptyString_21) {

    GooString gooStr;

    EXPECT_TRUE(gooStr.toStr().empty());

}



TEST_F(GooStringTest_21, ConstructorWithCStringInitializesCorrectly_21) {

    const char* testString = "Hello";

    GooString gooStr(testString);

    EXPECT_EQ(gooStr.toStr(), "Hello");

}



TEST_F(GooStringTest_21, ConstructorWithStringViewInitializesCorrectly_21) {

    std::string_view testString = "World";

    GooString gooStr(testString);

    EXPECT_EQ(gooStr.toStr(), "World");

}



TEST_F(GooStringTest_21, ConstructorWithStdStringInitializesCorrectly_21) {

    std::string testString = "Poppler";

    GooString gooStr(testString);

    EXPECT_EQ(gooStr.toStr(), "Poppler");

}



TEST_F(GooStringTest_21, MoveConstructorTransfersOwnership_21) {

    GooString original("MoveMe");

    GooString moved(std::move(original));

    EXPECT_EQ(moved.toStr(), "MoveMe");

    EXPECT_TRUE(original.toStr().empty());

}



TEST_F(GooStringTest_21, ToNonConstStrReturnsSameReference_21) {

    GooString gooStr("Mutable");

    std::string& nonConstRef = gooStr.toNonConstStr();

    EXPECT_EQ(&nonConstRef, &gooStr.toStr());

}



TEST_F(GooStringTest_21, CopyMethodCreatesDeepCopy_21) {

    GooString original("CopyMe");

    auto copy = original.copy();

    EXPECT_EQ(copy->toStr(), "CopyMe");

    EXPECT_NE(&copy->toNonConstStr(), &original.toNonConstStr());

}



TEST_F(GooStringTest_21, GetCharReturnsCorrectCharacter_21) {

    GooString gooStr("Indexing");

    EXPECT_EQ(gooStr.getChar(0), 'I');

    EXPECT_EQ(gooStr.getChar(3), 'x');

}



TEST_F(GooStringTest_21, SetCharModifiesCharacterAtPosition_21) {

    GooString gooStr("Modify");

    gooStr.setChar(0, 'M');

    gooStr.setChar(4, 'f');

    EXPECT_EQ(gooStr.toStr(), "Modyfy");

}



TEST_F(GooStringTest_21, GetCharWithInvalidIndexThrowsException_21) {

    GooString gooStr("Bounds");

    EXPECT_THROW(gooStr.getChar(6), std::out_of_range);

}



TEST_F(GooStringTest_21, SetCharWithInvalidIndexThrowsException_21) {

    GooString gooStr("Bounds");

    EXPECT_THROW(gooStr.setChar(6, 'X'), std::out_of_range);

}
