#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "mrwimage.hpp"

#include "basicio.hpp"

#include "error.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class MrwImageTest_981 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        mrwImage = std::make_unique<MrwImage>(std::move(mockIo), false);

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<MrwImage> mrwImage;

};



TEST_F(MrwImageTest_981, ReadMetadata_SuccessfulRead_981) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.mrw"));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the initial 8 bytes

        static const byte testData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

        memcpy(buf, testData, rcount);

        return rcount;

    });

    EXPECT_CALL(*mockIo, seek(8, BasicIo::cur)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the next 8 bytes

        static const byte testData[] = {0x54, 0x54, 0x57, 0x00, 0x00, 0x01, 0x02, 0x03};

        memcpy(buf, testData, rcount);

        return rcount;

    });

    EXPECT_CALL(*mockIo, read(_, 1)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the remaining data

        static const byte testData[] = {0x54};

        memcpy(buf, testData, rcount);

        return rcount;

    });



    EXPECT_NO_THROW(mrwImage->readMetadata());

}



TEST_F(MrwImageTest_981, ReadMetadata_OpenFailed_981) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(1));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.mrw"));



    EXPECT_THROW(mrwImage->readMetadata(), Error);

}



TEST_F(MrwImageTest_981, ReadMetadata_NotAnMrwFile_981) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.mrw"));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the initial 8 bytes

        static const byte testData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

        memcpy(buf, testData, rcount);

        return rcount;

    });

    EXPECT_CALL(*mockIo, seek(8, BasicIo::cur)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the next 8 bytes

        static const byte testData[] = {0x54, 0x54, 0x4E, 0x00, 0x00, 0x01, 0x02, 0x03};

        memcpy(buf, testData, rcount);

        return rcount;

    });



    EXPECT_THROW(mrwImage->readMetadata(), Error);

}



TEST_F(MrwImageTest_981, ReadMetadata_ReadFailed_981) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.mrw"));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce(Return(0));



    EXPECT_THROW(mrwImage->readMetadata(), Error);

}



TEST_F(MrwImageTest_981, ReadMetadata_EndOfFile_981) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.mrw"));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte* buf, size_t rcount) -> size_t {

        // Simulate reading the initial 8 bytes

        static const byte testData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

        memcpy(buf, testData, rcount);

        return rcount;

    });

    EXPECT_CALL(*mockIo, seek(8, BasicIo::cur)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce(Return(0));



    EXPECT_THROW(mrwImage->readMetadata(), Error);

}
