#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"

#include "exiv2/error.hpp"

#include "helper_functions.hpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, size, (), (const));

    MOCK_METHOD(size_t, tell, (), (const));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

};



TEST_F(MockBasicIoTest_118, ReadWORDTag_ReturnsCorrectValue_118) {

    NiceMock<MockBasicIo> mockIo;

    const uint8_t data[] = {0x34, 0x12}; // little-endian representation of 0x1234

    EXPECT_CALL(mockIo, size()).WillRepeatedly(Return(2));

    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, read(WORD)).WillOnce(Return(DataBuf(data, WORD)));



    uint16_t result = Exiv2::readWORDTag(BasicIo::UniquePtr(&mockIo));



    EXPECT_EQ(result, 0x1234);

}



TEST_F(MockBasicIoTest_118, ReadWORDTag_AtBoundary_ReturnsCorrectValue_118) {

    NiceMock<MockBasicIo> mockIo;

    const uint8_t data[] = {0x56, 0x78};

    EXPECT_CALL(mockIo, size()).WillRepeatedly(Return(2));

    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, read(WORD)).WillOnce(Return(DataBuf(data, WORD)));



    uint16_t result = Exiv2::readWORDTag(BasicIo::UniquePtr(&mockIo));



    EXPECT_EQ(result, 0x7856);

}



TEST_F(MockBasicIoTest_118, ReadWORDTag_TellBeyondEnd_ThrowsError_118) {

    NiceMock<MockBasicIo> mockIo;

    EXPECT_CALL(mockIo, size()).WillOnce(Return(2));

    EXPECT_CALL(mockIo, tell()).WillOnce(Return(3));



    try {

        Exiv2::readWORDTag(BasicIo::UniquePtr(&mockIo));

        FAIL() << "Expected an exception to be thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerCorruptedMetadata);

    }

}



TEST_F(MockBasicIoTest_118, ReadWORDTag_SizeLessThanTell_ThrowsError_118) {

    NiceMock<MockBasicIo> mockIo;

    EXPECT_CALL(mockIo, size()).WillOnce(Return(1));

    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));



    try {

        Exiv2::readWORDTag(BasicIo::UniquePtr(&mockIo));

        FAIL() << "Expected an exception to be thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerCorruptedMetadata);

    }

}



TEST_F(MockBasicIoTest_118, ReadWORDTag_SizeLessThanTellPlusWORD_ThrowsError_118) {

    NiceMock<MockBasicIo> mockIo;

    EXPECT_CALL(mockIo, size()).WillOnce(Return(2));

    EXPECT_CALL(mockIo, tell()).WillOnce(Return(1));



    try {

        Exiv2::readWORDTag(BasicIo::UniquePtr(&mockIo));

        FAIL() << "Expected an exception to be thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerCorruptedMetadata);

    }

}
