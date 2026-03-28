#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(uint16_t, tag, (), (const, override));

    MOCK_METHOD(IfdId, group, (), (const, override));

    MOCK_METHOD(byte*, start, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, write, (IoWrapper&, ByteOrder, size_t, size_t, size_t, size_t&), (override));

    MOCK_METHOD(size_t, writeData, (IoWrapper&, ByteOrder, size_t, size_t, size_t&) const, (override));

    MOCK_METHOD(size_t, writeImage, (IoWrapper&, ByteOrder) const, (override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, sizeData, (), (const, override));

    MOCK_METHOD(size_t, sizeImage, (), (const, override));

};



class SonyTagDecipherTest_1625 : public ::testing::Test {

protected:

    MockTiffComponent mockObject;

    const byte testBytes[4] = {0x00, 0x01, 0x02, 0x03};

    size_t testSize = sizeof(testBytes);

};



TEST_F(SonyTagDecipherTest_1625, NormalOperation_1625) {

    uint16_t tag = 0x9050;

    DataBuf result = sonyTagDecipher(tag, testBytes, testSize, &mockObject);

    EXPECT_TRUE(result.pData != nullptr && result.size > 0);

}



TEST_F(SonyTagDecipherTest_1625, BoundaryCondition_ZeroSize_1625) {

    uint16_t tag = 0x9050;

    DataBuf result = sonyTagDecipher(tag, testBytes, 0, &mockObject);

    EXPECT_TRUE(result.pData == nullptr && result.size == 0);

}



TEST_F(SonyTagDecipherTest_1625, BoundaryCondition_NullBytes_1625) {

    uint16_t tag = 0x9050;

    DataBuf result = sonyTagDecipher(tag, nullptr, testSize, &mockObject);

    EXPECT_TRUE(result.pData == nullptr && result.size == 0);

}



TEST_F(SonyTagDecipherTest_1625, BoundaryCondition_NullObject_1625) {

    uint16_t tag = 0x9050;

    DataBuf result = sonyTagDecipher(tag, testBytes, testSize, nullptr);

    EXPECT_TRUE(result.pData == nullptr && result.size == 0);

}



TEST_F(SonyTagDecipherTest_1625, ExternalInteraction_VerifyObjectMethodsNotCalled_1625) {

    uint16_t tag = 0x9050;

    EXPECT_CALL(mockObject, tag()).Times(0);

    EXPECT_CALL(mockObject, group()).Times(0);

    EXPECT_CALL(mockObject, start()).Times(0);

    EXPECT_CALL(mockObject, count()).Times(0);



    DataBuf result = sonyTagDecipher(tag, testBytes, testSize, &mockObject);

}
