#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class XmpValueTest_826 : public Test {

protected:

    XmpValue xmpValue_;

};



TEST_F(XmpValueTest_826, SetXmpArrayType_NormalOperation_826) {

    xmpValue_.setXmpArrayType(xaOrdered);

    EXPECT_EQ(xmpValue_.xmpArrayType(), xaOrdered);



    xmpValue_.setXmpArrayType(xaBag);

    EXPECT_EQ(xmpValue_.xmpArrayType(), xaBag);



    xmpValue_.setXmpArrayType(xaAlternate);

    EXPECT_EQ(xmpValue_.xmpArrayType(), xaAlternate);



    xmpValue_.setXmpArrayType(xaNone);

    EXPECT_EQ(xmpValue_.xmpArrayType(), xaNone);

}



TEST_F(XmpValueTest_826, SetXmpArrayType_BoundaryConditions_826) {

    // Assuming XmpArrayType is an enum with known values

    xmpValue_.setXmpArrayType(static_cast<XmpArrayType>(-1)); // Out of range value

    EXPECT_EQ(xmpValue_.xmpArrayType(), static_cast<XmpArrayType>(-1));



    xmpValue_.setXmpArrayType(static_cast<XmpArrayType>(1000000)); // Large out of range value

    EXPECT_EQ(xmpValue_.xmpArrayType(), static_cast<XmpArrayType>(1000000));

}



TEST_F(XmpValueTest_826, XmpArrayType_DefaultInitialization_826) {

    EXPECT_EQ(xmpValue_.xmpArrayType(), xaNone);

}
