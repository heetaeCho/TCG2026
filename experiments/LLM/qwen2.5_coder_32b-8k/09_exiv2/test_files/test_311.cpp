#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));



    MockIoWrapper(BasicIo& io, const byte* pHeader, size_t size, OffsetWriter* pow)

        : IoWrapper(io, pHeader, size, pow) {}

};



class MockMnHeader : public MnHeader {

public:

    MOCK_METHOD(bool, read, (const byte * pData, size_t size, ByteOrder byteOrder), (override));

    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, write, (IoWrapper & ioWrapper, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, ifdOffset, (), (const, override));

    MOCK_METHOD(ByteOrder, byteOrder, (), (const, override));

    MOCK_METHOD(size_t, baseOffset, (size_t mnOffset), (const, override));



    MockMnHeader() = default;

};



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    NiceMock<MockIoWrapper> mockIoWrapper;

    std::unique_ptr<NiceMock<MockMnHeader>> mockMnHeader;

    TiffIfdMakernote tiffIfdMakernote;



    TiffIfdMakernoteTest()

        : mockIoWrapper(mockBasicIo, nullptr, 0, nullptr),

          mockMnHeader(std::make_unique<NiceMock<MockMnHeader>>()),

          tiffIfdMakernote(1, ifd0Id, exifId, std::move(mockMnHeader), false) {}



    BasicIo& mockBasicIo;

};



TEST_F(TiffIfdMakernoteTest_311, WriteHeader_HeaderNotSet_ReturnsZero_311) {

    tiffIfdMakernote.pHeader_.reset();

    EXPECT_EQ(tiffIfdMakernote.writeHeader(mockIoWrapper, littleEndian), 0);

}



TEST_F(TiffIfdMakernoteTest_311, WriteHeader_HeaderSet_CallsWriteAndReturnsResult_311) {

    size_t expectedSize = 42;

    ON_CALL(*mockMnHeader, write(_, _)).WillByDefault(testing::Return(expectedSize));

    EXPECT_CALL(*mockMnHeader, write(::testing::Ref(mockIoWrapper), littleEndian));



    EXPECT_EQ(tiffIfdMakernote.writeHeader(mockIoWrapper, littleEndian), expectedSize);

}



TEST_F(TiffIfdMakernoteTest_311, WriteHeader_HeaderSetWithBigEndian_CallsWriteAndReturnsResult_311) {

    size_t expectedSize = 42;

    ON_CALL(*mockMnHeader, write(_, _)).WillByDefault(testing::Return(expectedSize));

    EXPECT_CALL(*mockMnHeader, write(::testing::Ref(mockIoWrapper), bigEndian));



    EXPECT_EQ(tiffIfdMakernote.writeHeader(mockIoWrapper, bigEndian), expectedSize);

}
