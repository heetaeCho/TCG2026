#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include <string>

#include <fstream>



using namespace Exiv2;



class MockExifData : public ExifData {

public:

    MOCK_METHOD(void, add, (const Entry&), (override));

};



class ExifThumbTest_772 : public ::testing::Test {

protected:

    MockExifData mockExifData;

    ExifThumb exifThumb;



    ExifThumbTest_772() : exifThumb(mockExifData) {}



    std::string createTempFile(const std::string& content = "dummy") {

        static int fileCount = 0;

        std::ofstream tempFile;

        std::string fileName = "tempfile_" + std::to_string(fileCount++) + ".jpg";

        tempFile.open(fileName, std::ios::out | std::ios::binary);

        tempFile << content;

        tempFile.close();

        return fileName;

    }



    void removeTempFile(const std::string& fileName) {

        std::remove(fileName.c_str());

    }

};



TEST_F(ExifThumbTest_772, SetJpegThumbnail_NormalOperation_772) {

    std::string path = createTempFile();

    EXPECT_NO_THROW(exifThumb.setJpegThumbnail(path));

    removeTempFile(path);

}



TEST_F(ExifThumbTest_772, SetJpegThumbnail_EmptyFilePath_772) {

    EXPECT_THROW(exifThumb.setJpegThumbnail(""), Exiv2::Error);

}



TEST_F(ExifThumbTest_772, SetJpegThumbnail_NonExistentFile_772) {

    EXPECT_THROW(exifThumb.setJpegThumbnail("non_existent_file.jpg"), Exiv2::Error);

}



TEST_F(ExifThumbTest_772, SetJpegThumbnail_EmptyFile_772) {

    std::string path = createTempFile("");

    EXPECT_NO_THROW(exifThumb.setJpegThumbnail(path));

    removeTempFile(path);

}
