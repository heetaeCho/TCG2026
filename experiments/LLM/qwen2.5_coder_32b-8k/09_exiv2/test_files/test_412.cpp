#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2::Internal;

using namespace testing;



// Mock class for TypeInfo

class MockTypeInfo {

public:

    MOCK_STATIC_METHOD1(typeName, const char*(Exiv2::TypeId));

};



TEST(toTiffTypeTest_412, ValidTypeId_ReturnsCorrespondingTiffType_412) {

    EXPECT_EQ(toTiffType(Exiv2::unsignedByte), ttUnsignedByte);

    EXPECT_EQ(toTiffType(Exiv2::asciiString), ttAsciiString);

    EXPECT_EQ(toTiffType(Exiv2::undefined), ttUndefined);

}



TEST(toTiffTypeTest_412, InvalidTypeId_ReturnsTtUndefined_412) {

    EXPECT_CALL(MockTypeInfo(), typeName(static_cast<Exiv2::TypeId>(0x10000)))

        .WillOnce(Return("string"));



    EXPECT_EQ(toTiffType(static_cast<Exiv2::TypeId>(0x10000)), ttUndefined);

}



TEST(toTiffTypeTest_412, BoundaryConditionMaxValidTypeId_ReturnsCorrespondingTiffType_412) {

    EXPECT_EQ(toTiffType(Exiv2::tiffIfd), ttTiffIfd);

}



TEST(toTiffTypeTest_412, BoundaryConditionAboveMaxValidTypeId_ReturnsTtUndefined_412) {

    EXPECT_CALL(MockTypeInfo(), typeName(static_cast<Exiv2::TypeId>(0xffff + 1)))

        .WillOnce(Return("string"));



    EXPECT_EQ(toTiffType(static_cast<Exiv2::TypeId>(0xffff + 1)), ttUndefined);

}



TEST(toTiffTypeTest_412, BoundaryConditionMinValidTypeId_ReturnsCorrespondingTiffType_412) {

    EXPECT_EQ(toTiffType(Exiv2::unsignedByte), ttUnsignedByte);

}
