#include <gtest/gtest.h>

#include "Object.h"



// Mock class for Object if needed (not required in this case as we don't have any external collaborators)

class MockObject : public Object {

public:

    using Object::Object;

};



// Test suite for the isNatural function

class IsNaturalTest_1771 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(IsNaturalTest_1771, PositiveInteger_ReturnsTrue_1771) {

    Object obj(1);

    EXPECT_TRUE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, Zero_ReturnsFalse_1771) {

    Object obj(0);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, NegativeInteger_ReturnsFalse_1771) {

    Object obj(-1);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, PositiveInt64_ReturnsTrue_1771) {

    Object obj(1LL);

    EXPECT_TRUE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, ZeroInt64_ReturnsFalse_1771) {

    Object obj(0LL);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, NegativeInt64_ReturnsFalse_1771) {

    Object obj(-1LL);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, NonIntegerType_ReturnsFalse_1771) {

    Object obj("string");

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, RealNumber_ReturnsFalse_1771) {

    Object obj(1.0);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, NegativeRealNumber_ReturnsFalse_1771) {

    Object obj(-1.0);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, BooleanTrue_ReturnsFalse_1771) {

    Object obj(true);

    EXPECT_FALSE(isNatural(&obj));

}



TEST_F(IsNaturalTest_1771, BooleanFalse_ReturnsFalse_1771) {

    Object obj(false);

    EXPECT_FALSE(isNatural(&obj));

}
