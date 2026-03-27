#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/webpimage.hpp"

#include "exiv2/basicio.hpp"

#include <sstream>

#include <memory>



using namespace Exiv2;

using namespace testing;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class WebPImageTest : public Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<WebPImage> webp_image;



    void SetUp() override {

        mock_io = std::make_unique<StrictMock<MockBasicIo>>();

        webp_image = std::make_unique<WebPImage>(std::move(mock_io));

    }

};



TEST_F(WebPImageTest_70, PrintStructureOpensFileSuccessfully_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsBasic, 0);

}



TEST_F(WebPImageTest_70, PrintStructureThrowsOnFileOpenFailure_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(1));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));



    EXPECT_THROW(webp_image->printStructure(std::ostringstream(), kpsBasic, 0), Error);

}



TEST_F(WebPImageTest_70, PrintStructureThrowsOnNotWebPFile_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return 0; });

    EXPECT_CALL(*mock_io, error()).WillOnce(Return(1));



    EXPECT_THROW(webp_image->printStructure(std::ostringstream(), kpsBasic, 0), Error);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesBasicOption_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsBasic, 0);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesRecursiveOption_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsRecursive, 0);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesXmpOption_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsXMP, 0);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesIccProfileOption_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsIccProfile, 0);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesIptcEraseOption_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsIptcErase, 0);

}



TEST_F(WebPImageTest_70, PrintStructureHandlesPaddingByte_70) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, path()).WillRepeatedly(Return("test.webp"));

    EXPECT_CALL(*mock_io, read(_)).WillOnce([](size_t rcount) -> size_t { return rcount; });

    EXPECT_CALL(*mock_io, seek(_, BasicIo::beg)).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, tell()).WillRepeatedly(Return(0, 1, 2, 3, 4));

    EXPECT_CALL(*mock_io, eof()).WillRepeatedly(Return(false, false, false, true));



    std::ostringstream out;

    webp_image->printStructure(out, kpsBasic, 0);

}
