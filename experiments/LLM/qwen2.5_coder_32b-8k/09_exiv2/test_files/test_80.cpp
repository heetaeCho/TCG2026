#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Eq;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(int64_t, tell, (), (const, override));

    MOCK_METHOD(int64_t, size, (), (const, override));

};



class MockHeaderReader : public RiffVideo::HeaderReader {

public:

    MockHeaderReader(const std::string& id, uint64_t size) : RiffVideo::HeaderReader(nullptr), id_(id), size_(size) {}

    MOCK_METHOD(std::string, getId, (), (const, override));

    MOCK_METHOD(uint64_t, getSize, (), (const, override));



private:

    std::string id_;

    uint64_t size_;



    const std::string& getId() const override { return id_; }

    uint64_t getSize() const override { return size_; }

};



class RiffVideoTest_80 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        riffVideo = std::make_unique<RiffVideo>(std::move(mockIo));

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<RiffVideo> riffVideo;

};



TEST_F(RiffVideoTest_80, ReadChunk_AVIH_80) {

    MockHeaderReader header("avih", 123);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(*mockIo, seekOrThrow(123, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_STRH_80) {

    MockHeaderReader header("strh", 456);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(*mockIo, seekOrThrow(456, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_STRF_80) {

    MockHeaderReader header("strf", 789);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(789));

    EXPECT_CALL(*mockIo, seekOrThrow(789, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_FMT_Audio_80) {

    MockHeaderReader header("fmt ", 1011);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(1011));

    EXPECT_CALL(*mockIo, seekOrThrow(1011, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_STRD_80) {

    MockHeaderReader header("strd", 1213);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(1213));

    EXPECT_CALL(*mockIo, seekOrThrow(1213, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_STRN_80) {

    MockHeaderReader header("strn", 1415);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(1415));

    EXPECT_CALL(*mockIo, seekOrThrow(1415, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_VPRP_80) {

    MockHeaderReader header("vprp", 1617);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(1617));

    EXPECT_CALL(*mockIo, seekOrThrow(1617, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_IDX1_80) {

    MockHeaderReader header("idx1", 1819);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(1819));

    EXPECT_CALL(*mockIo, seekOrThrow(1819, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_DATA_80) {

    MockHeaderReader header("data", 2021);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(2021));

    EXPECT_CALL(*mockIo, seekOrThrow(2021, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_JUNK_80) {

    MockHeaderReader header("junk", 2223);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(header, getSize()).WillOnce(::testing::Return(2223));

    EXPECT_CALL(*mockIo, seekOrThrow(2223, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_Unknown_80) {

    MockHeaderReader header("unknown", 2425);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(*mockIo, seekOrThrow(2425, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_ZeroSize_80) {

    MockHeaderReader header("avih", 0);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(*mockIo, seekOrThrow(0, BasicIo::beg, ErrorCode::kerFailedToReadImageData));

    riffVideo->readChunk(header);

}



TEST_F(RiffVideoTest_80, ReadChunk_SeekThrows_80) {

    MockHeaderReader header("avih", 123);

    EXPECT_CALL(header, getId()).WillRepeatedly(::testing::ReturnRefOfCopy(header.getId()));

    EXPECT_CALL(*mockIo, seekOrThrow(123, BasicIo::beg, ErrorCode::kerFailedToReadImageData)).WillOnce(testing::Throw(std::runtime_error("Seek failed")));

    EXPECT_THROW(riffVideo->readChunk(header), std::runtime_error);

}
