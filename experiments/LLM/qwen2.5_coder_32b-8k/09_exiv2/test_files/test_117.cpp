#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"

#include "helper_functions.hpp"



using namespace Exiv2;

using namespace testing;



class BasicIoMock : public BasicIo {

public:

    MOCK_METHOD(size_t, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

};



TEST_F(BasicIOTest_117, ReadDWORDTag_NormalOperation_117) {

    std::vector<byte> testData = {0x34, 0x12, 0x78, 0x56}; // little-endian representation of 0x56781234

    BasicIoMock mockBasicIo;

    EXPECT_CALL(mockBasicIo, read(DWORD)).WillOnce(Return(testData));

    EXPECT_CALL(mockBasicIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, size()).WillOnce(Return(DWORD));



    uint32_t result = readDWORDTag(BasicIo::UniquePtr(&mockBasicIo, [](BasicIo*){}));

    EXPECT_EQ(result, 0x56781234);

}



TEST_F(BasicIOTest_117, ReadDWORDTag_BoundaryCondition_AtEndOfFile_117) {

    std::vector<byte> testData = {0x34, 0x12, 0x78, 0x56};

    BasicIoMock mockBasicIo;

    EXPECT_CALL(mockBasicIo, read(DWORD)).WillOnce(Return(testData));

    EXPECT_CALL(mockBasicIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, size()).WillOnce(Return(DWORD));



    uint32_t result = readDWORDTag(BasicIo::UniquePtr(&mockBasicIo, [](BasicIo*){}));

    EXPECT_EQ(result, 0x56781234);

}



TEST_F(BasicIOTest_117, ReadDWORDTag_ExceptionalCase_NotEnoughData_117) {

    std::vector<byte> testData = {0x34, 0x12}; // Less than DWORD size

    BasicIoMock mockBasicIo;

    EXPECT_CALL(mockBasicIo, read(DWORD)).WillOnce(Return(testData));

    EXPECT_CALL(mockBasicIo, tell()).WillOnce(Return(0));

    EXPECT_CALL(mockBasicIo, size()).WillOnce(Return(2));



    EXPECT_THROW({

        readDWORDTag(BasicIo::UniquePtr(&mockBasicIo, [](BasicIo*){}));

    }, Error);

}



TEST_F(BasicIOTest_117, ReadDWORDTag_ExceptionalCase_SeekBeyondEndOfFile_117) {

    std::vector<byte> testData = {0x34, 0x12, 0x78, 0x56};

    BasicIoMock mockBasicIo;

    EXPECT_CALL(mockBasicIo, read(DWORD)).WillOnce(Return(testData));

    EXPECT_CALL(mockBasicIo, tell()).WillOnce(Return(2)); // Already at position 2

    EXPECT_CALL(mockBasicIo, size()).WillOnce(Return(4));



    EXPECT_THROW({

        readDWORDTag(BasicIo::UniquePtr(&mockBasicIo, [](BasicIo*){}));

    }, Error);

}
