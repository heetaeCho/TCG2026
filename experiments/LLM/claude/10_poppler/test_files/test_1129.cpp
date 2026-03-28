#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "Stream.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "Dict.h"

class EmbFileTest_1129 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create an EmbFile from an empty/invalid stream object
static std::unique_ptr<EmbFile> createEmbFileFromNullObj() {
    Object obj;
    return std::make_unique<EmbFile>(std::move(obj));
}

// Test that creating an EmbFile from a null/invalid Object does not crash
TEST_F(EmbFileTest_1129, ConstructFromNullObject_1129) {
    Object obj;
    EXPECT_NO_THROW({
        EmbFile embFile(std::move(obj));
    });
}

// Test that checksum() returns nullptr when constructed from invalid object
TEST_F(EmbFileTest_1129, ChecksumReturnsNullForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    const GooString *cs = embFile->checksum();
    // For an invalid/empty object, checksum is expected to be null
    EXPECT_EQ(cs, nullptr);
}

// Test that createDate() returns nullptr for invalid object
TEST_F(EmbFileTest_1129, CreateDateReturnsNullForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    const GooString *cd = embFile->createDate();
    EXPECT_EQ(cd, nullptr);
}

// Test that modDate() returns nullptr for invalid object
TEST_F(EmbFileTest_1129, ModDateReturnsNullForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    const GooString *md = embFile->modDate();
    EXPECT_EQ(md, nullptr);
}

// Test that mimeType() returns nullptr for invalid object
TEST_F(EmbFileTest_1129, MimeTypeReturnsNullForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    const GooString *mt = embFile->mimeType();
    EXPECT_EQ(mt, nullptr);
}

// Test that size() returns a reasonable value (likely -1 or 0) for invalid object
TEST_F(EmbFileTest_1129, SizeForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    int sz = embFile->size();
    // For an invalid object, size is typically -1
    EXPECT_LE(sz, 0);
}

// Test that isOk() returns false for an invalid object
TEST_F(EmbFileTest_1129, IsOkReturnsFalseForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    EXPECT_FALSE(embFile->isOk());
}

// Test that streamObject() returns a non-null pointer (it returns address of internal member)
TEST_F(EmbFileTest_1129, StreamObjectReturnsNonNullPointer_1129) {
    auto embFile = createEmbFileFromNullObj();
    Object *obj = embFile->streamObject();
    EXPECT_NE(obj, nullptr);
}

// Test that stream() returns nullptr for invalid object
TEST_F(EmbFileTest_1129, StreamReturnsNullForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    Stream *s = embFile->stream();
    // For a non-stream object, stream() likely returns nullptr
    EXPECT_EQ(s, nullptr);
}

// Test that EmbFile is not copyable (compile-time check is implicit; 
// we verify that the deleted copy constructor and assignment are respected)
TEST_F(EmbFileTest_1129, EmbFileIsNotCopyable_1129) {
    EXPECT_FALSE(std::is_copy_constructible<EmbFile>::value);
    EXPECT_FALSE(std::is_copy_assignable<EmbFile>::value);
}

// Test that save returns false for invalid embedded file
TEST_F(EmbFileTest_1129, SaveReturnsFalseForInvalidObject_1129) {
    auto embFile = createEmbFileFromNullObj();
    // Attempt to save to a temp path; should fail since object is invalid
    std::string tempPath = "/tmp/embfile_test_1129_output.bin";
    bool result = embFile->save(tempPath);
    EXPECT_FALSE(result);
    // Clean up in case it did create a file
    std::remove(tempPath.c_str());
}

// Test constructing EmbFile with a proper stream object containing params
TEST_F(EmbFileTest_1129, ConstructFromStreamWithParams_1129) {
    // Create a dictionary with embedded file parameters
    auto paramsDict = Object(new Dict(nullptr));
    paramsDict.dictSet("Size", Object(42));
    paramsDict.dictSet("CheckSum", Object(new GooString("abc123")));
    paramsDict.dictSet("CreationDate", Object(new GooString("D:20230101")));
    paramsDict.dictSet("ModDate", Object(new GooString("D:20230601")));

    // Create a minimal MemStream
    static const char data[] = "test data";
    Object streamDict(new Dict(nullptr));
    streamDict.dictSet("Length", Object(static_cast<int>(sizeof(data) - 1)));
    streamDict.dictSet("Params", std::move(paramsDict));
    streamDict.dictSet("Subtype", Object(new GooString("application/octet-stream")));

    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, sizeof(data) - 1, std::move(streamDict));
    Object streamObj(static_cast<Stream *>(memStream));

    EmbFile embFile(std::move(streamObj));

    // Verify that the embedded file parsed the parameters
    EXPECT_EQ(embFile.size(), 42);

    if (embFile.checksum() != nullptr) {
        EXPECT_EQ(embFile.checksum()->toStr(), "abc123");
    }

    if (embFile.createDate() != nullptr) {
        EXPECT_EQ(embFile.createDate()->toStr(), "D:20230101");
    }

    if (embFile.modDate() != nullptr) {
        EXPECT_EQ(embFile.modDate()->toStr(), "D:20230601");
    }
}

// Test that multiple calls to checksum() return the same pointer (consistency)
TEST_F(EmbFileTest_1129, ChecksumConsistentAcrossCalls_1129) {
    auto embFile = createEmbFileFromNullObj();
    const GooString *cs1 = embFile->checksum();
    const GooString *cs2 = embFile->checksum();
    EXPECT_EQ(cs1, cs2);
}

// Test that multiple calls to size() return consistent results
TEST_F(EmbFileTest_1129, SizeConsistentAcrossCalls_1129) {
    auto embFile = createEmbFileFromNullObj();
    int sz1 = embFile->size();
    int sz2 = embFile->size();
    EXPECT_EQ(sz1, sz2);
}
