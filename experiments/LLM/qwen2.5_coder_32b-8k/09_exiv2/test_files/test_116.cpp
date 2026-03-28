#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/types.hpp"

#include "helper_functions.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

};



TEST_F(MockBasicIoTest_116, ReadQWORDTag_SuccessfulRead_116) {

    MockBasicIo mockIo;

    const uint64_t expectedValue = 0x123456789ABCDEF0ULL;

    uint8_t buffer[8] = {0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12};



    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, size()).WillOnce(Return(8));

    EXPECT_CALL(mockIo, read(8)).WillOnce(Return(DataBuf(buffer, 8)));



    uint64_t result = readQWORDTag(BasicIo::UniquePtr(&mockIo));



    EXPECT_EQ(result, expectedValue);

}



TEST_F(MockBasicIoTest_116, ReadQWORDTag_TellBeyondEndOfFile_116) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, tell()).WillOnce(Return(10));

    EXPECT_CALL(mockIo, size()).WillOnce(Return(8));



    EXPECT_THROW(readQWORDTag(BasicIo::UniquePtr(&mockIo)), Exiv2Error);

}



TEST_F(MockBasicIoTest_116, ReadQWORDTag_ReadLessThanQWORD_116) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, size()).WillOnce(Return(7));

    EXPECT_CALL(mockIo, read(8)).WillOnce(Return(DataBuf()));



    EXPECT_THROW(readQWORDTag(BasicIo::UniquePtr(&mockIo)), Exiv2Error);

}



TEST_F(MockBasicIoTest_116, ReadQWORDTag_ReadReturnsEmptyBuffer_116) {

    MockBasicIo mockIo;



    EXPECT_CALL(mockIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, size()).WillOnce(Return(8));

    EXPECT_CALL(mockIo, read(8)).WillOnce(Return(DataBuf()));



    EXPECT_THROW(readQWORDTag(BasicIo::UniquePtr(&mockIo)), Exiv2Error);

}
