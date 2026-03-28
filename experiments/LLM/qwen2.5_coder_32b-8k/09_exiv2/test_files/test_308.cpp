#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/makernote_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockMnHeader : public MnHeader {

public:

    MOCK_METHOD(bool, read, (const byte* pData, size_t size, ByteOrder byteOrder), (override));

};



class TiffIfdMakernoteTest_308 : public ::testing::Test {

protected:

    std::unique_ptr<MockMnHeader> mockMnHeader;

    TiffIfdMakernote tiffIfdMakernote;



    TiffIfdMakernoteTest_308()

        : mockMnHeader(std::make_unique<MockMnHeader>()),

          tiffIfdMakernote(0, IfdId::rootIFD, IfdId::rootIFD, std::move(mockMnHeader), false) {}

};



TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithNullPointer_308) {

    EXPECT_TRUE(tiffIfdMakernote.readHeader(nullptr, 10, littleEndian));

}



TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithNonNullPointerAndSizeZero_308) {

    byte data[] = {0};

    EXPECT_CALL(*mockMnHeader, read(_, 0, _)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tiffIfdMakernote.readHeader(data, 0, littleEndian));

}



TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithNonNullPointerAndPositiveSize_308) {

    byte data[] = {1, 2, 3};

    EXPECT_CALL(*mockMnHeader, read(data, 3, littleEndian)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tiffIfdMakernote.readHeader(data, 3, littleEndian));

}



TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithDifferentByteOrder_308) {

    byte data[] = {1, 2, 3};

    EXPECT_CALL(*mockMnHeader, read(data, 3, bigEndian)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(tiffIfdMakernote.readHeader(data, 3, bigEndian));

}
