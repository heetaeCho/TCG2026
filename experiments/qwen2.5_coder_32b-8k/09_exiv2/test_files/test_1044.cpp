#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/asfvideo.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, open, (OpenMode mode), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(size_t, read, (byte* data, size_t count), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), (override));

    MOCK_METHOD(uint64_t, seek, (uint64_t offset, Position pos), (override));

    MOCK_METHOD(bool, good, (), (const, override));

};



class AsfVideo_HeaderReaderTest_1044 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    HeaderReader* header_reader_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        header_reader_ = new HeaderReader(mock_io_);

    }



    void TearDown() override {

        delete header_reader_;

    }

};



TEST_F(AsfVideo_HeaderReaderTest_1044, getSize_ReturnsInitialSize_1044) {

    EXPECT_EQ(header_reader_->getSize(), 0u);

}



TEST_F(AsfVideo_HeaderReaderTest_1044, getRemainingSize_ReturnsInitialRemainingSize_1044) {

    EXPECT_EQ(header_reader_->getRemainingSize(), 0u);

}



TEST_F(AsfVideo_HeaderReaderTest_1044, getId_ReturnsDataBufReference_1044) {

    DataBuf& id_buf = header_reader_->getId();

    EXPECT_TRUE(id_buf.guid() == GUID); // Assuming GUID is a constant defined somewhere

}
