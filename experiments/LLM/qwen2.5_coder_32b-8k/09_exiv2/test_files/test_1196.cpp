#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/bmffimage.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;



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

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string&, path, (), (const override));

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class BmffImageTest_1196 : public ::testing::Test {

protected:

    void SetUp() override {

        io = std::make_unique<MockBasicIo>();

        image = new BmffImage(std::move(io), false, 10);

    }



    void TearDown() override {

        delete image;

    }



    std::unique_ptr<MockBasicIo> io;

    BmffImage* image;

};



TEST_F(BmffImageTest_1196, ParseTiff_NormalOperation_1196) {

    EXPECT_CALL(*io, tell()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));

    EXPECT_CALL(*io, seek(0, BasicIo::beg)).Times(1);

    EXPECT_CALL(*io, read(1024)).WillOnce(testing::Invoke([](size_t rcount) -> DataBuf {

        DataBuf buffer(rcount);

        // Fill buffer with some data if necessary

        return buffer;

    }));

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).Times(1);



    image->parseTiff(0x8769, 1024, 0);

}



TEST_F(BmffImageTest_1196, ParseTiff_StartGreaterThanSize_1196) {

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));



    EXPECT_THROW(image->parseTiff(0x8769, 512, 2048), Error);

}



TEST_F(BmffImageTest_1196, ParseTiff_LengthGreaterThanRemainingSize_1196) {

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));



    EXPECT_THROW(image->parseTiff(0x8769, 513, 512), Error);

}



TEST_F(BmffImageTest_1196, ParseTiff_StartGreaterThanInt64Max_1196) {

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));



    EXPECT_THROW(image->parseTiff(0x8769, 512, static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) + 1), Error);

}



TEST_F(BmffImageTest_1196, ParseTiff_LengthGreaterThanSizeTMax_1196) {

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));



    EXPECT_THROW(image->parseTiff(0x8769, static_cast<uint64_t>(std::numeric_limits<size_t>::max()) + 1, 512), Error);

}



TEST_F(BmffImageTest_1196, ParseTiff_ReadLessThanLength_1196) {

    EXPECT_CALL(*io, tell()).WillOnce(testing::Return(0));

    EXPECT_CALL(*io, size()).WillRepeatedly(testing::Return(1024));

    EXPECT_CALL(*io, seek(0, BasicIo::beg)).Times(1);

    EXPECT_CALL(*io, read(512)).WillOnce(testing::Invoke([](size_t rcount) -> DataBuf {

        DataBuf buffer(rcount - 1); // Simulate reading less than requested

        return buffer;

    }));

    EXPECT_CALL(*io, seek(_, BasicIo::beg)).Times(1);



    image->parseTiff(0x8769, 512, 0);

}
