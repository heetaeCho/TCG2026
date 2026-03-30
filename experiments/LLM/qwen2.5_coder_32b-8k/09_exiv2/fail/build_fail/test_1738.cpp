#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tiffimage.hpp"

#include "exiv2/basicio.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



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



class TiffImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        tiffImage = std::make_unique<TiffImage>(std::move(mockIo), false);

    }



    std::unique_ptr<TiffImage> tiffImage;

    std::unique_ptr<MockBasicIo> mockIo;

};



TEST_F(TiffImageTest_1738, PrintStructure_SuccessfulOpenAndRead_1738) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, imageType()).WillOnce(Return(ImageType::tiff));

    EXPECT_CALL(*mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test_path"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    std::ostringstream oss;

    tiffImage->printStructure(oss, PrintStructureOption::kpsNone, 0);

}



TEST_F(TiffImageTest_1738, PrintStructure_OpenFailed_1738) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test_path"));



    std::ostringstream oss;

    EXPECT_THROW(tiffImage->printStructure(oss, PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(TiffImageTest_1738, PrintStructure_NotAJpegOrTiffType_1738) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, imageType()).WillOnce(Return(ImageType::none));

    EXPECT_CALL(*mockIo, isTiffType(_, false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(true));



    std::ostringstream oss;

    EXPECT_THROW(tiffImage->printStructure(oss, PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(TiffImageTest_1738, PrintStructure_SeekFailed_1738) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, imageType()).WillOnce(Return(ImageType::tiff));

    EXPECT_CALL(*mockIo, seek(0, BasicIo::beg)).WillOnce(Return(-1));



    std::ostringstream oss;

    EXPECT_THROW(tiffImage->printStructure(oss, PrintStructureOption::kpsNone, 0), Error);

}



TEST_F(TiffImageTest_1738, PrintStructure_ErrorOrEofAfterTypeCheck_1738) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, imageType()).WillOnce(Return(ImageType::none));

    EXPECT_CALL(*mockIo, isTiffType(_, false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(true));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true));



    std::ostringstream oss;

    EXPECT_THROW(tiffImage->printStructure(oss, PrintStructureOption::kpsNone, 0), Error);

}
