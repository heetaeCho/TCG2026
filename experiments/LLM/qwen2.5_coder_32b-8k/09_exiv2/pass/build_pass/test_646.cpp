#include <gtest/gtest.h>

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcKeyTest_646 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(IptcKeyTest_646, ConstructorWithTagAndRecord_646) {

    IptcKey key(123, 456);

    EXPECT_EQ(key.tag(), 123u);

}



TEST_F(IptcKeyTest_646, ConstructorWithKeyString_646) {

    IptcKey key("testKey");

    EXPECT_EQ(key.key(), "testKey");

}



TEST_F(IptcKeyTest_646, TagMethodReturnsCorrectValue_646) {

    IptcKey key(123, 456);

    EXPECT_EQ(key.tag(), 123u);

}



TEST_F(IptcKeyTest_646, KeyMethodReturnsCorrectValue_646) {

    IptcKey key("testKey");

    EXPECT_EQ(key.key(), "testKey");

}



// Assuming tag() and record() are the only observable methods with boundary conditions

TEST_F(IptcKeyTest_646, BoundaryConditionTagZero_646) {

    IptcKey key(0, 456);

    EXPECT_EQ(key.tag(), 0u);

}



TEST_F(IptcKeyTest_646, BoundaryConditionRecordZero_646) {

    IptcKey key(123, 0);

    EXPECT_EQ(key.record(), 0u);

}



// Assuming no exceptional or error cases are observable through the provided interface



// Assuming no external interactions to verify
