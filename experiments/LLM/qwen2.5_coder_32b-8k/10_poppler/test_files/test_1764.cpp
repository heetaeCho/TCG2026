#include <gtest/gtest.h>

#include "Object.h"



using namespace poppler;



// Test fixture for Object class tests

class ObjectTest_1764 : public ::testing::Test {

protected:

    std::unique_ptr<Object> objBefore;

    std::unique_ptr<Object> objAfter;

    std::unique_ptr<Object> objWarichu;

    std::unique_ptr<Object> objInline;

    std::unique_ptr<Object> objOther;



    void SetUp() override {

        objBefore = std::make_unique<Object>("Before");

        objAfter = std::make_unique<Object>("After");

        objWarichu = std::make_unique<Object>("Warichu");

        objInline = std::make_unique<Object>("Inline");

        objOther = std::make_unique<Object>("Other");

    }

};



// Test if isRubyPositionName returns true for "Before" with TEST_ID 1764

TEST_F(ObjectTest_1764, IsRubyPositionName_Before_ReturnsTrue_1764) {

    EXPECT_TRUE(isRubyPositionName(objBefore.get()));

}



// Test if isRubyPositionName returns true for "After" with TEST_ID 1764

TEST_F(ObjectTest_1764, IsRubyPositionName_After_ReturnsTrue_1764) {

    EXPECT_TRUE(isRubyPositionName(objAfter.get()));

}



// Test if isRubyPositionName returns true for "Warichu" with TEST_ID 1764

TEST_F(ObjectTest_1764, IsRubyPositionName_Warichu_ReturnsTrue_1764) {

    EXPECT_TRUE(isRubyPositionName(objWarichu.get()));

}



// Test if isRubyPositionName returns true for "Inline" with TEST_ID 1764

TEST_F(ObjectTest_1764, IsRubyPositionName_Inline_ReturnsTrue_1764) {

    EXPECT_TRUE(isRubyPositionName(objInline.get()));

}



// Test if isRubyPositionName returns false for an unrelated name with TEST_ID 1764

TEST_F(ObjectTest_1764, IsRubyPositionName_Other_ReturnsFalse_1764) {

    EXPECT_FALSE(isRubyPositionName(objOther.get()));

}
