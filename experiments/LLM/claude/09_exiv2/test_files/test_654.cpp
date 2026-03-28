#include <gtest/gtest.h>
#include "exiv2/types.hpp"

// Include the .cpp to access the static function
// This is necessary because ignoreList has internal linkage (static)
#include "quicktimevideo.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class IgnoreListTest_654 : public ::testing::Test {
protected:
    DataBuf makeDataBuf(const char* tag, size_t size = 4) {
        return DataBuf(reinterpret_cast<const byte*>(tag), size);
    }
};

// Test each tag in the ignore list returns true
TEST_F(IgnoreListTest_654, MdatIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("mdat");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, EdtsIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("edts");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, JunkIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("junk");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, IodsIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("iods");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, AlisIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("alis");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, StscIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stsc");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, StszIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stsz");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, StcoIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stco");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, CttsIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("ctts");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, StssIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stss");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, SkipIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("skip");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, WideIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("wide");
    EXPECT_TRUE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, CmvdIsInIgnoreList_654) {
    DataBuf buf = makeDataBuf("cmvd");
    EXPECT_TRUE(ignoreList(buf));
}

// Test tags NOT in the ignore list return false
TEST_F(IgnoreListTest_654, MoovIsNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("moov");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, TrakIsNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("trak");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, FtypIsNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("ftyp");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, UdtaIsNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("udta");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, EmptyStringIsNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("\0\0\0\0");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, RandomBytesNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("abcd");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, PartialMatchNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("mda\0");
    EXPECT_FALSE(ignoreList(buf));
}

// Test case sensitivity - uppercase should not match
TEST_F(IgnoreListTest_654, UppercaseMDATNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("MDAT");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, MixedCaseNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("Mdat");
    EXPECT_FALSE(ignoreList(buf));
}

// Test with buffer containing more data (tag at the beginning)
TEST_F(IgnoreListTest_654, LargerBufferWithMdatTag_654) {
    const char data[] = "mdatextradata";
    DataBuf buf(reinterpret_cast<const byte*>(data), sizeof(data) - 1);
    EXPECT_TRUE(ignoreList(buf));
}

// Test similar but different tags
TEST_F(IgnoreListTest_654, SimilarTagStsdNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stsd");
    EXPECT_FALSE(ignoreList(buf));
}

TEST_F(IgnoreListTest_654, SimilarTagStblNotInIgnoreList_654) {
    DataBuf buf = makeDataBuf("stbl");
    EXPECT_FALSE(ignoreList(buf));
}
