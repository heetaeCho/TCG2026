#include <gtest/gtest.h>

#include "JsonBox/Value.h"



using namespace JsonBox;



class ValueTest_55 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_55, SetObject_WhenTypeIsOBJECT_ReplacesExistingObject_55) {

    Object initialObject = {{"key1", Value("value1")}};

    value.setObject(initialObject);

    Object newObject = {{"key2", Value("value2")}};

    value.setObject(newObject);



    EXPECT_EQ(value.getObject(), newObject);

}



TEST_F(ValueTest_55, SetObject_WhenTypeIsNotOBJECT_CreatesNewObject_55) {

    value.setInteger(10); // Change type to INTEGER

    Object newObject = {{"key", Value("value")}};

    value.setObject(newObject);



    EXPECT_EQ(value.getObject(), newObject);

}



TEST_F(ValueTest_55, SetObject_VerifiesObjectTypeAfterSet_55) {

    Object newObject = {{"key", Value("value")}};

    value.setObject(newObject);



    EXPECT_TRUE(value.isObject());

}



TEST_F(ValueTest_55, SetObject_EmptyObject_SetsEmptyObject_55) {

    Object emptyObject;

    value.setObject(emptyObject);



    EXPECT_EQ(value.getObject(), emptyObject);

}



TEST_F(ValueTest_55, GetObject_AfterSetObject_ReturnsSameObject_55) {

    Object newObject = {{"key", Value("value")}};

    value.setObject(newObject);



    EXPECT_EQ(value.getObject(), newObject);

}
