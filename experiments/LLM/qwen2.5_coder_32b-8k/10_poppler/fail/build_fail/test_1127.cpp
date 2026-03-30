#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/FileSpec.h"

#include <string>



class EmbFileTest : public ::testing::Test {

protected:

    Object objStr;

    std::unique_ptr<EmbFile> embFile;



    void SetUp() override {

        embFile = std::make_unique<EmbFile>(std::move(objStr));

    }

};



TEST_F(EmbFileTest_1127, ModDateReturnsNonNull_1127) {

    ASSERT_NE(embFile->modDate(), nullptr);

}



TEST_F(EmbFileTest_1127, CreateDateReturnsNonNull_1127) {

    ASSERT_NE(embFile->createDate(), nullptr);

}



TEST_F(EmbFileTest_1127, ChecksumReturnsNonNull_1127) {

    ASSERT_NE(embFile->checksum(), nullptr);

}



TEST_F(EmbFileTest_1127, MimeTypeReturnsNonNull_1127) {

    ASSERT_NE(embFile->mimeType(), nullptr);

}



TEST_F(EmbFileTest_1127, StreamObjectReturnsValidPointer_1127) {

    ASSERT_TRUE(embFile->streamObject() != nullptr);

}



TEST_F(EmbFileTest_1127, StreamReturnsValidPointer_1127) {

    ASSERT_TRUE(embFile->stream() != nullptr);

}



TEST_F(EmbFileTest_1127, IsOkInitiallyTrue_1127) {

    EXPECT_TRUE(embFile->isOk());

}



// Boundary conditions and exceptional cases are limited in this context as the interface doesn't provide much variability.

// Assuming save might fail due to an invalid path, we can test that scenario.



TEST_F(EmbFileTest_1127, SaveFailsOnInvalidPath_1127) {

    EXPECT_FALSE(embFile->save("/nonexistent/path/to/file"));

}



TEST_F(EmbFileTest_1127, SizeReturnsNonNegative_1127) {

    EXPECT_GE(embFile->size(), 0);

}
