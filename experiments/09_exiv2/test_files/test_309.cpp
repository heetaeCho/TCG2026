#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "makernote_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



class TiffIfdMakernoteTest : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> mockMnHeader = std::make_unique<MockMnHeader>();

    TiffIfdMakernote tifffifdmakernote{1, ifdGroupExifIFD, ifdGroupExifIFD, std::move(mockMnHeader), false};

};



TEST_F(TiffIfdMakernoteTest_309, SetByteOrderCallsSetByteOrderOnHeader_309) {

    EXPECT_CALL(*dynamic_cast<MockMnHeader*>(tifffifdmakernote.pHeader_.get()), setByteOrder(ByteOrder::littleEndian)).Times(1);

    tifffifdmakernote.setByteOrder(ByteOrder::littleEndian);

}



TEST_F(TiffIfdMakernoteTest_309, SetByteOrderWithNullHeaderDoesNothing_309) {

    TiffIfdMakernote tifffifdmakernote{1, ifdGroupExifIFD, ifdGroupExifIFD, nullptr, false};

    EXPECT_NO_THROW(tifffifdmakernote.setByteOrder(ByteOrder::littleEndian));

}



TEST_F(TiffIfdMakernoteTest_309, SetImageByteOrderSetsImageByteOrder_309) {

    tifffifdmakernote.setImageByteOrder(ByteOrder::bigEndian);

    EXPECT_EQ(tifffifdmakernote.byteOrder(), ByteOrder::bigEndian);

}



TEST_F(TiffIfdMakernoteTest_309, ByteOrderReturnsCorrectValueAfterSet_309) {

    tifffifdmakernote.setByteOrder(ByteOrder::littleEndian);

    EXPECT_EQ(tifffifdmakernote.byteOrder(), ByteOrder::littleEndian);

}



TEST_F(TiffIfdMakernoteTest_309, MnOffsetReturnsDefaultValue_309) {

    EXPECT_EQ(tifffifdmakernote.mnOffset(), 0u);

}



TEST_F(TiffIfdMakernoteTest_309, IfdOffsetDelegatesToHeader_309) {

    EXPECT_CALL(*dynamic_cast<MockMnHeader*>(tifffifdmakernote.pHeader_.get()), ifdOffset()).WillOnce(testing::Return(42u));

    EXPECT_EQ(tifffifdmakernote.ifdOffset(), 42u);

}



TEST_F(TiffIfdMakernoteTest_309, BaseOffsetDelegatesToHeader_309) {

    EXPECT_CALL(*dynamic_cast<MockMnHeader*>(tifffifdmakernote.pHeader_.get()), baseOffset(10)).WillOnce(testing::Return(52u));

    EXPECT_EQ(tifffifdmakernote.baseOffset(10), 52u);

}



class MockMnHeader : public MnHeader {

public:

    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));

    MOCK_METHOD(bool, read, (const byte *pData, size_t size, ByteOrder byteOrder), (override));

    MOCK_METHOD(size_t, write, (IoWrapper &ioWrapper, ByteOrder byteOrder), (override));

    MOCK_METHOD(const size_t, size, (), (override));

    MOCK_METHOD(const size_t, ifdOffset, (), (const, override));

    MOCK_METHOD(const ByteOrder, byteOrder, (), (const, override));

    MOCK_METHOD(const size_t, baseOffset, (size_t mnOffset), (const, override));

};
