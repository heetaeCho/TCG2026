#include <gtest/gtest.h>

#include "FileSpec.h"



class EmbFileTest : public ::testing::Test {

protected:

    Object mockObject;

    EmbFile* embFile;



    void SetUp() override {

        embFile = new EmbFile(std::move(mockObject));

    }



    void TearDown() override {

        delete embFile;

    }

};



TEST_F(EmbFileTest_1133, IsOk_ReturnsTrueWhenStream_1133) {

    mockObject = Object(true);

    EXPECT_TRUE(embFile->isOk());

}



TEST_F(EmbFileTest_1133, IsOk_ReturnsFalseWhenNotStream_1133) {

    mockObject = Object(false);

    EXPECT_FALSE(embFile->isOk());

}



TEST_F(EmbFileTest_1133, Size_ReturnsCorrectSize_1133) {

    // Assuming m_size is set during construction or through some other means

    int expectedSize = 123; // Hypothetical size value for testing

    embFile->m_size = expectedSize;

    EXPECT_EQ(embFile->size(), expectedSize);

}



TEST_F(EmbFileTest_1133, ModDate_ReturnsCorrectModDate_1133) {

    auto modDateStr = std::make_unique<GooString>("2023-10-05T14:48:00Z");

    embFile->m_modDate = std::move(modDateStr);

    EXPECT_EQ(embFile->modDate()->c_str(), "2023-10-05T14:48:00Z");

}



TEST_F(EmbFileTest_1133, CreateDate_ReturnsCorrectCreateDate_1133) {

    auto createDateStr = std::make_unique<GooString>("2023-10-05T14:48:00Z");

    embFile->m_createDate = std::move(createDateStr);

    EXPECT_EQ(embFile->createDate()->c_str(), "2023-10-05T14:48:00Z");

}



TEST_F(EmbFileTest_1133, Checksum_ReturnsCorrectChecksum_1133) {

    auto checksumStr = std::make_unique<GooString>("abcdef1234567890");

    embFile->m_checksum = std::move(checksumStr);

    EXPECT_EQ(embFile->checksum()->c_str(), "abcdef1234567890");

}



TEST_F(EmbFileTest_1133, MimeType_ReturnsCorrectMimeType_1133) {

    auto mimeTypeStr = std::make_unique<GooString>("application/pdf");

    embFile->m_mimetype = std::move(mimeTypeStr);

    EXPECT_EQ(embFile->mimeType()->c_str(), "application/pdf");

}



TEST_F(EmbFileTest_1133, StreamObject_ReturnsCorrectStreamObject_1133) {

    EXPECT_EQ(embFile->streamObject(), &embFile->m_objStr);

}



// Assuming stream() method returns a valid Stream pointer when isOk() is true

TEST_F(EmbFileTest_1133, Stream_ReturnsValidStreamPointerWhenOk_1133) {

    mockObject = Object(true);

    EXPECT_NE(embFile->stream(), nullptr);

}



TEST_F(EmbFileTest_1133, Stream_ReturnsNullptrWhenNotOk_1133) {

    mockObject = Object(false);

    EXPECT_EQ(embFile->stream(), nullptr);

}



// Assuming save() method returns true when file is saved successfully

TEST_F(EmbFileTest_1133, Save_ReturnsTrueOnSuccessfulSave_1133) {

    mockObject = Object(true);

    // Mocking the behavior of FILE* operations for save2(FILE*) would require Google Mock

    EXPECT_TRUE(embFile->save("/tmp/testfile.pdf"));

}



// Assuming save() method returns false when file cannot be saved

TEST_F(EmbFileTest_1133, Save_ReturnsFalseOnFailedSave_1133) {

    mockObject = Object(true);

    // Mocking the behavior of FILE* operations for save2(FILE*) would require Google Mock

    EXPECT_FALSE(embFile->save("/nonexistent/path/testfile.pdf"));

}
