// StructElement_isTextDecorationName_tests_1762.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE: isTextDecorationName() is a file-local (static) function in StructElement.cc.
// To test it without re-implementing/inferencing logic, we include the .cc so the
// function is available in this translation unit.
#include "StructElement.cc"

class StructElementIsTextDecorationNameTest_1762 : public ::testing::Test {};

TEST_F(StructElementIsTextDecorationNameTest_1762, ReturnsTrueForKnownDecorationNames_1762)
{
    Object none(objName, "None");
    Object underline(objName, "Underline");
    Object overline(objName, "Overline");
    Object lineThrough(objName, "LineThrough");

    EXPECT_TRUE(isTextDecorationName(&none));
    EXPECT_TRUE(isTextDecorationName(&underline));
    EXPECT_TRUE(isTextDecorationName(&overline));
    EXPECT_TRUE(isTextDecorationName(&lineThrough));
}

TEST_F(StructElementIsTextDecorationNameTest_1762, ReturnsFalseForOtherNameValues_1762)
{
    Object empty(objName, "");
    Object lowerUnderline(objName, "underline");
    Object unknown(objName, "StrikeThrough");
    Object whitespace(objName, " None");
    Object similar(objName, "LineThroughs");

    EXPECT_FALSE(isTextDecorationName(&empty));
    EXPECT_FALSE(isTextDecorationName(&lowerUnderline));
    EXPECT_FALSE(isTextDecorationName(&unknown));
    EXPECT_FALSE(isTextDecorationName(&whitespace));
    EXPECT_FALSE(isTextDecorationName(&similar));
}

TEST_F(StructElementIsTextDecorationNameTest_1762, ReturnsFalseForNonNameObjects_1762)
{
    Object nullObj = Object::null();
    Object eofObj = Object::eof();
    Object errObj = Object::error();

    Object boolObj(true);
    Object intObj(123);
    Object realObj(3.25);

    EXPECT_FALSE(isTextDecorationName(&nullObj));
    EXPECT_FALSE(isTextDecorationName(&eofObj));
    EXPECT_FALSE(isTextDecorationName(&errObj));

    EXPECT_FALSE(isTextDecorationName(&boolObj));
    EXPECT_FALSE(isTextDecorationName(&intObj));
    EXPECT_FALSE(isTextDecorationName(&realObj));
}