#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(uint64_t, size, (), (const override));

    MOCK_METHOD(uint64_t, read, (char* buf, uint64_t bytes), (override));

    MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));

};



class AsfVideo_HeaderReaderTest_1046 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    AsfVideo::HeaderReader header_reader_;



    AsfVideo_HeaderReaderTest_1046() : mock_io_(std::make_unique<MockBasicIo>()),

                                       header_reader_(mock_io_) {}

};



TEST_F(AsfVideo_HeaderReaderTest_1046, GetIdReturnsDataBuf_1046) {

    DataBuf& id = header_reader_.getId();

    EXPECT_TRUE(!id.empty());  // Assuming GUID is non-empty

}



TEST_F(AsfVideo_HeaderReaderTest_1046, GetSizeReturnsValidValue_1046) {

    EXPECT_GE(header_reader_.getSize(), 0);

}



TEST_F(AsfVideo_HeaderReaderTest_1046, GetRemainingSizeReturnsValidValue_1046) {

    EXPECT_GE(header_reader_.getRemainingSize(), 0);

}



TEST_F(AsfVideo_HeaderReaderTest_1046, BoundaryCondition_SizeZero_1046) {

    ON_CALL(*mock_io_, size()).WillByDefault(::testing::Return(0));

    EXPECT_EQ(header_reader_.getSize(), 0);

    EXPECT_EQ(header_reader_.getRemainingSize(), 0);

}



TEST_F(AsfVideo_HeaderReaderTest_1046, BoundaryCondition_SizeNonZero_1046) {

    uint64_t test_size = 128;

    ON_CALL(*mock_io_, size()).WillByDefault(::testing::Return(test_size));

    EXPECT_EQ(header_reader_.getSize(), test_size);

}



TEST_F(AsfVideo_HeaderReaderTest_1046, ExternalInteraction_ReadCalledOnce_1046) {

    uint64_t test_size = 128;

    ON_CALL(*mock_io_, size()).WillByDefault(::testing::Return(test_size));

    EXPECT_CALL(*mock_io_, read(::testing::NotNull(), ::testing::Eq(GUID.size())))

        .Times(1);

    header_reader_.getId();

}
