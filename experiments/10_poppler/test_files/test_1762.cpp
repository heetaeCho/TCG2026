#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"



using namespace testing;



class ObjectTest_1762 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(ObjectTest_1762, IsTextDecorationName_None_1762) {

    Object obj("None");

    EXPECT_TRUE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_Underline_1762) {

    Object obj("Underline");

    EXPECT_TRUE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_Overline_1762) {

    Object obj("Overline");

    EXPECT_TRUE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_LineThrough_1762) {

    Object obj("LineThrough");

    EXPECT_TRUE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_OtherString_1762) {

    Object obj("OtherString");

    EXPECT_FALSE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_EmptyString_1762) {

    Object obj("");

    EXPECT_FALSE(isTextDecorationName(&obj));

}



TEST_F(ObjectTest_1762, IsTextDecorationName_NotAName_1762) {

    Object obj(42); // Assuming 42 is an integer and not a name

    EXPECT_FALSE(isTextDecorationName(&obj));

}
