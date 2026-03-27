#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OptionalContent.h"

#include "TestProjects/poppler/poppler/Object.h"



class OCGsTest : public ::testing::Test {

protected:

    XRef* m_xref = nullptr;

    Object emptyObject;



    void SetUp() override {

        // Initialize any necessary setup before each test

    }



    void TearDown() override {

        // Clean up after each test if necessary

    }

};



TEST_F(OCGsTest_940, GetOrderArray_ReturnsNullptrWhenOrderIsNotAnArray_940) {

    OCGs ocgs(emptyObject, m_xref);

    EXPECT_EQ(nullptr, ocgs.getOrderArray());

}



TEST_F(OCGsTest_940, GetOrderArray_ReturnsNullptrWhenOrderArrayIsEmpty_940) {

    Object emptyArray(Object::objArray, Array{});

    OCGs ocgs(emptyArray, m_xref);

    EXPECT_EQ(nullptr, ocgs.getOrderArray());

}



TEST_F(OCGsTest_940, GetOrderArray_ReturnsValidPointerWhenOrderIsNonEmptyArray_940) {

    Object nonEmptyArray(Object::objArray, Array{Object(), Object()});

    OCGs ocgs(nonEmptyArray, m_xref);

    EXPECT_NE(nullptr, ocgs.getOrderArray());

}



TEST_F(OCGsTest_940, GetOrderArray_ReturnsValidPointerWhenOrderIsNonEmptyArrayWithElements_940) {

    Object nonEmptyArray(Object::objArray, Array{Object(), Object()});

    OCGs ocgs(nonEmptyArray, m_xref);

    EXPECT_NE(nullptr, ocgs.getOrderArray());

    EXPECT_EQ(2, ocgs.getOrderArray()->getLength());

}
