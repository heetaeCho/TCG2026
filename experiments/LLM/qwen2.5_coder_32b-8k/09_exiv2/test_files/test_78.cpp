#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class RiffVideoTest_78 : public ::testing::Test {

protected:

    BasicIo::UniquePtr mockIo;

    RiffVideo* riffVideo;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        riffVideo = new RiffVideo(std::move(mockIo));

    }



    void TearDown() override {

        delete riffVideo;

    }

};



TEST_F(RiffVideoTest_78, ReadMetadata_SuccessfulRead_78) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024));

    EXPECT_CALL(*mockIo, path()).Times(2).WillRepeatedly(ReturnRefOfCopy(std::string("test.avi")));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(0)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    // Mock the isRiffType function

    EXPECT_CALL(*mockIo, read(_, _))

        .Times(2)

        .WillOnce([](byte* buf, size_t rcount) {

            memcpy(buf, "RIFF", 4);

            return 4;

        })

        .WillOnce([](byte* buf, size_t rcount) {

            memcpy(buf, "AVI ", 4);

            return 4;

        });



    EXPECT_NO_THROW(riffVideo->readMetadata());

}



TEST_F(RiffVideoTest_78, ReadMetadata_FileOpenFailed_78) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).Times(2).WillRepeatedly(ReturnRefOfCopy(std::string("test.avi")));



    try {

        riffVideo->readMetadata();

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerDataSourceOpenFailed);

        EXPECT_STREQ(e.what(), "DataSource open failed for test.avi");

    }

}



TEST_F(RiffVideoTest_78, ReadMetadata_NotRiffType_78) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).Times(2).WillRepeatedly(ReturnRefOfCopy(std::string("test.avi")));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(0)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    // Mock the isRiffType function to return false

    EXPECT_CALL(*mockIo, read(_, _))

        .Times(2)

        .WillOnce([](byte* buf, size_t rcount) {

            memcpy(buf, "RIFF", 4);

            return 4;

        })

        .WillOnce([](byte* buf, size_t rcount) {

            memcpy(buf, "NOTA", 4); // Not a valid RIFF type

            return 4;

        });



    try {

        riffVideo->readMetadata();

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerNotAnImage);

        EXPECT_STREQ(e.what(), "RIFF");

    }

}



TEST_F(RiffVideoTest_78, ReadMetadata_EndOfFileBeforeHeaderRead_78) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).Times(2).WillRepeatedly(ReturnRefOfCopy(std::string("test.avi")));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(0)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true));



    // Mock the isRiffType function

    EXPECT_CALL(*mockIo, read(_, _))

        .Times(1)

        .WillOnce([](byte* buf, size_t rcount) {

            return 0; // Simulate end of file

        });



    try {

        riffVideo->readMetadata();

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerFailedToReadImageData);

    }

}



TEST_F(RiffVideoTest_78, ReadMetadata_ErrorReadingHeader_78) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).Times(2).WillRepeatedly(ReturnRefOfCopy(std::string("test.avi")));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(-1)).WillOnce(Return(-1)); // Simulate read error

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    // Mock the isRiffType function

    EXPECT_CALL(*mockIo, read(_, _))

        .Times(2)

        .WillOnce([](byte* buf, size_t rcount) {

            memcpy(buf, "RIFF", 4);

            return 4;

        })

        .WillOnce([](byte* buf, size_t rcount) {

            return 0; // Simulate read error

        });



    try {

        riffVideo->readMetadata();

        FAIL() << "Expected exception not thrown";

    } catch (const Error& e) {

        EXPECT_EQ(e.code(), ErrorCode::kerFailedToReadImageData);

    }

}
