#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/FileSpec.h"

#include <memory>

#include <string>



class FileSpecTest_1135 : public ::testing::Test {

protected:

    std::unique_ptr<FileSpec> fileSpec;



    void SetUp() override {

        // Create a mock or dummy Object to pass to the constructor

        Object* dummyObject = new Object(); // Assuming Object has a default constructor

        fileSpec = std::make_unique<FileSpec>(dummyObject);

        delete dummyObject; // Clean up the dummy object

    }

};



TEST_F(FileSpecTest_1135, GetFileNameReturnsNonNull_1135) {

    const GooString* fileName = fileSpec->getFileName();

    EXPECT_NE(fileName, nullptr);

}



TEST_F(FileSpecTest_1135, IsOkReturnsTrueWhenValid_1135) {

    bool isOkay = fileSpec->isOk();

    EXPECT_TRUE(isOkay); // Assuming a valid FileSpec object returns true

}



TEST_F(FileSpecTest_1135, GetFileNameForPlatformReturnsNonNull_1135) {

    GooString* fileNameForPlatform = fileSpec->getFileNameForPlatform();

    EXPECT_NE(fileNameForPlatform, nullptr);

}



TEST_F(FileSpecTest_1135, GetEmbeddedFileReturnsNullWhenNoEmbedding_1135) {

    EmbFile* embFile = fileSpec->getEmbeddedFile();

    EXPECT_EQ(embFile, nullptr); // Assuming no embedding by default

}



TEST_F(FileSpecTest_1135, GetDescriptionReturnsNonNull_1135) {

    const GooString* description = fileSpec->getDescription();

    EXPECT_NE(description, nullptr);

}
