#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jpgimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

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



class JpegBaseTest : public ::testing::Test {

protected:

    MockBasicIo mockIo;

    BasicIo::UniquePtr ioPtr = std::make_unique<MockBasicIo>(mockIo);

    JpegBase jpegBase{kJpegType, std::move(ioPtr), false, nullptr, 0};

};



TEST_F(JpegBaseTest_1219, WriteMetadata_SuccessfulOpenAndClose_1219) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, close()).WillOnce(Return(0));



    jpegBase.writeMetadata();

}



TEST_F(JpegBaseTest_1219, WriteMetadata_OpenFails_ThrowsException_1219) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(-1));



    EXPECT_THROW(jpegBase.writeMetadata(), Error);

}



TEST_F(JpegBaseTest_1219, WriteMetadata_TransferFails_ThrowsException_1219) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, close()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, transfer(_)).WillOnce(Return(-1));



    EXPECT_THROW(jpegBase.writeMetadata(), Error);

}



TEST_F(JpegBaseTest_1219, WriteMetadata_WriteHeaderFails_ThrowsException_1219) {

    // Since writeHeader is private and not directly accessible, we assume it would be invoked in doWriteMetadata

    // For this test to work, mock the internal behavior of transfer to throw an exception which should mimic a failure in writeHeader.

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, close()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, transfer(_)).WillOnce(Return(-1));



    EXPECT_THROW(jpegBase.writeMetadata(), Error);

}



TEST_F(JpegBaseTest_1219, WriteMetadata_CloseFails_LogsErrorButDoesNotThrowException_1219) {

    EXPECT_CALL(mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(mockIo, close()).WillOnce(Return(-1));



    EXPECT_NO_THROW(jpegBase.writeMetadata());

}
