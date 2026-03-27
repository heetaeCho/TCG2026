#include <gtest/gtest.h>

#include "poppler/OptionalContent.h"

#include "poppler/Object.h"



class OCGsTest_941 : public ::testing::Test {

protected:

    XRef* m_xref;

    Object emptyObject;



    void SetUp() override {

        m_xref = nullptr; // Assuming no need to mock XRef for this test

        emptyObject = Object();

    }



    void TearDown() override {

        // Clean up if necessary

    }

};



TEST_F(OCGsTest_941, GetRBGroupsArray_ReturnsNullForEmptyArray_941) {

    OCGs ocgs(emptyObject, m_xref);

    EXPECT_EQ(ocgs.getRBGroupsArray(), nullptr);

}



TEST_F(OCGsTest_941, GetRBGroupsArray_ReturnsValidPointerForNonEmptyArray_941) {

    Object arrayObject(new Array());

    OCGs ocgs(arrayObject, m_xref);

    EXPECT_NE(ocgs.getRBGroupsArray(), nullptr);

}



TEST_F(OCGsTest_941, GetRBGroupsArray_LengthZeroForEmptyArray_941) {

    OCGs ocgs(emptyObject, m_xref);

    const Array* result = ocgs.getRBGroupsArray();

    EXPECT_EQ(result ? result->getLength() : 0, 0);

}



TEST_F(OCGsTest_941, GetRBGroupsArray_LengthNonZeroForNonEmptyArray_941) {

    Object arrayObject(new Array());

    arrayObject.arrayAdd(Object(1));

    OCGs ocgs(arrayObject, m_xref);

    const Array* result = ocgs.getRBGroupsArray();

    EXPECT_EQ(result ? result->getLength() : 0, 1);

}
