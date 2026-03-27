#include <gtest/gtest.h>

#include "Object.h"



TEST(isPlacementNameTest_1754, Block_ReturnsTrue_1754) {

    Object blockObj("Block");

    EXPECT_TRUE(isPlacementName(&blockObj));

}



TEST(isPlacementNameTest_1754, Inline_ReturnsTrue_1754) {

    Object inlineObj("Inline");

    EXPECT_TRUE(isPlacementName(&inlineObj));

}



TEST(isPlacementNameTest_1754, Before_ReturnsTrue_1754) {

    Object beforeObj("Before");

    EXPECT_TRUE(isPlacementName(&beforeObj));

}



TEST(isPlacementNameTest_1754, Start_ReturnsTrue_1754) {

    Object startObj("Start");

    EXPECT_TRUE(isPlacementName(&startObj));

}



TEST(isPlacementNameTest_1754, End_ReturnsTrue_1754) {

    Object endObj("End");

    EXPECT_TRUE(isPlacementName(&endObj));

}



TEST(isPlacementNameTest_1754, Other_ReturnsFalse_1754) {

    Object otherObj("Other");

    EXPECT_FALSE(isPlacementName(&otherObj));

}



TEST(isPlacementNameTest_1754, EmptyString_ReturnsFalse_1754) {

    Object emptyObj("");

    EXPECT_FALSE(isPlacementName(&emptyObj));

}



TEST(isPlacementNameTest_1754, NullObject_ReturnsFalse_1754) {

    Object nullObj = Object::null();

    EXPECT_FALSE(isPlacementName(&nullObj));

}
