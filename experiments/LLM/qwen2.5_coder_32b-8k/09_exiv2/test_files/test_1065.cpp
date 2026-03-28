#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::InSequence;

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

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

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

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class ImageTest : public ::testing::Test {

protected:

    MockBasicIo mock_io;

    Image image{ImageType::jpeg, 0xff, std::make_unique<MockBasicIo>(mock_io)};

    std::ostringstream output;



    void SetUp() override {

        visits.clear();

    }

};



TEST_F(ImageTest_1065, NormalOperation_PrintIFDStructure_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata));

    EXPECT_CALL(mock_io, readOrThrow(_, 2, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte* buf, size_t rcount, ErrorCode err) { std::memset(buf, 1, rcount); return rcount; });

    EXPECT_CALL(mock_io, tell()).WillRepeatedly(Return(0));

    image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 0, false, 'T', 0);

    EXPECT_EQ(output.str().find("STRUCTURE OF TIFF FILE (TT):"), 0U); // Check if the structure starts with expected string

}



TEST_F(ImageTest_1065, BoundaryCondition_PrintIFDStructure_StartGreaterThanSize_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(_, BasicIo::beg, ErrorCode::kerCorruptedMetadata));

    EXPECT_CALL(mock_io, readOrThrow(_, 2, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte* buf, size_t rcount, ErrorCode err) { std::memset(buf, 1, rcount); return rcount; });

    EXPECT_CALL(mock_io, tell()).WillRepeatedly(Return(100));

    EXPECT_CALL(mock_io, size()).WillOnce(Return(50));

    image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 100, false, 'T', 0);

}



TEST_F(ImageTest_1065, ErrorCondition_PrintIFDStructure_SeekOrThrowFails_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(_, BasicIo::beg, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::Throw(Error(ErrorCode::kerCorruptedMetadata)));

    image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 0, false, 'T', 0);

}



TEST_F(ImageTest_1065, ErrorCondition_PrintIFDStructure_ReadOrThrowFails_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata));

    EXPECT_CALL(mock_io, readOrThrow(_, 2, ErrorCode::kerCorruptedMetadata)).WillOnce(testing::Throw(Error(ErrorCode::kerCorruptedMetadata)));

    image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 0, false, 'T', 0);

}



TEST_F(ImageTest_1065, ErrorCondition_PrintIFDStructure_TooManyDirectoryEntries_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata));

    EXPECT_CALL(mock_io, readOrThrow(_, 2, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte* buf, size_t rcount, ErrorCode err) { std::memset(buf, 51, rcount); return rcount; });

    EXPECT_THROW(image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 0, false, 'T', 0), Error);

}



TEST_F(ImageTest_1065, ErrorCondition_PrintIFDStructure_DirectoryTooLarge_1065) {

    EXPECT_CALL(mock_io, seekOrThrow(0, BasicIo::beg, ErrorCode::kerCorruptedMetadata));

    EXPECT_CALL(mock_io, readOrThrow(_, 2, ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte* buf, size_t rcount, ErrorCode err) { std::memset(buf, 1, rcount); return rcount; });

    EXPECT_CALL(mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(mock_io, readOrThrow(_, 256 * sizeof(uint16_t), ErrorCode::kerCorruptedMetadata))

        .WillOnce([](byte* buf, size_t rcount, ErrorCode err) { std::memset(buf, 1, rcount); return rcount; });

    EXPECT_THROW(image.printIFDStructure(mock_io, output, PrintStructureOption::kpsBasic, 0, false, 'T', 0), Error);

}
