#include <gtest/gtest.h>

#include "Array.h"

#include "GooString.h"



class ArrayTest_112 : public ::testing::Test {

protected:

    XRef* xref;

    Array* array;



    void SetUp() override {

        xref = new XRef();

        array = new Array(xref);

    }



    void TearDown() override {

        delete array;

        delete xref;

    }

};



TEST_F(ArrayTest_112, GetLengthInitiallyZero_112) {

    EXPECT_EQ(array->getLength(), 0);

}



TEST_F(ArrayTest_112, AddIncreasesCount_112) {

    Object obj;

    array->add(std::move(obj));

    EXPECT_EQ(array->getLength(), 1);

}



TEST_F(ArrayTest_112, RemoveDecreasesCount_112) {

    Object obj;

    array->add(std::move(obj));

    array->remove(0);

    EXPECT_EQ(array->getLength(), 0);

}



TEST_F(ArrayTest_112, GetElementAfterAdd_112) {

    Object obj;

    array->add(std::move(obj));

    const Object& retrievedObj = array->getNF(0);

    // Assuming operator== is implemented for Object

    EXPECT_EQ(retrievedObj, obj);

}



TEST_F(ArrayTest_112, GetElementBoundaryCondition_112) {

    Object obj;

    array->add(std::move(obj));

    EXPECT_THROW(array->getNF(1), std::out_of_range); // Assuming getNF throws out_of_range for invalid index

}



TEST_F(ArrayTest_112, RemoveBoundaryCondition_112) {

    EXPECT_THROW(array->remove(0), std::out_of_range); // Assuming remove throws out_of_range for invalid index

}
