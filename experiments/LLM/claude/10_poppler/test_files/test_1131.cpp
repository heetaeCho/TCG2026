#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"

class EmbFileTest_1131 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing EmbFile with a null/empty stream object results in not-ok state
TEST_F(EmbFileTest_1131, ConstructWithNullStream_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that streamObject returns a non-null pointer
TEST_F(EmbFileTest_1131, StreamObjectReturnsNonNull_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    Object *streamObj = embFile.streamObject();
    EXPECT_NE(streamObj, nullptr);
}

// Test size with invalid/empty embedded file
TEST_F(EmbFileTest_1131, SizeWithInvalidFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    int size = embFile.size();
    // For an invalid embedded file, size should be -1 or 0
    EXPECT_LE(size, 0);
}

// Test that modDate returns nullptr for empty embedded file
TEST_F(EmbFileTest_1131, ModDateNullForEmptyFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *modDate = embFile.modDate();
    EXPECT_EQ(modDate, nullptr);
}

// Test that createDate returns nullptr for empty embedded file
TEST_F(EmbFileTest_1131, CreateDateNullForEmptyFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *createDate = embFile.createDate();
    EXPECT_EQ(createDate, nullptr);
}

// Test that checksum returns nullptr for empty embedded file
TEST_F(EmbFileTest_1131, ChecksumNullForEmptyFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *checksum = embFile.checksum();
    EXPECT_EQ(checksum, nullptr);
}

// Test that mimeType returns nullptr for empty embedded file
TEST_F(EmbFileTest_1131, MimeTypeNullForEmptyFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *mimeType = embFile.mimeType();
    EXPECT_EQ(mimeType, nullptr);
}

// Test that stream returns nullptr for invalid embedded file
TEST_F(EmbFileTest_1131, StreamNullForInvalidFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    Stream *s = embFile.stream();
    EXPECT_EQ(s, nullptr);
}

// Test that isOk returns false for invalid embedded file
TEST_F(EmbFileTest_1131, IsOkFalseForInvalidFile_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    EXPECT_FALSE(embFile.isOk());
}

// Test save with invalid path for invalid embedded file
TEST_F(EmbFileTest_1131, SaveFailsWithInvalidPath_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("");
    EXPECT_FALSE(result);
}

// Test save with a non-writable path
TEST_F(EmbFileTest_1131, SaveFailsWithNonWritablePath_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("/nonexistent_dir/nonexistent_file.bin");
    EXPECT_FALSE(result);
}

// Test constructing with a valid stream dictionary
TEST_F(EmbFileTest_1131, ConstructWithStreamDict_1131) {
    // Create a stream-like object with a dictionary containing Params
    Dict *dict = new Dict(nullptr);
    Object paramsDict(new Dict(nullptr));
    
    // Build a minimal valid stream object
    Object streamObj(new Dict(nullptr));
    
    EmbFile embFile(std::move(streamObj));
    // Even with a dict object (not a stream), it should handle gracefully
    Object *retObj = embFile.streamObject();
    EXPECT_NE(retObj, nullptr);
}

// Test that streamObject returns the same pointer on multiple calls
TEST_F(EmbFileTest_1131, StreamObjectConsistentPointer_1131) {
    Object obj;
    EmbFile embFile(std::move(obj));
    Object *ptr1 = embFile.streamObject();
    Object *ptr2 = embFile.streamObject();
    EXPECT_EQ(ptr1, ptr2);
}
