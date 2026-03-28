#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_101, GetArray_ReturnsNullptrWhenNotArrayType_101) {

    Object obj;

    ASSERT_EQ(obj.getArray(), nullptr);

}



TEST_F(ObjectTest_101, GetArray_ReturnsValidPointerWhenArrayType_101) {

    Array* array = new Array();

    Object obj(array);

    ASSERT_NE(obj.getArray(), nullptr);

    delete array;  // Cleanup

}



TEST_F(ObjectTest_101, IsArray_ReturnsFalseForNonArrayType_101) {

    Object obj;

    EXPECT_FALSE(obj.isArray());

}



TEST_F(ObjectTest_101, IsArray_ReturnsTrueForArrayType_101) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;  // Cleanup

}



TEST_F(ObjectTest_101, GetType_ReturnsCorrectTypeForArray_101) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_EQ(obj.getType(), objArray);

    delete array;  // Cleanup

}



TEST_F(ObjectTest_101, ConstructorFromArray_SetsArrayType_101) {

    Array* array = new Array();

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

    delete array;  // Cleanup

}
