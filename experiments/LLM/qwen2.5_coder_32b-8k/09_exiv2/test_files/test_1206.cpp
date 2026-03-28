#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/preview.hpp"

#include "exiv2/types.hpp"

#include <fstream>



using namespace Exiv2;

using namespace testing;



class PreviewImageTest_1206 : public Test {

protected:

    void SetUp() override {

        // Initialize a sample DataBuf for the PreviewImage

        byte data[] = {0x00, 0x01, 0x02, 0x03};

        previewData = std::make_unique<DataBuf>(data, sizeof(data));

        previewImage = std::make_unique<PreviewImage>(

            PreviewProperties(), std::move(*previewData)

        );

    }



    void TearDown() override {

        // Clean up any files created during tests

        std::remove(testFilePath.c_str());

    }



    std::unique_ptr<DataBuf> previewData;

    std::unique_ptr<PreviewImage> previewImage;

    const std::string testFilePath = "test_preview_file";

};



TEST_F(PreviewImageTest_1206, WriteFile_CreatesFileWithCorrectSize_1206) {

    size_t fileSize = previewImage->writeFile(testFilePath);

    EXPECT_EQ(fileSize, 4); // Size of the data array



    std::ifstream file(testFilePath, std::ios::binary | std::ios::ate);

    ASSERT_TRUE(file.is_open());

    EXPECT_EQ(static_cast<size_t>(file.tellg()), fileSize);

}



TEST_F(PreviewImageTest_1206, WriteFile_ReturnsZeroForEmptyData_1206) {

    // Create a PreviewImage with empty data

    DataBuf emptyData;

    auto emptyPreviewImage = std::make_unique<PreviewImage>(

        PreviewProperties(), std::move(emptyData)

    );



    size_t fileSize = emptyPreviewImage->writeFile(testFilePath);

    EXPECT_EQ(fileSize, 0);



    std::ifstream file(testFilePath, std::ios::binary | std::ios::ate);

    ASSERT_TRUE(file.is_open());

    EXPECT_EQ(static_cast<size_t>(file.tellg()), fileSize);

}



TEST_F(PreviewImageTest_1206, WriteFile_ThrowsOnInvalidPath_1206) {

    // Assuming an invalid path would be something like "/nonexistent_directory/file"

    const std::string invalidPath = "/nonexistent_directory/test_preview_file";

    

    EXPECT_THROW(previewImage->writeFile(invalidPath), Error);

}



TEST_F(PreviewImageTest_1206, WriteFile_HandlesExistingFile_1206) {

    // First write to create the file

    previewImage->writeFile(testFilePath);



    // Write again to check if it overwrites or throws an error

    size_t fileSize = previewImage->writeFile(testFilePath);

    EXPECT_EQ(fileSize, 4); // Size of the data array



    std::ifstream file(testFilePath, std::ios::binary | std::ios::ate);

    ASSERT_TRUE(file.is_open());

    EXPECT_EQ(static_cast<size_t>(file.tellg()), fileSize);

}
