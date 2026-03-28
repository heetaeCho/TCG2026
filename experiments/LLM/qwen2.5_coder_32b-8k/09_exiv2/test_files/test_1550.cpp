#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"

#include "exiv2/basicio.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo& src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class OrfImageTest_1550 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        orfImage = std::make_unique<OrfImage>(std::move(mockIo), false);

    }



    std::unique_ptr<OrfImage> orfImage;

    std::unique_ptr<MockBasicIo> mockIo;

};



TEST_F(OrfImageTest_1550, PrintStructure_SuccessfulOpen_1550) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.orf"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, seek(_, _)).WillOnce(Return(0));



    std::ostringstream out;

    orfImage->printStructure(out, PrintStructureOption::kpsNone, 0);

    EXPECT_EQ(out.str(), "ORF IMAGE\n");

}



TEST_F(OrfImageTest_1550, PrintStructure_OpenFailed_1550) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.orf"));



    EXPECT_THROW({

        std::ostringstream out;

        orfImage->printStructure(out, PrintStructureOption::kpsNone, 0);

    }, Error);

}



TEST_F(OrfImageTest_1550, PrintStructure_ImageTypeNotSupported_1550) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.orf"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    // Mocking the imageType() to return ImageType::none and isOrfType to return false

    ON_CALL(*orfImage, imageType()).WillByDefault(Return(ImageType::none));

    EXPECT_CALL(*orfImage, isOrfType(_, _)).WillOnce(Return(false));



    EXPECT_THROW({

        std::ostringstream out;

        orfImage->printStructure(out, PrintStructureOption::kpsNone, 0);

    }, Error);

}



TEST_F(OrfImageTest_1550, PrintStructure_ReadImageDataFailed_1550) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.orf"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(true));



    // Mocking the imageType() to return ImageType::none and isOrfType to return false

    ON_CALL(*orfImage, imageType()).WillByDefault(Return(ImageType::none));

    EXPECT_CALL(*orfImage, isOrfType(_, _)).WillOnce(Return(false));



    EXPECT_THROW({

        std::ostringstream out;

        orfImage->printStructure(out, PrintStructureOption::kpsNone, 0);

    }, Error);

}



TEST_F(OrfImageTest_1550, PrintStructure_NotAJpeg_1550) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(Return("test.orf"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    // Mocking the imageType() to return ImageType::none and isOrfType to return false

    ON_CALL(*orfImage, imageType()).WillByDefault(Return(ImageType::none));

    EXPECT_CALL(*orfImage, isOrfType(_, _)).WillOnce(Return(false));



    EXPECT_THROW({

        std::ostringstream out;

        orfImage->printStructure(out, PrintStructureOption::kpsNone, 0);

    }, Error);

}
