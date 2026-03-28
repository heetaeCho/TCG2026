#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/cr2image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class Cr2ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo = std::make_unique<MockBasicIo>();

    Cr2Image cr2Image{std::move(mockIo), false};

};



TEST_F(Cr2ImageTest_1743, ReadMetadata_Success_1743) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, mmap(_)).WillOnce(Return(reinterpret_cast<byte*>(new byte[1])));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.cr2"));



    cr2Image.readMetadata();

}



TEST_F(Cr2ImageTest_1743, ReadMetadata_OpenFailed_1743) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.cr2"));



    EXPECT_THROW(cr2Image.readMetadata(), Error);

}



TEST_F(Cr2ImageTest_1743, ReadMetadata_NotCr2Type_1743) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, mmap(_)).WillOnce(Return(nullptr));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.cr2"));



    EXPECT_THROW(cr2Image.readMetadata(), Error);

}



TEST_F(Cr2ImageTest_1743, ReadMetadata_DecodeFailed_1743) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, mmap(_)).WillOnce(Return(reinterpret_cast<byte*>(new byte[1])));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.cr2"));

    EXPECT_CALL(Cr2Parser::decode, (_, _, _, reinterpret_cast<const byte*>(_), 1))

        .WillOnce(Return(invalidByteOrder));



    EXPECT_THROW(cr2Image.readMetadata(), Error);

}
