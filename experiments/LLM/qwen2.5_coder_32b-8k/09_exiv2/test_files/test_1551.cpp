#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using testing::_;

using testing::NiceMock;

using testing::Return;

using testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class OrfImageTest : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    OrfImage orf_image{std::make_unique<MockBasicIo>(mock_io), false};

};



TEST_F(OrfImageTest_NormalOperation_1551, ReadMetadata_SuccessfulRead_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, path()).WillOnce(Return("test.orf"));

    EXPECT_CALL(mock_io, mmap(_)).WillOnce(Return(reinterpret_cast<byte*>(new byte[1])));

    EXPECT_CALL(mock_io, size()).WillRepeatedly(Return(1));

    EXPECT_CALL(mock_io, munmap()).Times(1);



    orf_image.readMetadata();

}



TEST_F(OrfImageTest_BoundaryConditions_1551, ReadMetadata_ZeroSizeFile_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, path()).WillOnce(Return("test.orf"));

    EXPECT_CALL(mock_io, mmap(_)).WillOnce(Return(reinterpret_cast<byte*>(new byte[1])));

    EXPECT_CALL(mock_io, size()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, munmap()).Times(1);



    EXPECT_THROW(orf_image.readMetadata(), Error);

}



TEST_F(OrfImageTest_ErrorCases_1551, ReadMetadata_OpenFailed_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(-1));

    EXPECT_THROW(orf_image.readMetadata(), Error);

}



TEST_F(OrfImageTest_ErrorCases_1551, ReadMetadata_NotAnOrfFile_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(false));

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, path()).WillOnce(Return("test.orf"));

    EXPECT_CALL(mock_io, mmap(_)).WillOnce(Return(reinterpret_cast<byte*>(new byte[1])));

    EXPECT_CALL(mock_io, size()).WillRepeatedly(Return(1));

    EXPECT_CALL(mock_io, munmap()).Times(1);



    // Assuming isOrfType returns false

    EXPECT_THROW(orf_image.readMetadata(), Error);

}



TEST_F(OrfImageTest_ErrorCases_1551, ReadMetadata_ReadImageDataFailed_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true)); // Simulate read failure

    EXPECT_CALL(mock_io, error()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, path()).WillOnce(Return("test.orf"));



    EXPECT_THROW(orf_image.readMetadata(), Error);

}



TEST_F(OrfImageTest_ErrorCases_1551, ReadMetadata_FileEndOfFile_1551) {

    EXPECT_CALL(mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(mock_io, isopen()).WillRepeatedly(Return(true));

    EXPECT_CALL(mock_io, eof()).WillOnce(Return(true)); // Simulate read failure

    EXPECT_CALL(mock_io, error()).WillOnce(Return(1)); // Error set



    EXPECT_THROW(orf_image.readMetadata(), Error);

}
