#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Test fixture for Value class tests

class ValueTest_788 : public ::testing::Test {

protected:

    // Create an instance of Value using the create static method

    UniquePtr value;

    ValueTest_788() : value(Value::create(TypeId::unsignedLong)) {}

};



// Test normal operation of toString method

TEST_F(ValueTest_788, ToStringNormalOperation_788) {

    EXPECT_EQ(value->toString(), "");

}



// Test boundary condition with empty data area

TEST_F(ValueTest_788, ToStringEmptyDataArea_788) {

    value->setDataArea(nullptr, 0);

    EXPECT_EQ(value->toString(), "");

}



// Test exceptional case where toString fails to write

TEST_F(ValueTest_788, ToStringFailure_788) {

    // Simulate a failure condition by setting ok_ to false

    value->ok_ = false;

    EXPECT_EQ(value->toString(), "");

}



// Test normal operation of count method (assuming it returns 0 for empty data)

TEST_F(ValueTest_788, CountNormalOperation_788) {

    EXPECT_EQ(value->count(), 0);

}



// Test boundary condition with empty data area

TEST_F(ValueTest_788, CountEmptyDataArea_788) {

    value->setDataArea(nullptr, 0);

    EXPECT_EQ(value->count(), 0);

}



// Test normal operation of size method (assuming it returns 0 for empty data)

TEST_F(ValueTest_788, SizeNormalOperation_788) {

    EXPECT_EQ(value->size(), 0);

}



// Test boundary condition with empty data area

TEST_F(ValueTest_788, SizeEmptyDataArea_788) {

    value->setDataArea(nullptr, 0);

    EXPECT_EQ(value->size(), 0);

}



// Test normal operation of sizeDataArea method (assuming it returns 0 for empty data)

TEST_F(ValueTest_788, SizeDataAreaNormalOperation_788) {

    EXPECT_EQ(value->sizeDataArea(), 0);

}



// Test boundary condition with empty data area

TEST_F(ValueTest_788, SizeDataAreaEmptyDataArea_788) {

    value->setDataArea(nullptr, 0);

    EXPECT_EQ(value->sizeDataArea(), 0);

}
