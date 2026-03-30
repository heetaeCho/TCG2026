#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <cstdint>



using namespace Exiv2;



TEST_F(ValueTypeTest_164, URationalToUint32_NormalOperation_164) {

    ValueType<URational> urational;

    URational u RationalVal(100, 1);

    urational = ValueType<URational>(uRationalVal, TypeId::urational);



    EXPECT_EQ(urational.toUint32(0), 100U);

}



TEST_F(ValueTypeTest_164, URationalToUint32_BoundaryCondition_ZeroNumerator_164) {

    ValueType<URational> urational;

    URational uRationalVal(0, 1);

    urational = ValueType<URational>(uRationalVal, TypeId::urational);



    EXPECT_EQ(urational.toUint32(0), 0U);

}



TEST_F(ValueTypeTest_164, URationalToUint32_BoundaryCondition_ZeroDenominator_164) {

    ValueType<URational> urational;

    URational uRationalVal(1, 0); // This should be handled gracefully

    urational = ValueType<URational>(uRationalVal, TypeId::urational);



    EXPECT_THROW(urational.toUint32(0), std::runtime_error);

}



TEST_F(ValueTypeTest_164, URationalToUint32_BoundaryCondition_LargeNumerator_164) {

    ValueType<URational> urational;

    URational uRationalVal(LARGE_INT, 1); // Assuming LARGE_INT is defined as a large number

    urational = ValueType<URational>(uRationalVal, TypeId::urational);



    EXPECT_EQ(urational.toUint32(0), static_cast<uint32_t>(LARGE_INT));

}



TEST_F(ValueTypeTest_164, URationalToUint32_ExceptionalCase_InvalidIndex_164) {

    ValueType<URational> urational;

    URational uRationalVal(100, 1);

    urational = ValueType<URational>(uRationalVal, TypeId::urational);



    EXPECT_THROW(urational.toUint32(1), std::out_of_range); // Invalid index

}
