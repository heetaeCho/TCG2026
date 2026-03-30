// File: test_xmpvalue_arraytype_828.cpp

#include <gtest/gtest.h>
#include <exiv2/value.hpp>

using namespace Exiv2;

class XmpValueTest_828 : public ::testing::Test {
protected:
    XmpValue value;
};

// ------------------------------------------------------------
// Normal operation
// ------------------------------------------------------------

TEST_F(XmpValueTest_828, DefaultXmpArrayTypeIsNone_828) {
    // Verify the observable default value
    EXPECT_EQ(value.xmpArrayType(), xaNone);
}

TEST_F(XmpValueTest_828, SetXmpArrayTypeUpdatesGetter_828) {
    value.setXmpArrayType(xaSeq);
    EXPECT_EQ(value.xmpArrayType(), xaSeq);
}

// ------------------------------------------------------------
// Boundary conditions
// ------------------------------------------------------------

TEST_F(XmpValueTest_828, SetXmpArrayTypeToSameValueIsStable_828) {
    value.setXmpArrayType(xaBag);
    EXPECT_EQ(value.xmpArrayType(), xaBag);

    // Set again to the same value
    value.setXmpArrayType(xaBag);
    EXPECT_EQ(value.xmpArrayType(), xaBag);
}

TEST_F(XmpValueTest_828, CanSetDifferentXmpArrayTypesSequentially_828) {
    value.setXmpArrayType(xaAlt);
    EXPECT_EQ(value.xmpArrayType(), xaAlt);

    value.setXmpArrayType(xaSeq);
    EXPECT_EQ(value.xmpArrayType(), xaSeq);

    value.setXmpArrayType(xaNone);
    EXPECT_EQ(value.xmpArrayType(), xaNone);
}

// ------------------------------------------------------------
// Exceptional / error cases (observable behavior)
// ------------------------------------------------------------

TEST_F(XmpValueTest_828, GetterDoesNotThrowOrChangeState_828) {
    value.setXmpArrayType(xaSeq);

    // Repeated calls should be safe and consistent
    EXPECT_NO_THROW({
        auto t1 = value.xmpArrayType();
        auto t2 = value.xmpArrayType();
        EXPECT_EQ(t1, t2);
    });
}