#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pngimage.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class PngImageTest_972 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        png_image = std::make_unique<PngImage>(std::move(mock_io), false);

    }



    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<PngImage> png_image;

};



TEST_F(PngImageTest_972, OpenFileFailure) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1));

    EXPECT_THROW(png_image->printStructure(std::cout, kpsBasic, 0), Error);

}



TEST_F(PngImageTest_972, NotAPngImage) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, _)).WillOnce([](byte* buf, size_t rcount) {

        std::memset(buf, 0, rcount);

        return rcount;

    });

    EXPECT_THROW(png_image->printStructure(std::cout, kpsBasic, 0), Error);

}



TEST_F(PngImageTest_972, SuccessfulPrintStructureBasic) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, _)).WillRepeatedly([](byte* buf, size_t rcount) {

        static bool first_call = true;

        if (first_call) {

            std::memcpy(buf, "\x89PNG\r\n\x1a\n", 8); // PNG signature

            first_call = false;

            return 8;

        }

        return 0; // End of file

    });

    EXPECT_NO_THROW(png_image->printStructure(std::cout, kpsBasic, 0));

}



TEST_F(PngImageTest_972, SuccessfulPrintStructureRecursive) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, _)).WillRepeatedly([](byte* buf, size_t rcount) {

        static bool first_call = true;

        if (first_call) {

            std::memcpy(buf, "\x89PNG\r\n\x1a\n", 8); // PNG signature

            first_call = false;

            return 8;

        }

        return 0; // End of file

    });

    EXPECT_NO_THROW(png_image->printStructure(std::cout, kpsRecursive, 0));

}



TEST_F(PngImageTest_972, SuccessfulPrintStructureIccProfile) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, _)).WillRepeatedly([](byte* buf, size_t rcount) {

        static bool first_call = true;

        if (first_call) {

            std::memcpy(buf, "\x89PNG\r\n\x1a\n", 8); // PNG signature

            first_call = false;

            return 8;

        }

        return 0; // End of file

    });

    EXPECT_NO_THROW(png_image->printStructure(std::cout, kpsIccProfile, 0));

}



TEST_F(PngImageTest_972, SuccessfulPrintStructureXMP) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io, read(_, _)).WillRepeatedly([](byte* buf, size_t rcount) {

        static bool first_call = true;

        if (first_call) {

            std::memcpy(buf, "\x89PNG\r\n\x1a\n", 8); // PNG signature

            first_call = false;

            return 8;

        }

        return 0; // End of file

    });

    EXPECT_NO_THROW(png_image->printStructure(std::cout, kpsXMP, 0));

}



TEST_F(PngImageTest_972, ReadMetadataFailure) {

    EXPECT_CALL(*mock_io, open()).WillOnce(Return(-1));

    EXPECT_THROW(png_image->readMetadata(), Error);

}
