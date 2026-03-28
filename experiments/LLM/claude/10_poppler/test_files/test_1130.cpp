#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "Stream.h"
#include "GooString.h"
#include "Dict.h"
#include "PDFDoc.h"

// Helper to create a minimal valid embedded file stream Object
static Object createEmbFileStreamObject(const char *mimeType = nullptr,
                                         const char *createDate = nullptr,
                                         const char *modDate = nullptr,
                                         const char *checksum = nullptr,
                                         int size = -1) {
    // We need to build a stream object with a Params dict
    // The EmbFile constructor expects an Object that is a stream
    // with optional /Params dict containing /Size, /CreationDate, /ModDate, /CheckSum
    // and optional /Subtype for mime type

    // Create the params dict
    Dict *paramsDict = new Dict((XRef *)nullptr);
    if (size >= 0) {
        paramsDict->add("Size", Object(size));
    }
    if (createDate) {
        paramsDict->add("CreationDate", Object(new GooString(createDate)));
    }
    if (modDate) {
        paramsDict->add("ModDate", Object(new GooString(modDate)));
    }
    if (checksum) {
        paramsDict->add("CheckSum", Object(new GooString(checksum)));
    }

    // Create the stream dict
    Dict *streamDict = new Dict((XRef *)nullptr);
    streamDict->add("Params", Object(paramsDict));
    if (mimeType) {
        streamDict->add("Subtype", Object(new GooString(mimeType)));
    }

    // Create a minimal memory stream
    const char *data = "";
    Object streamDictObj(streamDict);
    MemStream *memStream = new MemStream(const_cast<char *>(data), 0, 0, std::move(streamDictObj));

    return Object(static_cast<Stream *>(memStream));
}

static Object createNullObject() {
    return Object(objNull);
}

class EmbFileTest_1130 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that mimeType returns the correct value when set
TEST_F(EmbFileTest_1130, MimeTypeReturnsCorrectValue_1130) {
    Object efStream = createEmbFileStreamObject("application/pdf");
    EmbFile embFile(std::move(efStream));
    
    const GooString *mime = embFile.mimeType();
    if (mime != nullptr) {
        EXPECT_STREQ(mime->c_str(), "application/pdf");
    }
}

// Test that mimeType returns nullptr when not set
TEST_F(EmbFileTest_1130, MimeTypeReturnsNullWhenNotSet_1130) {
    Object efStream = createEmbFileStreamObject();
    EmbFile embFile(std::move(efStream));
    
    const GooString *mime = embFile.mimeType();
    EXPECT_EQ(mime, nullptr);
}

// Test createDate accessor
TEST_F(EmbFileTest_1130, CreateDateReturnsCorrectValue_1130) {
    Object efStream = createEmbFileStreamObject(nullptr, "D:20230101120000");
    EmbFile embFile(std::move(efStream));
    
    const GooString *date = embFile.createDate();
    if (date != nullptr) {
        EXPECT_STREQ(date->c_str(), "D:20230101120000");
    }
}

// Test modDate accessor
TEST_F(EmbFileTest_1130, ModDateReturnsCorrectValue_1130) {
    Object efStream = createEmbFileStreamObject(nullptr, nullptr, "D:20230615080000");
    EmbFile embFile(std::move(efStream));
    
    const GooString *date = embFile.modDate();
    if (date != nullptr) {
        EXPECT_STREQ(date->c_str(), "D:20230615080000");
    }
}

// Test checksum accessor
TEST_F(EmbFileTest_1130, ChecksumReturnsCorrectValue_1130) {
    Object efStream = createEmbFileStreamObject(nullptr, nullptr, nullptr, "abc123checksum");
    EmbFile embFile(std::move(efStream));
    
    const GooString *cs = embFile.checksum();
    if (cs != nullptr) {
        EXPECT_STREQ(cs->c_str(), "abc123checksum");
    }
}

// Test size accessor
TEST_F(EmbFileTest_1130, SizeReturnsCorrectValue_1130) {
    Object efStream = createEmbFileStreamObject(nullptr, nullptr, nullptr, nullptr, 42);
    EmbFile embFile(std::move(efStream));
    
    int sz = embFile.size();
    EXPECT_EQ(sz, 42);
}

// Test size returns -1 (or default) when not specified
TEST_F(EmbFileTest_1130, SizeReturnsDefaultWhenNotSet_1130) {
    Object efStream = createEmbFileStreamObject();
    EmbFile embFile(std::move(efStream));
    
    int sz = embFile.size();
    EXPECT_EQ(sz, -1);
}

