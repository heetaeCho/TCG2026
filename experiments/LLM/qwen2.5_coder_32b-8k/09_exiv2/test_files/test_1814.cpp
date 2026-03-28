#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/crwimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class CrwImageTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    std::unique_ptr<MockBasicIo> mock_io_ptr{&mock_io};

    CrwImage crw_image{std::move(mock_io_ptr), false};

};



TEST_F(CrwImageTest, ReadMetadata_Success_1814) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, mmap(false)).WillOnce(Return(new byte[1024]));

    EXPECT_CALL(mock_io, munmap()).WillOnce(Return(0));



    EXPECT_NO_THROW(crw_image.readMetadata());

}



TEST_F(CrwImageTest, ReadMetadata_OpenFailed_1814) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));

    EXPECT_CALL(mock_io, path()).WillOnce(Return("test.crw"));



    EXPECT_THROW(crw_image.readMetadata(), Error);

}



TEST_F(CrwImageTest, ReadMetadata_NotACrwImage_1814) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, mmap(false)).WillOnce(Return(new byte[1024]));

    EXPECT_CALL(mock_io, munmap()).WillOnce(Return(0));



    // Assuming isCrwType returns false

    EXPECT_THROW(crw_image.readMetadata(), Error);

}



TEST_F(CrwImageTest, ReadMetadata_ReadFailed_1814) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, mmap(false)).WillOnce(Return(new byte[1024]));

    EXPECT_CALL(mock_io, munmap()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(1));



    EXPECT_THROW(crw_image.readMetadata(), Error);

}



TEST_F(CrwImageTest, ReadMetadata_EOF_1814) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillOnce(Return(true));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(1024));

    EXPECT_CALL(mock_io, mmap(false)).WillOnce(Return(new byte[1024]));

    EXPECT_CALL(mock_io, munmap()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true));



    EXPECT_THROW(crw_image.readMetadata(), Error);

}
