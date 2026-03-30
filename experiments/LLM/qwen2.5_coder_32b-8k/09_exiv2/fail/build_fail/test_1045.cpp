#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"

#include <memory>



using namespace ::testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(uint64_t, size, (), (const, override));

    MOCK_METHOD(void, seek, (long offset), (override));

    MOCK_METHOD(long, tell, (), (const, override));

    MOCK_METHOD(bool, read, (byte* data, long count), (override));

};



class AsfVideo_HeaderReaderTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    Exiv2::AsfVideo::HeaderReader header_reader_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        header_reader_ = Exiv2::AsfVideo::HeaderReader(mock_io_);

    }

};



TEST_F(AsfVideo_HeaderReaderTest_1045, GetRemainingSize_ReturnsInitialValue_1045) {

    EXPECT_EQ(header_reader_.getRemainingSize(), 0u);

}



// Assuming getSize() returns the size of the DataBuf IdBuf_, and it's not initially set.

TEST_F(AsfVideo_HeaderReaderTest_1045, GetSize_ReturnsZeroInitially_1045) {

    EXPECT_EQ(header_reader_.getSize(), 0u);

}



// Mocking read behavior to simulate data reading and check if getRemainingSize changes accordingly.

TEST_F(AsfVideo_HeaderReaderTest_1045, ReadData_DecreasesRemainingSize_1045) {

    const uint64_t initial_size = 1024;

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(initial_size));

    byte data[10];

    EXPECT_CALL(*mock_io_, read(_, _)).WillOnce(Invoke([](byte* data, long count) -> bool {

        memset(data, 0, count);

        return true;

    }));



    header_reader_.readData(data, sizeof(data));



    EXPECT_EQ(header_reader_.getRemainingSize(), initial_size - sizeof(data));

}



// Boundary condition test for reading zero bytes.

TEST_F(AsfVideo_HeaderReaderTest_1045, ReadZeroBytes_RemainingSizeUnchanged_1045) {

    const uint64_t initial_size = 1024;

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(initial_size));



    byte data[1];

    EXPECT_CALL(*mock_io_, read(_, _)).WillOnce(Invoke([](byte* data, long count) -> bool {

        return true; // Simulate successful read of zero bytes.

    }));



    header_reader_.readData(data, 0);



    EXPECT_EQ(header_reader_.getRemainingSize(), initial_size);

}



// Exceptional case: Simulate a failed read operation and check if remaining size is unchanged.

TEST_F(AsfVideo_HeaderReaderTest_1045, ReadFails_RemainingSizeUnchanged_1045) {

    const uint64_t initial_size = 1024;

    EXPECT_CALL(*mock_io_, size()).WillOnce(Return(initial_size));



    byte data[1];

    EXPECT_CALL(*mock_io_, read(_, _)).WillOnce(Invoke([](byte* data, long count) -> bool {

        return false; // Simulate failed read.

    }));



    header_reader_.readData(data, sizeof(data));



    EXPECT_EQ(header_reader_.getRemainingSize(), initial_size);

}



// Test getId() function to ensure it returns a reference to the DataBuf IdBuf_.

TEST_F(AsfVideo_HeaderReaderTest_1045, GetId_ReturnsDataBufReference_1045) {

    DataBuf& id = header_reader_.getId();

    EXPECT_EQ(id.type(), GUID);

}
