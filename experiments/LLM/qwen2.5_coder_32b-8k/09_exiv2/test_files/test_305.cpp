#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/makernote_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockMnHeader : public MnHeader {

public:

    MOCK_METHOD(bool, read, (const byte *pData, size_t size, ByteOrder byteOrder), (override));

    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, write, (IoWrapper &ioWrapper, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, ifdOffset, (), (const, override));

    MOCK_METHOD(ByteOrder, byteOrder, (), (const, override));

    MOCK_METHOD(size_t, baseOffset, (size_t mnOffset), (const, override));

};



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MockMnHeader> mockHeader;

    ByteOrder imageByteOrder = littleEndian;



    void SetUp() override {

        mockHeader = std::make_unique<MockMnHeader>();

        mockHeader->setByteOrder(littleEndian);

    }



    TiffIfdMakernote createTiffIfdMakernote(std::unique_ptr<MnHeader> pHeader) {

        return TiffIfdMakernote(0, ifd0Id, exifId, std::move(pHeader), false);

    }

};



TEST_F(TiffIfdMakernoteTest_305, ByteOrder_ReturnsImageByteOrderWhenNoHeader_305) {

    // Arrange

    TiffIfdMakernote tiffIfdMakernote = createTiffIfdMakernote(nullptr);

    tiffIfdMakernote.setImageByteOrder(littleEndian);



    // Act & Assert

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), littleEndian);

}



TEST_F(TiffIfdMakernoteTest_305, ByteOrder_ReturnsHeaderByteOrderWhenValid_305) {

    // Arrange

    TiffIfdMakernote tiffIfdMakernote = createTiffIfdMakernote(std::move(mockHeader));

    EXPECT_CALL(*mockHeader, byteOrder()).WillOnce(::testing::Return(bigEndian));



    // Act & Assert

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), bigEndian);

}



TEST_F(TiffIfdMakernoteTest_305, ByteOrder_ReturnsInvalidByteOrderWhenNullHeader_305) {

    // Arrange

    TiffIfdMakernote tiffIfdMakernote = createTiffIfdMakernote(nullptr);



    // Act & Assert

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), invalidByteOrder);

}



TEST_F(TiffIfdMakernoteTest_305, ByteOrder_ReturnsImageByteOrderWhenHeaderHasInvalidByteOrder_305) {

    // Arrange

    TiffIfdMakernote tiffIfdMakernote = createTiffIfdMakernote(std::move(mockHeader));

    EXPECT_CALL(*mockHeader, byteOrder()).WillOnce(::testing::Return(invalidByteOrder));



    // Act & Assert

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), imageByteOrder);

}
