#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include "Object.h"
#include "GooString.h"

// Test fixture for BaseStream tests
class BaseStreamTest_130 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// A concrete subclass of BaseStream for testing purposes,
// since BaseStream has pure virtual methods from Stream
class TestableBaseStream : public BaseStream {
public:
    TestableBaseStream(Object &&dictA, Goffset lengthA)
        : BaseStream(std::move(dictA), lengthA) {}

    std::unique_ptr<BaseStream> copy() override {
        return nullptr;
    }

    std::unique_ptr<Stream> makeSubStream(Goffset start, bool limited, Goffset length, Object &&dict) override {
        return nullptr;
    }

    void setPos(Goffset pos, int dir) override {}

    Goffset getStart() override { return 0; }

    void moveStart(Goffset delta) override {}

    StreamKind getKind() const override { return strFile; }

    void reset() override {}

    int getChar() override { return EOF; }

    int lookChar() override { return EOF; }

    Goffset getPos() override { return 0; }

    GooString *getFileName() override { return nullptr; }

    int getUnfilteredChar() override { return EOF; }

    void unfilteredReset() override {}
};

// Test that getFileName returns nullptr by default
TEST_F(BaseStreamTest_130, GetFileNameReturnsNullptr_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 0);
    EXPECT_EQ(stream.getFileName(), nullptr);
}

// Test that getLength returns the length passed to constructor
TEST_F(BaseStreamTest_130, GetLengthReturnsConstructorValue_130) {
    Object dict;
    Goffset expectedLength = 1024;
    TestableBaseStream stream(std::move(dict), expectedLength);
    EXPECT_EQ(stream.getLength(), expectedLength);
}

// Test getLength with zero length
TEST_F(BaseStreamTest_130, GetLengthWithZero_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 0);
    EXPECT_EQ(stream.getLength(), 0);
}

// Test getLength with large value
TEST_F(BaseStreamTest_130, GetLengthWithLargeValue_130) {
    Object dict;
    Goffset largeLength = 1000000000LL;
    TestableBaseStream stream(std::move(dict), largeLength);
    EXPECT_EQ(stream.getLength(), largeLength);
}

// Test isBinary returns expected value
TEST_F(BaseStreamTest_130, IsBinaryReturnsTrue_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    // BaseStream::isBinary should return true for binary streams
    EXPECT_TRUE(stream.isBinary(true));
}

// Test isBinary with last=false
TEST_F(BaseStreamTest_130, IsBinaryWithLastFalse_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_TRUE(stream.isBinary(false));
}

// Test getBaseStream returns this
TEST_F(BaseStreamTest_130, GetBaseStreamReturnsSelf_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_EQ(stream.getBaseStream(), &stream);
}

// Test getUndecodedStream returns this
TEST_F(BaseStreamTest_130, GetUndecodedStreamReturnsSelf_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_EQ(stream.getUndecodedStream(), &stream);
}

// Test getDict returns dict pointer
TEST_F(BaseStreamTest_130, GetDictReturnsDict_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    // getDict may return nullptr if dict is not a dictionary type
    // We just verify it doesn't crash
    stream.getDict();
}

// Test getDictObject returns pointer to internal dict object
TEST_F(BaseStreamTest_130, GetDictObjectReturnsNonNull_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    Object *dictObj = stream.getDictObject();
    EXPECT_NE(dictObj, nullptr);
}

// Test copy returns nullptr in our test implementation
TEST_F(BaseStreamTest_130, CopyReturnsNullptr_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    auto copied = stream.copy();
    EXPECT_EQ(copied, nullptr);
}

// Test makeSubStream returns nullptr in our test implementation
TEST_F(BaseStreamTest_130, MakeSubStreamReturnsNullptr_130) {
    Object dict;
    Object subDict;
    TestableBaseStream stream(std::move(dict), 100);
    auto sub = stream.makeSubStream(0, false, 50, std::move(subDict));
    EXPECT_EQ(sub, nullptr);
}

// Test getStart returns 0 in our test implementation
TEST_F(BaseStreamTest_130, GetStartReturnsZero_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_EQ(stream.getStart(), 0);
}

// Test negative length
TEST_F(BaseStreamTest_130, GetLengthWithNegativeValue_130) {
    Object dict;
    Goffset negativeLength = -1;
    TestableBaseStream stream(std::move(dict), negativeLength);
    EXPECT_EQ(stream.getLength(), negativeLength);
}

// Test setPos doesn't crash
TEST_F(BaseStreamTest_130, SetPosDoesNotCrash_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_NO_FATAL_FAILURE(stream.setPos(0, 0));
    EXPECT_NO_FATAL_FAILURE(stream.setPos(50, 0));
    EXPECT_NO_FATAL_FAILURE(stream.setPos(0, -1));
}

// Test moveStart doesn't crash
TEST_F(BaseStreamTest_130, MoveStartDoesNotCrash_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 100);
    EXPECT_NO_FATAL_FAILURE(stream.moveStart(0));
    EXPECT_NO_FATAL_FAILURE(stream.moveStart(10));
}

// Test getFileName on base class default
TEST_F(BaseStreamTest_130, BaseClassGetFileNameDefault_130) {
    Object dict;
    TestableBaseStream stream(std::move(dict), 0);
    GooString *fileName = stream.getFileName();
    EXPECT_EQ(fileName, nullptr);
}
