#include <gtest/gtest.h>
#include <cstring>

// Reconstruct the minimal types needed based on the provided interface

namespace Exiv2 {
namespace Internal {

struct NikonArrayIdx {
    struct Key {
        int tag_;
        const char* ver_;
        int size_;
    };

    int tag_;
    const char* ver_;
    int size_;
    int idx_;

    bool operator==(const Key& key) const {
        return key.tag_ == tag_ && 0 == strncmp(key.ver_, ver_, strlen(ver_)) && (size_ == 0 || key.size_ == size_);
    }
};

}  // namespace Internal
}  // namespace Exiv2

using Exiv2::Internal::NikonArrayIdx;

class NikonArrayIdxTest_1535 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Exact match on tag, version, and size
TEST_F(NikonArrayIdxTest_1535, ExactMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 50;

    EXPECT_TRUE(idx == key);
}

// Test: Tag mismatch should return false
TEST_F(NikonArrayIdxTest_1535, TagMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 200;
    key.ver_ = "0210";
    key.size_ = 50;

    EXPECT_FALSE(idx == key);
}

// Test: Version mismatch should return false
TEST_F(NikonArrayIdxTest_1535, VersionMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0300";
    key.size_ = 50;

    EXPECT_FALSE(idx == key);
}

// Test: Size mismatch with non-zero idx size should return false
TEST_F(NikonArrayIdxTest_1535, SizeMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 60;

    EXPECT_FALSE(idx == key);
}

// Test: When idx size_ is 0, any key size should match (wildcard)
TEST_F(NikonArrayIdxTest_1535, SizeZeroWildcard_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 999;

    EXPECT_TRUE(idx == key);
}

// Test: When idx size_ is 0, key size 0 should also match
TEST_F(NikonArrayIdxTest_1535, SizeZeroBothZero_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 0;

    EXPECT_TRUE(idx == key);
}

// Test: Version prefix matching - key version is longer but starts with idx version
TEST_F(NikonArrayIdxTest_1535, VersionPrefixMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "02";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 50;

    // strncmp compares only strlen(ver_) = 2 characters, "02" == "02" => true
    EXPECT_TRUE(idx == key);
}

// Test: Version prefix mismatch
TEST_F(NikonArrayIdxTest_1535, VersionPrefixMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "03";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "0210";
    key.size_ = 50;

    EXPECT_FALSE(idx == key);
}

// Test: Empty version string should match any key version
TEST_F(NikonArrayIdxTest_1535, EmptyVersionMatchesAny_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "anything";
    key.size_ = 42;

    // strlen("") == 0, strncmp with n=0 always returns 0
    EXPECT_TRUE(idx == key);
}

// Test: All fields match except tag (negative tag values)
TEST_F(NikonArrayIdxTest_1535, NegativeTagMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = -1;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = -1;
    key.ver_ = "0210";
    key.size_ = 50;

    EXPECT_TRUE(idx == key);
}

// Test: Tag zero match
TEST_F(NikonArrayIdxTest_1535, TagZeroMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 0;
    idx.ver_ = "0100";
    idx.size_ = 10;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 0;
    key.ver_ = "0100";
    key.size_ = 10;

    EXPECT_TRUE(idx == key);
}

// Test: Key version is shorter than idx version - strncmp uses strlen(idx.ver_)
TEST_F(NikonArrayIdxTest_1535, KeyVersionShorterThanIdxVersion_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 100;
    key.ver_ = "02";
    key.size_ = 50;

    // strncmp("02", "0210", 4) - compares up to 4 chars
    // "02\0" vs "0210" - at position 2, '\0' < '1', so strncmp != 0
    EXPECT_FALSE(idx == key);
}

// Test: Multiple conditions fail - both tag and version mismatch
TEST_F(NikonArrayIdxTest_1535, MultipleFieldsMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 100;
    idx.ver_ = "0210";
    idx.size_ = 50;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 200;
    key.ver_ = "0300";
    key.size_ = 60;

    EXPECT_FALSE(idx == key);
}

// Test: Size matches when both are the same non-zero value
TEST_F(NikonArrayIdxTest_1535, SizeExactNonZeroMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 5;
    idx.ver_ = "01";
    idx.size_ = 1;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 5;
    key.ver_ = "01";
    key.size_ = 1;

    EXPECT_TRUE(idx == key);
}

// Test: Single character version match
TEST_F(NikonArrayIdxTest_1535, SingleCharVersionMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 10;
    idx.ver_ = "A";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 10;
    key.ver_ = "ABC";
    key.size_ = 0;

    EXPECT_TRUE(idx == key);
}

// Test: Single character version mismatch
TEST_F(NikonArrayIdxTest_1535, SingleCharVersionMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 10;
    idx.ver_ = "B";
    idx.size_ = 0;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 10;
    key.ver_ = "ABC";
    key.size_ = 0;

    EXPECT_FALSE(idx == key);
}

// Test: Large size values
TEST_F(NikonArrayIdxTest_1535, LargeSizeMatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 1;
    idx.ver_ = "0100";
    idx.size_ = 1000000;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 1;
    key.ver_ = "0100";
    key.size_ = 1000000;

    EXPECT_TRUE(idx == key);
}

// Test: Large size mismatch
TEST_F(NikonArrayIdxTest_1535, LargeSizeMismatch_1535) {
    NikonArrayIdx idx;
    idx.tag_ = 1;
    idx.ver_ = "0100";
    idx.size_ = 1000000;
    idx.idx_ = 0;

    NikonArrayIdx::Key key;
    key.tag_ = 1;
    key.ver_ = "0100";
    key.size_ = 999999;

    EXPECT_FALSE(idx == key);
}
