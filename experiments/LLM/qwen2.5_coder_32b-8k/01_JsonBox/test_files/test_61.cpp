#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_61 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_61, SetNullChangesTypeToNull_61) {

    value.setNull();

    EXPECT_EQ(value.getType(), NULL_VALUE);

}



TEST_F(ValueTest_61, SetNullClearsData_61) {

    value.setString("test");

    value.setNull();

    EXPECT_TRUE(value.isNull());

    EXPECT_EQ(value.tryGetString("default"), "default");

}



TEST_F(ValueTest_61, InitialTypeIsNotNull_61) {

    EXPECT_NE(value.getType(), NULL_VALUE);

}
