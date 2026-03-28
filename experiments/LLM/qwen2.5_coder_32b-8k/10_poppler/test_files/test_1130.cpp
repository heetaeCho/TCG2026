#include <gtest/gtest.h>

#include "FileSpec.h"



class EmbFileTest_1130 : public ::testing::Test {

protected:

    virtual void SetUp() override {

        // Setup any common resources if needed

    }



    virtual void TearDown() override {

        // Cleanup any common resources if needed

    }

};



TEST_F(EmbFileTest_1130, MimeType_ReturnsValidPointer_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    const GooString* mimeType = embFile.mimeType();

    EXPECT_NE(mimeType, nullptr);

}



TEST_F(EmbFileTest_1130, Size_ReturnsNonNegativeValue_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    int size = embFile.size();

    EXPECT_GE(size, 0);

}



TEST_F(EmbFileTest_1130, ModDate_ReturnsValidPointer_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    const GooString* modDate = embFile.modDate();

    EXPECT_NE(modDate, nullptr);

}



TEST_F(EmbFileTest_1130, CreateDate_ReturnsValidPointer_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    const GooString* createDate = embFile.createDate();

    EXPECT_NE(createDate, nullptr);

}



TEST_F(EmbFileTest_1130, Checksum_ReturnsValidPointer_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    const GooString* checksum = embFile.checksum();

    EXPECT_NE(checksum, nullptr);

}



TEST_F(EmbFileTest_1130, IsOk_ReturnsTrueForValidObject_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    bool isOk = embFile.isOk();

    EXPECT_TRUE(isOk);

}



TEST_F(EmbFileTest_1130, Save_ReturnsFalseForInvalidPath_1130) {

    Object efStream;

    EmbFile embFile(std::move(efStream));

    bool result = embFile.save("/nonexistent/path/file.txt");

    EXPECT_FALSE(result);

}
