#include <gtest/gtest.h>

#include "poppler/StructElement.h"



class StructElementTest : public ::testing::Test {

protected:

    Object stmRef;

    StructElement* structElement;



    void SetUp() override {

        structElement = new StructElement();

    }



    void TearDown() override {

        delete structElement;

    }

};



TEST_F(StructElementTest_1697, HasStmRef_ReturnsFalse_WhenStmRefIsNotSet_1697) {

    EXPECT_FALSE(structElement->hasStmRef());

}



TEST_F(StructElementTest_1697, HasStmRef_ReturnsTrue_WhenStmRefIsSet_1697) {

    stmRef = Object(true); // Assuming setting a bool to true sets the ref

    structElement = new StructElement(stmRef);

    EXPECT_TRUE(structElement->hasStmRef());

}



TEST_F(StructElementTest_1697, HasStmRef_ReturnsFalse_WhenStmRefIsExplicitlySetToNonRef_1697) {

    stmRef = Object(false); // Assuming setting a bool to false does not set the ref

    structElement = new StructElement(stmRef);

    EXPECT_FALSE(structElement->hasStmRef());

}



TEST_F(StructElementTest_1697, HasStmRef_ReturnsFalse_WhenStmRefIsDefaultConstructed_1697) {

    EXPECT_FALSE(structElement->hasStmRef());

}
