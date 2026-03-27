#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/jpgimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::NiceMock;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte* buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const override));

    MOCK_METHOD(size_t, size, (), (const override));

    MOCK_METHOD(bool, isopen, (), (const override));

    MOCK_METHOD(int, error, (), (const override));

    MOCK_METHOD(bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class JpegImageTest_1222 : public ::testing::Test {

protected:

    NiceMock<MockBasicIo> mock_io;

    JpegImage jpeg_image{std::make_unique<MockBasicIo>(mock_io), false};

};



TEST_F(JpegImageTest_1222, IsThisType_ReturnsTrueForJpeg_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate reading a JPEG SOI marker

            if (rcount >= 2) {

                buf[0] = 0xFF;

                buf[1] = 0xD8;

            }

            return rcount;

        });



    EXPECT_TRUE(jpeg_image.isThisType(mock_io, false));

}



TEST_F(JpegImageTest_1222, IsThisType_ReturnsFalseForNonJpeg_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate reading non-JPEG data

            if (rcount >= 2) {

                buf[0] = 0x00;

                buf[1] = 0x00;

            }

            return rcount;

        });



    EXPECT_FALSE(jpeg_image.isThisType(mock_io, false));

}



TEST_F(JpegImageTest_1222, IsThisType_AdvancesStreamWhenTrue_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate reading a JPEG SOI marker

            if (rcount >= 2) {

                buf[0] = 0xFF;

                buf[1] = 0xD8;

            }

            return rcount;

        });

    EXPECT_CALL(mock_io, seek(2, BasicIo::beg)).Times(1);



    jpeg_image.isThisType(mock_io, true);

}



TEST_F(JpegImageTest_1222, IsThisType_DoesNotAdvanceStreamWhenFalse_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate reading non-JPEG data

            if (rcount >= 2) {

                buf[0] = 0x00;

                buf[1] = 0x00;

            }

            return rcount;

        });

    EXPECT_CALL(mock_io, seek(_, _)).Times(0);



    jpeg_image.isThisType(mock_io, true);

}



TEST_F(JpegImageTest_1222, IsThisType_HandlesShortRead_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate a short read (only 1 byte)

            if (rcount >= 1) {

                buf[0] = 0xFF;

            }

            return 1;

        });



    EXPECT_FALSE(jpeg_image.isThisType(mock_io, false));

}



TEST_F(JpegImageTest_1222, IsThisType_ReadThrowsError_1222) {

    EXPECT_CALL(mock_io, read(_, _))

        .WillOnce([](byte* buf, size_t rcount) -> size_t {

            // Simulate a read error

            return 0;

        });



    EXPECT_FALSE(jpeg_image.isThisType(mock_io, false));

}
