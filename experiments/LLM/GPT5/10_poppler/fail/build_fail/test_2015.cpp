#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Object.h"

// Mock class for Object to simulate required behaviors for testing
class MockObject : public Object {
public:
    MOCK_CONST_METHOD0(isName, bool());
    MOCK_CONST_METHOD1(isName, bool(std::string_view));
};

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Square_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Square")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingSquare);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Circle_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Circle")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingCircle);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Diamond_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Diamond")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingDiamond);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_OpenArrow_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("OpenArrow")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingOpenArrow);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_ClosedArrow_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("ClosedArrow")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Butt_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Butt")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingButt);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_ROpenArrow_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("ROpenArrow")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingROpenArrow);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_RClosedArrow_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("RClosedArrow")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingRClosedArrow);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Slash_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Slash")).WillOnce(testing::Return(true));
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingSlash);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_None_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("None")).WillOnce(testing::Return(false));  // Default case
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingNone);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Error_Invalid_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("Invalid")).WillOnce(testing::Return(false));  // Edge case for an invalid value
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingNone);
}

TEST_F(AnnotLineEndingStyleTest_2015, parseAnnotLineEndingStyle_Empty_2015) {
    MockObject name;
    EXPECT_CALL(name, isName("")).WillOnce(testing::Return(false));  // Edge case for an empty string
    EXPECT_EQ(parseAnnotLineEndingStyle(name), annotLineEndingNone);
}