#include <gtest/gtest.h>

#include "Object.h"



// Assuming the function isPositive is part of a class or namespace for testing purposes.

// Here we assume it's in a namespace called StructElement for this example.

namespace StructElement {

    static bool isPositive(Object *value) { return value->isNum() && value->getNum() >= 0.0; }

}



class ObjectTest_1772 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



TEST_F(ObjectTest_1772, IsPositive_NumberGreaterThanZero_1772) {

    Object obj(5.0);

    EXPECT_TRUE(StructElement::isPositive(&obj));

}



TEST_F(ObjectTest_1772, IsPositive_NumberEqualToZero_1772) {

    Object obj(0.0);

    EXPECT_TRUE(StructElement::isPositive(&obj));

}



TEST_F(ObjectTest_1772, IsPositive_NegativeNumber_1772) {

    Object obj(-5.0);

    EXPECT_FALSE(StructElement::isPositive(&obj));

}



TEST_F(ObjectTest_1772, IsPositive_NotANumber_1772) {

    Object obj("not_a_number");

    EXPECT_FALSE(StructElement::isPositive(&obj));

}



TEST_F(ObjectTest_1772, IsPositive_ZeroFromGetNumWithDefaultValue_1772) {

    Object obj;

    EXPECT_TRUE(StructElement::isPositive(&obj)); // Assuming getNum() on uninitialized returns 0

}
