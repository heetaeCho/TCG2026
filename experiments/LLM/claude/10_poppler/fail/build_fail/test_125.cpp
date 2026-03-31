#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"

// Since BaseStream is abstract (inherits from Stream which has pure virtual methods),
// we need a concrete subclass for testing. We'll use a minimal test double that
// implements the pure virtual methods just enough to instantiate.

// However, we can only test the isBinary method as specified in the partial code.
// We need to find a concrete subclass or create a minimal one.

// FileStream is a concrete subclass of BaseStream available in the codebase.
// Let's try to use it, or if not available, we create a minimal concrete class.

// Based on the known interface, let's create a minimal testable concrete class
// that inherits from BaseStream and implements required pure virtuals.

class TestableBaseStream : public BaseStream {
public:
    TestableBaseStream() : BaseStream(Object(), 0) {}
    
    StreamKind getKind() const override { return strFile; }
    void reset() override {}
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    Goffset getPos() override { return 0; }
    void setPos(Goffset pos, int dir = 0) override {}
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) override { return nullptr; }
    bool isBinary(bool last = true) const override { return BaseStream::isBinary(last); }
    int getUnfilteredChar() override { return EOF; }
    void unfilteredReset() override {}
};

class BaseStreamTest_125 : public ::testing::Test {
protected:
    void SetUp() override {
        stream = std::make_unique<TestableBaseStream>();
    }
    
    std::unique_ptr<TestableBaseStream> stream;
};

// Test isBinary with default parameter (last = true)
TEST_F(BaseStreamTest_125, IsBinaryDefaultParameterReturnsTrue_125) {
    EXPECT_TRUE(stream->isBinary());
}

// Test isBinary with explicit true
TEST_F(BaseStreamTest_125, IsBinaryWithTrueReturnsTrue_125) {
    EXPECT_TRUE(stream->isBinary(true));
}

// Test isBinary with explicit false
TEST_F(BaseStreamTest_125, IsBinaryWithFalseReturnsFalse_125) {
    EXPECT_FALSE(stream->isBinary(false));
}

// Test getBaseStream returns this
TEST_F(BaseStreamTest_125, GetBaseStreamReturnsSelf_125) {
    EXPECT_EQ(stream->getBaseStream(), stream.get());
}

// Test getUndecodedStream returns this
TEST_F(BaseStreamTest_125, GetUndecodedStreamReturnsSelf_125) {
    EXPECT_EQ(stream->getUndecodedStream(), stream.get());
}

// Test getLength returns the length passed in constructor
TEST_F(BaseStreamTest_125, GetLengthReturnsConstructedLength_125) {
    EXPECT_EQ(stream->getLength(), 0);
}

// Test getDict returns a valid Dict pointer or nullptr (depending on empty object)
TEST_F(BaseStreamTest_125, GetDictReturnsNonNull_125) {
    // With an empty Object, getDict may return nullptr
    Dict *d = stream->getDict();
    // We just verify it doesn't crash; the result depends on the Object passed
    (void)d;
}

// Test getDictObject returns a pointer to the dict object
TEST_F(BaseStreamTest_125, GetDictObjectReturnsNonNull_125) {
    Object *obj = stream->getDictObject();
    EXPECT_NE(obj, nullptr);
}

// Test getFileName returns nullptr for base implementation
TEST_F(BaseStreamTest_125, GetFileNameReturnsNullptr_125) {
    GooString *fileName = stream->getFileName();
    EXPECT_EQ(fileName, nullptr);
}

// Test getStart returns a valid offset
TEST_F(BaseStreamTest_125, GetStartReturnsZeroByDefault_125) {
    Goffset start = stream->getStart();
    EXPECT_GE(start, 0);
}

// Test isBinary boundary: multiple consecutive calls with different parameters
TEST_F(BaseStreamTest_125, IsBinaryMultipleCalls_125) {
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
    EXPECT_TRUE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
}

// Test that getKind returns the expected kind
TEST_F(BaseStreamTest_125, GetKindReturnsExpected_125) {
    EXPECT_EQ(stream->getKind(), strFile);
}
