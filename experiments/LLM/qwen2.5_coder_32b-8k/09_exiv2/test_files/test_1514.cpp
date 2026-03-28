#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include "makernote_int.hpp"  // Assuming this is where the newOMSystemMn function is declared



namespace Exiv2 {

    namespace Internal {



class TiffIfdMakernote {};



using ::testing::Eq;

using ::testing::IsNull;

using ::testing::NotNull;



class MakernoteIntTest_1514 : public ::testing::Test {

protected:

    uint16_t tag = 0x0000;  // Example tag value

    IfdId group = ifd0Id;   // Example group value

    IfdId mnGroup = makernoteIfdId;  // Example makernote group value

    ByteOrder byteOrder = littleEndian;  // Example byte order value



    std::unique_ptr<const byte> data;

    size_t dataSize;



    void SetUp() override {

        dataSize = OMSystemMnHeader::sizeOfSignature() + 18;

        data = std::make_unique<byte[]>(dataSize);

    }

};



TEST_F(MakernoteIntTest_1514, ValidDataReturnsNonNullPtr_1514) {

    auto result = newOMSystemMn(tag, group, mnGroup, data.get(), dataSize, byteOrder);

    EXPECT_THAT(result, NotNull());

}



TEST_F(MakernoteIntTest_1514, NullDataReturnsNullPtr_1514) {

    auto result = newOMSystemMn(tag, group, mnGroup, nullptr, dataSize, byteOrder);

    EXPECT_THAT(result, IsNull());

}



TEST_F(MakernoteIntTest_1514, SizeLessThanMinimumReturnsNullPtr_1514) {

    dataSize = OMSystemMnHeader::sizeOfSignature() + 17;

    auto result = newOMSystemMn(tag, group, mnGroup, data.get(), dataSize, byteOrder);

    EXPECT_THAT(result, IsNull());

}



TEST_F(MakernoteIntTest_1514, SizeEqualToMinimumReturnsNonNullPtr_1514) {

    dataSize = OMSystemMnHeader::sizeOfSignature() + 18;

    auto result = newOMSystemMn(tag, group, mnGroup, data.get(), dataSize, byteOrder);

    EXPECT_THAT(result, NotNull());

}



TEST_F(MakernoteIntTest_1514, SizeGreaterThanMinimumReturnsNonNullPtr_1514) {

    dataSize = OMSystemMnHeader::sizeOfSignature() + 19;

    auto result = newOMSystemMn(tag, group, mnGroup, data.get(), dataSize, byteOrder);

    EXPECT_THAT(result, NotNull());

}



    }  // namespace Internal

}  // namespace Exiv2
