#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/pgfimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class PgfImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<PgfImage> pgfImage;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        pgfImage = std::make_unique<PgfImage>(std::move(mockIo), false);

    }

};



TEST_F(PgfImageTest_1711, ReadMetadata_SuccessfulRead_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x50\x47\x46\x20", rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, tell()).WillOnce(testing::Return(4));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x00\x00\x00\x18", rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, read(testing::_, 20)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        // Mock reading of header structure

        std::memset(buf, 0x00, rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, read(testing::_, 8)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        // Mock reading of image data

        std::memset(buf, 0x00, rcount);

        return rcount;

    }));



    EXPECT_NO_THROW(pgfImage->readMetadata());

}



TEST_F(PgfImageTest_1711, ReadMetadata_OpenFailed_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(1));

    EXPECT_THROW(pgfImage->readMetadata(), Error);

}



TEST_F(PgfImageTest_1711, ReadMetadata_NotPgfFile_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x42\x4d\x38\x0a", rcount); // Not PGF

        return rcount;

    }));

    EXPECT_THROW(pgfImage->readMetadata(), Error);

}



TEST_F(PgfImageTest_1711, ReadMetadata_EmptyFile_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memset(buf, 0x00, rcount);

        return 0; // Simulate end of file

    }));

    EXPECT_THROW(pgfImage->readMetadata(), Error);

}



TEST_F(PgfImageTest_1711, ReadMetadata_HeaderTooLarge_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x50\x47\x46\x20", rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, tell()).WillOnce(testing::Return(4));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\xff\xff\xff\xfe", rcount); // Header size larger than max size

        return rcount;

    }));

    EXPECT_THROW(pgfImage->readMetadata(), Error);

}



TEST_F(PgfImageTest_1711, ReadMetadata_DataReadFailed_1711) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, isopen()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x50\x47\x46\x20", rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, tell()).WillOnce(testing::Return(4));

    EXPECT_CALL(*mockIo, read(testing::_, 4)).WillOnce(testing::Invoke([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x00\x00\x00\x18", rcount);

        return rcount;

    }));

    EXPECT_CALL(*mockIo, read(testing::_, 20)).WillOnce(testing::Return(0)); // Simulate data read failure

    EXPECT_THROW(pgfImage->readMetadata(), Error);

}
