#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::InSequence;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(int, putb, (byte), (override));

    MOCK_METHOD(DataBuf, read, (size_t), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo&), (override));

    MOCK_METHOD(int, seek, (int64_t, Position), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class AsfVideoTest : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        asfVideo = std::make_unique<AsfVideo>(std::move(io));

    }



    std::unique_ptr<MockBasicIo> io;

    std::unique_ptr<AsfVideo> asfVideo;

};



TEST_F(AsfVideoTest_HeaderExtension_SeeksCorrectly_1569, SeeksByGUIDAndWORDThenHeaderExtDataLength_1569) {

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce([](int64_t offset, BasicIo::Position pos) {

        EXPECT_EQ(offset, GUID + WORD);

        return 0;

    });



    EXPECT_CALL(*io, readDWORDTag(_)).WillOnce(Return(42)); // Mock header_ext_data_length to be 42



    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce([](int64_t offset, BasicIo::Position pos) {

        EXPECT_EQ(offset, GUID + WORD + 42);

        return 0;

    });



    asfVideo->headerExtension();

}



TEST_F(AsfVideoTest_HeaderExtension_ReadsHeaderExtDataLength_1569, ReadsDWORDTagForHeaderExtDataLength_1569) {

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*io, readDWORDTag(_)).WillOnce(Return(42)); // Mock header_ext_data_length to be 42

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce(Return(0));



    asfVideo->headerExtension();

}



TEST_F(AsfVideoTest_HeaderExtension_SeekErrorHandling_1569, HandlesSeekErrorsGracefully_1569) {

    InSequence seq;

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce(Return(-1));

    EXPECT_THROW(asfVideo->headerExtension(), Error);

}



TEST_F(AsfVideoTest_HeaderExtension_ReadErrorHandling_1569, HandlesReadErrorsGracefully_1569) {

    InSequence seq;

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*io, readDWORDTag(_)).WillOnce([](BasicIo* io) -> uint32_t { throw Error(); });

    EXPECT_THROW(asfVideo->headerExtension(), Error);

}
