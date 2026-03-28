#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <memory>

#include <cstdint>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = IfdId::exifId;

    const byte* pData = nullptr;

    size_t size = 0;

    ByteOrder byteOrder = littleEndian;



    std::unique_ptr<TiffIfdMakernote> createMakernote() {

        return newOlympusMn(tag, group, IfdId(), pData, size, byteOrder);

    }

};



TEST_F(TiffIfdMakernoteTest_1511, NullDataReturnsNullPtr_1511) {

    pData = nullptr;

    size = 14;

    EXPECT_EQ(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, SizeLessThan14ReturnsNullPtr_1511) {

    const char data[] = "OM SYSTEM\0\0\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = 13;

    EXPECT_EQ(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, InvalidSignatureReturnsNullPtr_1511) {

    const char data[] = "INVALID\0\0\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = 14;

    EXPECT_EQ(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, ValidOMSystemSignatureCreatesOMSystemMn2_1511) {

    const char data[] = "OM SYSTEM\0\0\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = OMSystemMnHeader::sizeOfSignature() + 18;

    EXPECT_NE(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, SizeLessThanOMSystemSizeReturnsNullPtr_1511) {

    const char data[] = "OM SYSTEM\0\0\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = OMSystemMnHeader::sizeOfSignature() + 17;

    EXPECT_EQ(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, ValidOlympusSignatureCreatesOM2Mn2_1511) {

    const char data[] = "OLYMPUS\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = OlympusMnHeader::sizeOfSignature() + 18;

    EXPECT_NE(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, SizeLessThanOlympusSizeReturnsNullPtr_1511) {

    const char data[] = "OLYMPUS\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = OlympusMnHeader::sizeOfSignature() + 17;

    EXPECT_EQ(createMakernote(), nullptr);

}



TEST_F(TiffIfdMakernoteTest_1511, SizeLessThanOlympus2SizeReturnsNullPtr_1511) {

    const char data[] = "OLYMPUS\0II";

    pData = reinterpret_cast<const byte*>(data);

    size = Olympus2MnHeader::sizeOfSignature() + 17;

    EXPECT_EQ(createMakernote(), nullptr);

}
