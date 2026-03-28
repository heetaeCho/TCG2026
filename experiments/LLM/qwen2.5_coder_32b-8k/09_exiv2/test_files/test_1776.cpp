#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockImage : public Image {

public:

    MOCK_METHOD(void, readMetadata, (), (override));

    MOCK_METHOD(void, writeMetadata, (), (override));

    MOCK_METHOD(ByteOrder, byteOrder, () const, (override));

};



TEST_F(CiffComponentTest_1776, DecodeCallsDoDecode_1776) {

    MockImage mockImage(ImageType::jpeg, 0x100, nullptr);

    CiffComponent ciffComponent(0x123, 0x456);

    EXPECT_CALL(mockImage, byteOrder()).WillOnce(testing::Return(littleEndian));

    EXPECT_CALL(mockImage, readMetadata()).Times(0);

    EXPECT_CALL(mockImage, writeMetadata()).Times(0);



    ciffComponent.decode(mockImage, littleEndian);

}



TEST_F(CiffComponentTest_1776, DecodeWithBigEndianByteOrder_1776) {

    MockImage mockImage(ImageType::jpeg, 0x100, nullptr);

    CiffComponent ciffComponent(0x123, 0x456);

    EXPECT_CALL(mockImage, byteOrder()).WillOnce(testing::Return(bigEndian));

    EXPECT_CALL(mockImage, readMetadata()).Times(0);

    EXPECT_CALL(mockImage, writeMetadata()).Times(0);



    ciffComponent.decode(mockImage, bigEndian);

}



TEST_F(CiffComponentTest_1776, DecodeWithDefaultConstructedComponent_1776) {

    MockImage mockImage(ImageType::jpeg, 0x100, nullptr);

    CiffComponent ciffComponent;

    EXPECT_CALL(mockImage, byteOrder()).WillOnce(testing::Return(littleEndian));

    EXPECT_CALL(mockImage, readMetadata()).Times(0);

    EXPECT_CALL(mockImage, writeMetadata()).Times(0);



    ciffComponent.decode(mockImage, littleEndian);

}



TEST_F(CiffComponentTest_1776, DecodeWithInvalidByteOrder_1776) {

    MockImage mockImage(ImageType::jpeg, 0x100, nullptr);

    CiffComponent ciffComponent(0x123, 0x456);

    EXPECT_CALL(mockImage, byteOrder()).WillOnce(testing::Return(invalidByteOrder));

    EXPECT_CALL(mockImage, readMetadata()).Times(0);

    EXPECT_CALL(mockImage, writeMetadata()).Times(0);



    ciffComponent.decode(mockImage, invalidByteOrder);

}
