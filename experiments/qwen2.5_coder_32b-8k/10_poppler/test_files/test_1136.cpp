#include <gtest/gtest.h>

#include "FileSpec.h"

#include <memory>



class FileSpecTest_1136 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup any common state before tests (if needed)

    }



    virtual void TearDown() {

        // Cleanup any common state after tests (if needed)

    }

};



TEST_F(FileSpecTest_1136, GetDescription_ReturnsValidPointer_1136) {

    Object fileSpecObject;

    FileSpec fileSpec(&fileSpecObject);

    const GooString *description = fileSpec.getDescription();

    EXPECT_TRUE(description != nullptr);

}



TEST_F(FileSpecTest_1136, IsOk_ReturnsTrueForValidFileSpec_1136) {

    Object fileSpecObject;

    FileSpec fileSpec(&fileSpecObject);

    EXPECT_TRUE(fileSpec.isOk());

}



TEST_F(FileSpecTest_1136, GetFileName_ReturnsValidPointer_1136) {

    Object fileSpecObject;

    FileSpec fileSpec(&fileSpecObject);

    const GooString *fileName = fileSpec.getFileName();

    EXPECT_TRUE(fileName != nullptr);

}



TEST_F(FileSpecTest_1136, GetEmbeddedFile_ReturnsNullptrIfNoEmbFile_1136) {

    Object fileSpecObject;

    FileSpec fileSpec(&fileSpecObject);

    EmbFile *embFile = fileSpec.getEmbeddedFile();

    EXPECT_TRUE(embFile == nullptr);

}



TEST_F(FileSpecTest_1136, GetFileNameForPlatform_ReturnsValidPointer_1136) {

    Object fileSpecObject;

    FileSpec fileSpec(&fileSpecObject);

    GooString *fileName = fileSpec.getFileNameForPlatform();

    EXPECT_TRUE(fileName != nullptr);

}



TEST_F(FileSpecTest_1136, NewFileSpecObject_CreatesValidFileSpecObject_1136) {

    XRef xref;

    std::string fileName = "testfile.txt";

    GooFile gooFile; // Assuming GooFile is default-constructible

    Object fileSpecObject = FileSpec::newFileSpecObject(&xref, &gooFile, fileName);

    EXPECT_TRUE(fileSpecObject.isDict());

}
