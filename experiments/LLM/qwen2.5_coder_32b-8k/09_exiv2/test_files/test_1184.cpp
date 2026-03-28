#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffimage_int.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class OffsetWriterTest_1184 : public Test {

protected:

    MockBasicIo mock_io;

    OffsetWriter offset_writer;



    void SetUp() override {

        // Setup any common state before each test

        offset_writer.setOrigin(0, 100, littleEndian);

        offset_writer.setTarget(0, 200);

    }

};



TEST_F(OffsetWriterTest_1184, WriteOffsets_SeeksCorrectly_1184) {

    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(Return(0));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_WritesFourBytes_1184) {

    EXPECT_CALL(mock_io, write(_, 4))

        .WillOnce(Return(4));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_CorrectByteOrderLittleEndian_1184) {

    byte buf[4] = {0};

    EXPECT_CALL(mock_io, write(ElementsAre(200 % 256, (200 / 256) % 256, (200 / 256 / 256) % 256, (200 / 256 / 256 / 256) % 256), 4))

        .WillOnce(Return(4));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_CorrectByteOrderBigEndian_1184) {

    byte buf[4] = {0};

    offset_writer.setOrigin(0, 100, bigEndian);



    EXPECT_CALL(mock_io, write(ElementsAre((200 / 256 / 256 / 256) % 256, (200 / 256 / 256) % 256, (200 / 256) % 256, 200 % 256), 4))

        .WillOnce(Return(4));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_SeekFailure_ReturnsError_1184) {

    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(Return(-1));

    EXPECT_CALL(mock_io, write(_, 4)).Times(0);



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_WriteFailure_ReturnsError_1184) {

    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, 4)).WillOnce(Return(3));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteMultipleOffsets_Correctly_1184) {

    offset_writer.setOrigin(1, 150, littleEndian);

    offset_writer.setTarget(1, 250);



    EXPECT_CALL(mock_io, seek(100, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, 4))

        .WillOnce(Return(4));



    EXPECT_CALL(mock_io, seek(150, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(mock_io, write(_, 4))

        .WillOnce(Return(4));



    offset_writer.writeOffsets(mock_io);

}



TEST_F(OffsetWriterTest_1184, WriteOffsets_NoOffsets_EmptyOperation_1184) {

    OffsetWriter empty_offset_writer;

    EXPECT_CALL(mock_io, seek(_, _)).Times(0);

    EXPECT_CALL(mock_io, write(_, _)).Times(0);



    empty_offset_writer.writeOffsets(mock_io);

}
