#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/makernote_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



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



class TiffIfdMakernoteTest_304 : public ::testing::Test {

protected:

    std::unique_ptr<MockMnHeader> mockMnHeader;

    std::unique_ptr<TiffIfdMakernote> tifffIfdMakernote;



    void SetUp() override {

        mockMnHeader = std::make_unique<MockMnHeader>();

        tifffIfdMakernote = std::make_unique<TiffIfdMakernote>(0x0001, ifdIdExifIFD, ifdIdMakernoteSubIFD, std::move(mockMnHeader), false);

    }

};



TEST_F(TiffIfdMakernoteTest_304, IfdOffset_ReturnsZeroWhenNoHeader_304) {

    EXPECT_EQ(tifffIfdMakernote->ifdOffset(), 0);

}



TEST_F(TiffIfdMakernoteTest_304, IfdOffset_DelegatesToHeaderWhenPresent_304) {

    mockMnHeader = std::make_unique<MockMnHeader>();

    EXPECT_CALL(*mockMnHeader, ifdOffset()).WillOnce(::testing::Return(123));

    tifffIfdMakernote->pHeader_ = std::move(mockMnHeader);

    EXPECT_EQ(tifffIfdMakernote->ifdOffset(), 123);

}



TEST_F(TiffIfdMakernoteTest_304, SetByteOrder_DelegatesToHeader_304) {

    mockMnHeader = std::make_unique<MockMnHeader>();

    EXPECT_CALL(*mockMnHeader, setByteOrder(ByteOrder::bigEndian));

    tifffIfdMakernote->pHeader_ = std::move(mockMnHeader);

    tifffIfdMakernote->setByteOrder(ByteOrder::bigEndian);

}



TEST_F(TiffIfdMakernoteTest_304, SetImageByteOrder_SetsInternalValue_304) {

    tifffIfdMakernote->setImageByteOrder(ByteOrder::littleEndian);

    EXPECT_EQ(tifffIfdMakernote->byteOrder(), ByteOrder::littleEndian);

}



TEST_F(TiffIfdMakernoteTest_304, ReadHeader_DelegatesToHeader_304) {

    const byte data[] = { 0x01, 0x02 };

    mockMnHeader = std::make_unique<MockMnHeader>();

    EXPECT_CALL(*mockMnHeader, read(data, 2, ByteOrder::bigEndian)).WillOnce(::testing::Return(true));

    tifffIfdMakernote->pHeader_ = std::move(mockMnHeader);

    EXPECT_TRUE(tifffIfdMakernote->readHeader(data, 2, ByteOrder::bigEndian));

}



TEST_F(TiffIfdMakernoteTest_304, WriteHeader_DelegatesToHeader_304) {

    IoWrapper ioWrapper;

    mockMnHeader = std::make_unique<MockMnHeader>();

    EXPECT_CALL(*mockMnHeader, write(::testing::Ref(ioWrapper), ByteOrder::bigEndian)).WillOnce(::testing::Return(2));

    tifffIfdMakernote->pHeader_ = std::move(mockMnHeader);

    EXPECT_EQ(tifffIfdMakernote->writeHeader(ioWrapper, ByteOrder::bigEndian), 2);

}
