#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "Stream.h"
#include "GooString.h"
#include "Dict.h"
#include "PDFDoc.h"

class EmbFileTest_1126 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test creating EmbFile with a null/empty object stream
TEST_F(EmbFileTest_1126, ConstructWithNullStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    // When constructed with invalid/null stream, isOk should return false
    EXPECT_FALSE(embFile.isOk());
}

// Test that size returns a value (likely -1 or 0 for invalid stream)
TEST_F(EmbFileTest_1126, SizeWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    int sz = embFile.size();
    // For an invalid stream, size is likely -1 or 0
    EXPECT_TRUE(sz == -1 || sz == 0);
}

// Test that modDate returns nullptr for an invalid/empty stream
TEST_F(EmbFileTest_1126, ModDateWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *md = embFile.modDate();
    // With no valid params dict, modDate should be nullptr
    EXPECT_EQ(md, nullptr);
}

// Test that createDate returns nullptr for an invalid/empty stream
TEST_F(EmbFileTest_1126, CreateDateWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *cd = embFile.createDate();
    EXPECT_EQ(cd, nullptr);
}

// Test that checksum returns nullptr for an invalid/empty stream
TEST_F(EmbFileTest_1126, ChecksumWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *cs = embFile.checksum();
    EXPECT_EQ(cs, nullptr);
}

// Test that mimeType returns nullptr for an invalid/empty stream
TEST_F(EmbFileTest_1126, MimeTypeWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    const GooString *mt = embFile.mimeType();
    EXPECT_EQ(mt, nullptr);
}

// Test that streamObject returns a non-null pointer (it should return address of internal object)
TEST_F(EmbFileTest_1126, StreamObjectReturnsNonNull_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    Object *streamObj = embFile.streamObject();
    EXPECT_NE(streamObj, nullptr);
}

// Test that stream returns nullptr for invalid embedded file
TEST_F(EmbFileTest_1126, StreamWithInvalidObject_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    Stream *s = embFile.stream();
    // For an invalid/non-stream object, stream() should return nullptr
    EXPECT_EQ(s, nullptr);
}

// Test that save fails for an invalid embedded file
TEST_F(EmbFileTest_1126, SaveFailsWithInvalidStream_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("/tmp/embfile_test_invalid_1126.bin");
    EXPECT_FALSE(result);
}

// Test that save fails with empty path
TEST_F(EmbFileTest_1126, SaveFailsWithEmptyPath_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    bool result = embFile.save("");
    EXPECT_FALSE(result);
}

// Test that EmbFile is not copyable (compile-time check - this test just verifies the interface contract)
TEST_F(EmbFileTest_1126, NotCopyable_1126) {
    EXPECT_FALSE(std::is_copy_constructible<EmbFile>::value);
    EXPECT_FALSE(std::is_copy_assignable<EmbFile>::value);
}

// Test size() const method returns int type
TEST_F(EmbFileTest_1126, SizeReturnsInt_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    // Verify the return type is int through compilation
    int sz = embFile.size();
    (void)sz; // suppress unused warning
    SUCCEED();
}

// Test that isOk is consistent with stream validity
TEST_F(EmbFileTest_1126, IsOkConsistencyCheck_1126) {
    Object obj;
    EmbFile embFile(std::move(obj));
    bool ok = embFile.isOk();
    Stream *s = embFile.stream();
    // If not ok, stream should be nullptr
    if (!ok) {
        EXPECT_EQ(s, nullptr);
    }
}
