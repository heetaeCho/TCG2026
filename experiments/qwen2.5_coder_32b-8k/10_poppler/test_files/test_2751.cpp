#include <gtest/gtest.h>

#include "poppler/Object.h"

#include "poppler/Array.h"



class ObjectTest_2751 : public ::testing::Test {

protected:

    void SetUp() override {

        xref = new XRef();

        array = new Array(xref);

    }



    void TearDown() override {

        delete array;

        delete xref;

    }



    XRef* xref;

    Array* array;

};



TEST_F(ObjectTest_2751, ConstructorFromArray_2751) {

    Object obj(array);

    EXPECT_TRUE(obj.isArray());

}



TEST_F(ObjectTest_2751, TypeCheckForArray_2751) {

    Object obj(array);

    EXPECT_EQ(obj.getType(), objArray);

}



TEST_F(ObjectTest_2751, ArrayGetLengthInitiallyZero_2751) {

    Object obj(array);

    EXPECT_EQ(obj.arrayGetLength(), 0);

}



TEST_F(ObjectTest_2751, ArrayAddIncreasesCount_2751) {

    Object obj(array);

    Object element(42);

    obj.arrayAdd(std::move(element));

    EXPECT_EQ(obj.arrayGetLength(), 1);

}



TEST_F(ObjectTest_2751, ArrayRemoveDecreasesCount_2751) {

    Object obj(array);

    Object element(42);

    obj.arrayAdd(std::move(element));

    obj.arrayRemove(0);

    EXPECT_EQ(obj.arrayGetLength(), 0);

}



TEST_F(ObjectTest_2751, ArrayGetElement_2751) {

    Object obj(array);

    Object element(42);

    obj.arrayAdd(std::move(element));

    Object retrieved = obj.arrayGet(0, 0);

    EXPECT_TRUE(retrieved.isInt());

    EXPECT_EQ(retrieved.getInt(), 42);

}



TEST_F(ObjectTest_2751, ArrayElementNotFound_2751) {

    Object obj(array);

    Object element(42);

    obj.arrayAdd(std::move(element));

    Object retrieved = obj.arrayGetNF(-1);

    EXPECT_TRUE(retrieved.isNull());

}



TEST_F(ObjectTest_2751, InvalidIndexAccess_2751) {

    Object obj(array);

    EXPECT_THROW(obj.arrayGet(0, 0), std::runtime_error); // Assuming invalid access throws an exception

}
