#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "jpgimage.hpp"

#include "basicio.hpp"

#include <sstream>



using namespace Exiv2;

using testing::Return;

using testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(void, readOrThrow, (byte*, size_t, ErrorCode), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo&), (override));

    MOCK_METHOD(int, seek, (int64_t, Position), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t, Position, ErrorCode), (override));

    MOCK_METHOD(byte*, mmap, (bool), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class JpegBaseTest_1218 : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    std::unique_ptr<MockBasicIo> io_ptr = std::make_unique<MockBasicIo>();

    JpegBase jpeg_base{ImageType::jpeg, std::move(io_ptr), false, nullptr, 0};



    void SetUp() override {

        io_ptr.reset(new MockBasicIo());

        jpeg_base.io_ = std::unique_ptr<BasicIo>(io_ptr.get());

    }

};



TEST_F(JpegBaseTest_1218, OpenFailure_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(1));

    EXPECT_THROW(jpeg_base.printStructure(std::ostringstream(), kpsBasic, 0), Error);

}



TEST_F(JpegBaseTest_1218, NotAJpegFile_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));

    EXPECT_THROW(jpeg_base.printStructure(std::ostringstream(), kpsBasic, 0), Error);

}



TEST_F(JpegBaseTest_1218, BasicPrintStructure_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));



    std::vector<byte> jpeg_data = {0xFF, 0xD8, 0xFF, 0xE1}; // SOI, APP1

    EXPECT_CALL(*io_ptr, read(_, _)).WillOnce(testing::Invoke([jpeg_data](byte* buffer, size_t count) -> size_t {

        std::copy(jpeg_data.begin(), jpeg_data.end(), buffer);

        return jpeg_data.size();

    }));



    std::ostringstream output;

    jpeg_base.printStructure(output, kpsBasic, 0);

    EXPECT_EQ(output.str().find("STRUCTURE OF JPEG FILE"), 0);

}



TEST_F(JpegBaseTest_1218, XmpOption_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));



    std::vector<byte> jpeg_data = {0xFF, 0xD8, 0xFF, 0xE1}; // SOI, APP1

    EXPECT_CALL(*io_ptr, read(_, _)).WillOnce(testing::Invoke([jpeg_data](byte* buffer, size_t count) -> size_t {

        std::copy(jpeg_data.begin(), jpeg_data.end(), buffer);

        return jpeg_data.size();

    }));



    std::ostringstream output;

    jpeg_base.printStructure(output, kpsXMP, 0);

}



TEST_F(JpegBaseTest_1218, RecursiveOption_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));



    std::vector<byte> jpeg_data = {0xFF, 0xD8, 0xFF, 0xE1}; // SOI, APP1

    EXPECT_CALL(*io_ptr, read(_, _)).WillOnce(testing::Invoke([jpeg_data](byte* buffer, size_t count) -> size_t {

        std::copy(jpeg_data.begin(), jpeg_data.end(), buffer);

        return jpeg_data.size();

    }));



    std::ostringstream output;

    jpeg_base.printStructure(output, kpsRecursive, 0);

}



TEST_F(JpegBaseTest_1218, IccProfileOption_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));



    std::vector<byte> jpeg_data = {0xFF, 0xD8, 0xFF, 0xE2}; // SOI, APP2

    EXPECT_CALL(*io_ptr, read(_, _)).WillOnce(testing::Invoke([jpeg_data](byte* buffer, size_t count) -> size_t {

        std::copy(jpeg_data.begin(), jpeg_data.end(), buffer);

        return jpeg_data.size();

    }));



    std::ostringstream output;

    jpeg_base.printStructure(output, kpsIccProfile, 0);

}



TEST_F(JpegBaseTest_1218, IptcEraseOption_1218) {

    EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));

    EXPECT_CALL(*io_ptr, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*io_ptr, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*io_ptr, eof()).WillRepeatedly(Return(false));



    std::vector<byte> jpeg_data = {0xFF, 0xD8, 0xFF, 0xED}; // SOI, APP13

    EXPECT_CALL(*io_ptr, read(_, _)).WillOnce(testing::Invoke([jpeg_data](byte* buffer, size_t count) -> size_t {

        std::copy(jpeg_data.begin(), jpeg_data.end(), buffer);

        return jpeg_data.size();

    }));



    std::ostringstream output;

    jpeg_base.printStructure(output, kpsIptcErase, 0);

}
