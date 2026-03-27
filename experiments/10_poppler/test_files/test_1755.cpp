#include <gtest/gtest.h>

#include "Object.h"



using namespace poppler;



// Test fixture for Object tests

class ObjectTest_1755 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed, but in this case no setup is required.

    }

};



// Test normal operation with valid names

TEST_F(ObjectTest_1755, IsWritingModeName_ValidNames_1755) {

    Object objLrTb("LrTb");

    Object objRlTb("RlTb");

    Object objTbRl("TbRl");



    EXPECT_TRUE(isWritingModeName(&objLrTb));

    EXPECT_TRUE(isWritingModeName(&objRlTb));

    EXPECT_TRUE(isWritingModeName(&objTbRl));

}



// Test boundary conditions with empty string

TEST_F(ObjectTest_1755, IsWritingModeName_EmptyString_1755) {

    Object objEmpty("");



    EXPECT_FALSE(isWritingModeName(&objEmpty));

}



// Test exceptional cases with invalid names

TEST_F(ObjectTest_1755, IsWritingModeName_InvalidNames_1755) {

    Object objLtRb("LtRb");

    Object objTbLR("TbLR");

    Object objRandom("Random");



    EXPECT_FALSE(isWritingModeName(&objLtRb));

    EXPECT_FALSE(isWritingModeName(&objTbLR));

    EXPECT_FALSE(isWritingModeName(&objRandom));

}



// Test with nullptr

TEST_F(ObjectTest_1755, IsWritingModeName_Nullptr_1755) {

    Object* objNull = nullptr;



    EXPECT_FALSE(isWritingModeName(objNull));

}
