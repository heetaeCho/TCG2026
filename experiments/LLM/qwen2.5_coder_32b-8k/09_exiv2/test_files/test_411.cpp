#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



// Mock function for findTagInfo

TypePtr mockFindTagInfo(uint16_t tag, IfdId group) {

    static TagInfo mockTagInfo = {SectionId::image, TypeId::unsignedByte, 0, nullptr};

    if ((tag == 0x0002 && group == IfdId::nikonAFTId) || (tag == 0x0047 && group == IfdId::pentaxId)) {

        mockTagInfo.typeId_ = Exiv2::signedByte;

    } else if (tag == 0x1122 && group == IfdId::ifd0Id) {

        mockTagInfo.typeId_ = Exiv2::asciiString;

    } else if (tag == 0x3344 && group == IfdId::exifId) {

        mockTagInfo.typeId_ = Exiv2::comment;

    } else {

        mockTagInfo.typeId_ = Exiv2::unsignedByte;

    }

    return &mockTagInfo;

}



// Override findTagInfo for testing

namespace Exiv2 { namespace Internal {

    TypePtr findTagInfo(uint16_t tag, IfdId group) {

        return ::mockFindTagInfo(tag, group);

    }

}}



class TiffCompositeTest_411 : public ::testing::Test {

protected:

};



TEST_F(TiffCompositeTest_411, NormalOperation_UndefinedToUnsignedByte_411) {

    EXPECT_EQ(toTypeId(TypeId::undefined, 0x1122, IfdId::ifd0Id), TypeId::asciiString);

}



TEST_F(TiffCompositeTest_411, NormalOperation_CommentTag_411) {

    EXPECT_EQ(toTypeId(TypeId::undefined, 0x3344, IfdId::exifId), TypeId::comment);

}



TEST_F(TiffCompositeTest_411, BoundaryCondition_TagInfoNotFound_411) {

    EXPECT_EQ(toTypeId(TypeId::unsignedByte, 0x9999, IfdId::lastId), TypeId::unsignedByte);

}



TEST_F(TiffCompositeTest_411, SpecialCase_NikonAFTId_0x0002_411) {

    EXPECT_EQ(toTypeId(TypeId::undefined, 0x0002, IfdId::nikonAFTId), TypeId::signedByte);

}



TEST_F(TiffCompositeTest_411, SpecialCase_PentaxId_0x0047_411) {

    EXPECT_EQ(toTypeId(TypeId::undefined, 0x0047, IfdId::pentaxId), TypeId::signedByte);

}



TEST_F(TiffCompositeTest_411, ExceptionalCase_TypeIdUndefined_411) {

    EXPECT_EQ(toTypeId(TypeId::undefined, 0x5566, IfdId::canonId), TypeId::unsignedByte);

}
