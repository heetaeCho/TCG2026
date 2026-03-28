#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"
#include "PDFDoc.h"

// Test fixture for EmbFile tests
class EmbFileTest_1132 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing EmbFile with a null/none object results in not ok state
TEST_F(EmbFileTest_1132, ConstructWithNullObject_IsNotOk_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test that stream() returns nullptr when EmbFile is not ok
TEST_F(EmbFileTest_1132, StreamReturnsNullWhenNotOk_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_EQ(embFile.stream(), nullptr);
}

// Test that size returns a value (likely -1 or 0 for invalid)
TEST_F(EmbFileTest_1132, SizeWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // For an invalid EmbFile, size should be some default (likely -1)
    int sz = embFile.size();
    EXPECT_LE(sz, 0);
}

// Test that modDate returns nullptr for invalid EmbFile
TEST_F(EmbFileTest_1132, ModDateWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_EQ(embFile.modDate(), nullptr);
}

// Test that createDate returns nullptr for invalid EmbFile
TEST_F(EmbFileTest_1132, CreateDateWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_EQ(embFile.createDate(), nullptr);
}

// Test that checksum returns nullptr for invalid EmbFile
TEST_F(EmbFileTest_1132, ChecksumWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_EQ(embFile.checksum(), nullptr);
}

// Test that mimeType returns nullptr for invalid EmbFile
TEST_F(EmbFileTest_1132, MimeTypeWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_EQ(embFile.mimeType(), nullptr);
}

// Test that streamObject returns a pointer to the internal object
TEST_F(EmbFileTest_1132, StreamObjectReturnsNonNull_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // streamObject should always return a pointer to the internal object
    Object *objPtr = embFile.streamObject();
    EXPECT_NE(objPtr, nullptr);
}

// Test constructing with error object
TEST_F(EmbFileTest_1132, ConstructWithErrorObject_IsNotOk_1132) {
    Object errObj = Object::error();
    EmbFile embFile(std::move(errObj));
    EXPECT_FALSE(embFile.isOk());
    EXPECT_EQ(embFile.stream(), nullptr);
}

// Test constructing with EOF object
TEST_F(EmbFileTest_1132, ConstructWithEofObject_IsNotOk_1132) {
    Object eofObj = Object::eof();
    EmbFile embFile(std::move(eofObj));
    EXPECT_FALSE(embFile.isOk());
    EXPECT_EQ(embFile.stream(), nullptr);
}

// Test constructing with an integer object (not a stream)
TEST_F(EmbFileTest_1132, ConstructWithIntObject_IsNotOk_1132) {
    Object intObj(42);
    EmbFile embFile(std::move(intObj));
    EXPECT_FALSE(embFile.isOk());
    EXPECT_EQ(embFile.stream(), nullptr);
}

// Test that save fails for invalid EmbFile (empty path)
TEST_F(EmbFileTest_1132, SaveFailsWithInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    EXPECT_FALSE(embFile.save(""));
}

// Test that save fails for invalid EmbFile with valid-looking path
TEST_F(EmbFileTest_1132, SaveFailsWithInvalidObjectValidPath_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    // Even with a valid path string, saving should fail if the object is invalid
    EXPECT_FALSE(embFile.save("/tmp/test_embfile_1132_output.bin"));
}

// Test constructing with boolean object (not a stream)
TEST_F(EmbFileTest_1132, ConstructWithBoolObject_IsNotOk_1132) {
    Object boolObj(true);
    EmbFile embFile(std::move(boolObj));
    EXPECT_FALSE(embFile.isOk());
}

// Test constructing with double object (not a stream)
TEST_F(EmbFileTest_1132, ConstructWithDoubleObject_IsNotOk_1132) {
    Object realObj(3.14);
    EmbFile embFile(std::move(realObj));
    EXPECT_FALSE(embFile.isOk());
    EXPECT_EQ(embFile.stream(), nullptr);
}

// Test that multiple accessors return consistent defaults for invalid object
TEST_F(EmbFileTest_1132, ConsistentDefaultsForInvalidObject_1132) {
    Object nullObj = Object::null();
    EmbFile embFile(std::move(nullObj));
    
    EXPECT_FALSE(embFile.isOk());
    EXPECT_EQ(embFile.stream(), nullptr);
    EXPECT_EQ(embFile.modDate(), nullptr);
    EXPECT_EQ(embFile.createDate(), nullptr);
    EXPECT_EQ(embFile.checksum(), nullptr);
    EXPECT_EQ(embFile.mimeType(), nullptr);
    EXPECT_LE(embFile.size(), 0);
}