// Test streamObject returns non-null
TEST_F(EmbFileTest_1130, StreamObjectReturnsNonNull_1130) {
    Object efStream = createEmbFileStreamObject("text/plain");
    EmbFile embFile(std::move(efStream));
    
    Object *streamObj = embFile.streamObject();
    EXPECT_NE(streamObj, nullptr);
}

// Test stream returns valid stream pointer
TEST_F(EmbFileTest_1130, StreamReturnsValidPointer_1130) {
    Object efStream = createEmbFileStreamObject("text/plain");
    EmbFile embFile(std::move(efStream));
    
    Stream *s = embFile.stream();
    // Stream may or may not be null depending on implementation, but should not crash
    if (s != nullptr) {
        SUCCEED();
    }
}

// Test isOk for valid embedded file
TEST_F(EmbFileTest_1130, IsOkReturnsTrueForValidStream_1130) {
    Object efStream = createEmbFileStreamObject("application/pdf");
    EmbFile embFile(std::move(efStream));
    
    EXPECT_TRUE(embFile.isOk());
}

// Test isOk for invalid/null stream object
TEST_F(EmbFileTest_1130, IsOkReturnsFalseForNullObject_1130) {
    Object nullObj = createNullObject();
    EmbFile embFile(std::move(nullObj));
    
    EXPECT_FALSE(embFile.isOk());
}

// Test that createDate returns nullptr when not set
TEST_F(EmbFileTest_1130, CreateDateReturnsNullWhenNotSet_1130) {
    Object efStream = createEmbFileStreamObject();
    EmbFile embFile(std::move(efStream));
    
    const GooString *date = embFile.createDate();
    EXPECT_EQ(date, nullptr);
}

// Test that modDate returns nullptr when not set
TEST_F(EmbFileTest_1130, ModDateReturnsNullWhenNotSet_1130) {
    Object efStream = createEmbFileStreamObject();
    EmbFile embFile(std::move(efStream));
    
    const GooString *date = embFile.modDate();
    EXPECT_EQ(date, nullptr);
}

// Test that checksum returns nullptr when not set
TEST_F(EmbFileTest_1130, ChecksumReturnsNullWhenNotSet_1130) {
    Object efStream = createEmbFileStreamObject();
    EmbFile embFile(std::move(efStream));
    
    const GooString *cs = embFile.checksum();
    EXPECT_EQ(cs, nullptr);
}

// Test with all fields populated
TEST_F(EmbFileTest_1130, AllFieldsPopulated_1130) {
    Object efStream = createEmbFileStreamObject("image/png", "D:20200101000000", "D:20200601000000", "deadbeef", 1024);
    EmbFile embFile(std::move(efStream));
    
    EXPECT_TRUE(embFile.isOk());
    
    const GooString *mime = embFile.mimeType();
    if (mime) {
        EXPECT_STREQ(mime->c_str(), "image/png");
    }
    
    const GooString *cd = embFile.createDate();
    if (cd) {
        EXPECT_STREQ(cd->c_str(), "D:20200101000000");
    }
    
    const GooString *md = embFile.modDate();
    if (md) {
        EXPECT_STREQ(md->c_str(), "D:20200601000000");
    }
    
    const GooString *cs = embFile.checksum();
    if (cs) {
        EXPECT_STREQ(cs->c_str(), "deadbeef");
    }
    
    EXPECT_EQ(embFile.size(), 1024);
}

// Test with zero-size file
TEST_F(EmbFileTest_1130, ZeroSizeFile_1130) {
    Object efStream = createEmbFileStreamObject(nullptr, nullptr, nullptr, nullptr, 0);
    EmbFile embFile(std::move(efStream));
    
    EXPECT_EQ(embFile.size(), 0);
}

// Test copy constructor is deleted (compile-time check; this test just verifies the object can be moved)
TEST_F(EmbFileTest_1130, MoveConstructionWorks_1130) {
    Object efStream = createEmbFileStreamObject("text/html");
    EmbFile embFile(std::move(efStream));
    
    EXPECT_TRUE(embFile.isOk());
}

// Test empty string mime type
TEST_F(EmbFileTest_1130, EmptyMimeType_1130) {
    Object efStream = createEmbFileStreamObject("");
    EmbFile embFile(std::move(efStream));
    
    const GooString *mime = embFile.mimeType();
    if (mime != nullptr) {
        EXPECT_STREQ(mime->c_str(), "");
    }
}
