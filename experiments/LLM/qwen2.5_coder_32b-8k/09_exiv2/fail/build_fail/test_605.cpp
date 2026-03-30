#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {

    class MockRemoteIo : public RemoteIo {

    public:

        MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

        MOCK_METHOD(void, throwException, (), ());

    };



    DataBuf createDataBuf(const std::vector<uint8_t>& data) {

        return DataBuf(data.data(), data.size());

    }

}



using namespace Exiv2;

using ::testing::_;



class RemoteIoTest_605 : public ::testing::Test {

protected:

    MockRemoteIo mockRemoteIo;

};



TEST_F(RemoteIoTest_605, ReadSuccessfulRead_605) {

    std::vector<uint8_t> expectedData = {1, 2, 3, 4};

    EXPECT_CALL(mockRemoteIo, read(_, expectedData.size())).WillOnce([](byte* buf, size_t rcount) {

        memcpy(buf, "\x01\x02\x03\x04", rcount);

        return rcount;

    });



    DataBuf result = mockRemoteIo.read(expectedData.size());

    EXPECT_EQ(result.size(), expectedData.size());

    EXPECT_TRUE(std::equal(result.c_data(), result.c_data() + result.size(), expectedData.begin()));

}



TEST_F(RemoteIoTest_605, ReadZeroBytesRequested_605) {

    EXPECT_CALL(mockRemoteIo, read(_, 0)).WillOnce([](byte* buf, size_t rcount) {

        return rcount;

    });



    DataBuf result = mockRemoteIo.read(0);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(RemoteIoTest_605, ReadNoDataAvailable_605) {

    EXPECT_CALL(mockRemoteIo, read(_, _)).WillOnce([](byte* buf, size_t rcount) {

        return 0;

    });



    EXPECT_THROW({

        mockRemoteIo.read(10);

    }, Error);

}



TEST_F(RemoteIoTest_605, ReadPartialDataAvailable_605) {

    std::vector<uint8_t> expectedData = {1, 2};

    EXPECT_CALL(mockRemoteIo, read(_, expectedData.size())).WillOnce([](byte* buf, size_t rcount) {

        memcpy(buf, "\x01\x02", rcount);

        return 2;

    });



    DataBuf result = mockRemoteIo.read(expectedData.size());

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(std::equal(result.c_data(), result.c_data() + result.size(), expectedData.begin()));

}



TEST_F(RemoteIoTest_605, ReadLargeAmountOfData_605) {

    size_t largeSize = 1024 * 1024; // 1MB

    std::vector<uint8_t> expectedData(largeSize, 0xFF);

    EXPECT_CALL(mockRemoteIo, read(_, largeSize)).WillOnce([&](byte* buf, size_t rcount) {

        memcpy(buf, expectedData.data(), rcount);

        return rcount;

    });



    DataBuf result = mockRemoteIo.read(largeSize);

    EXPECT_EQ(result.size(), largeSize);

    EXPECT_TRUE(std::equal(result.c_data(), result.c_data() + result.size(), expectedData.begin()));

}
