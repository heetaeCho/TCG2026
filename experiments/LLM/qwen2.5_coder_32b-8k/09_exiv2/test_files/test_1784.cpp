#include <gtest/gtest.h>

#include "exiv2/src/crwimage_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class CiffComponentTest_1784 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1784, TypeId_ReturnsUnsignedByteForTag0_1784) {

    EXPECT_EQ(component.typeId(0x0000), unsignedByte);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsAsciiStringForTag2048_1784) {

    EXPECT_EQ(component.typeId(0x0800), asciiString);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsUnsignedShortForTag4096_1784) {

    EXPECT_EQ(component.typeId(0x1000), unsignedShort);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsUnsignedLongForTag6144_1784) {

    EXPECT_EQ(component.typeId(0x1800), unsignedLong);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsUndefinedForTag8192_1784) {

    EXPECT_EQ(component.typeId(0x2000), undefined);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsDirectoryForTag16384_1784) {

    EXPECT_EQ(component.typeId(0x2800), directory);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsDirectoryForTag18432_1784) {

    EXPECT_EQ(component.typeId(0x3000), directory);

}



TEST_F(CiffComponentTest_1784, TypeId_ReturnsInvalidTypeIdForUnrecognizedTag_1784) {

    EXPECT_EQ(component.typeId(0xFFFF), invalidTypeId);

}
