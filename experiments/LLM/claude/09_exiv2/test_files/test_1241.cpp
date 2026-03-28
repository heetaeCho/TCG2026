#include <gtest/gtest.h>
#include <string>

// Include the header for XmpNsInfo
#include "exiv2/properties.hpp"

using namespace Exiv2;

// Test fixture for XmpNsInfo tests
class XmpNsInfoTest_1241 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: operator== with Prefix returns true when prefixes match
TEST_F(XmpNsInfoTest_1241, PrefixEqualityMatchingPrefix_1241) {
    XmpNsInfo info;
    info.prefix_ = "dc";
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "dc";

    EXPECT_TRUE(info == prefix);
}

// Test: operator== with Prefix returns false when prefixes do not match
TEST_F(XmpNsInfoTest_1241, PrefixEqualityNonMatchingPrefix_1241) {
    XmpNsInfo info;
    info.prefix_ = "dc";
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "xmp";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Prefix - empty prefix matches empty info prefix
TEST_F(XmpNsInfoTest_1241, PrefixEqualityBothEmpty_1241) {
    XmpNsInfo info;
    info.prefix_ = "";
    info.ns_ = "";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "";

    EXPECT_TRUE(info == prefix);
}

// Test: operator== with Prefix - empty prefix does not match non-empty info prefix
TEST_F(XmpNsInfoTest_1241, PrefixEqualityEmptyPrefixVsNonEmpty_1241) {
    XmpNsInfo info;
    info.prefix_ = "dc";
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Prefix - non-empty prefix does not match empty info prefix
TEST_F(XmpNsInfoTest_1241, PrefixEqualityNonEmptyPrefixVsEmpty_1241) {
    XmpNsInfo info;
    info.prefix_ = "";
    info.ns_ = "";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "dc";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Prefix - case sensitivity check
TEST_F(XmpNsInfoTest_1241, PrefixEqualityCaseSensitive_1241) {
    XmpNsInfo info;
    info.prefix_ = "dc";
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "DC";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Prefix - similar but different prefixes
TEST_F(XmpNsInfoTest_1241, PrefixEqualitySimilarButDifferent_1241) {
    XmpNsInfo info;
    info.prefix_ = "xmp";
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "xmpMM";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Prefix - prefix is a substring of info prefix
TEST_F(XmpNsInfoTest_1241, PrefixEqualitySubstringPrefix_1241) {
    XmpNsInfo info;
    info.prefix_ = "xmpMM";
    info.ns_ = "http://ns.adobe.com/xap/1.0/mm/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "xmp";

    EXPECT_FALSE(info == prefix);
}

// Test: operator== with Ns returns true when namespaces match
TEST_F(XmpNsInfoTest_1241, NsEqualityMatchingNs_1241) {
    XmpNsInfo info;
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.prefix_ = "dc";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://purl.org/dc/elements/1.1/";

    EXPECT_TRUE(info == ns);
}

// Test: operator== with Ns returns false when namespaces do not match
TEST_F(XmpNsInfoTest_1241, NsEqualityNonMatchingNs_1241) {
    XmpNsInfo info;
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.prefix_ = "dc";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/xap/1.0/";

    EXPECT_FALSE(info == ns);
}

// Test: operator== with Prefix - long prefix string matching
TEST_F(XmpNsInfoTest_1241, PrefixEqualityLongPrefix_1241) {
    XmpNsInfo info;
    info.prefix_ = "aVeryLongPrefixNameThatIsUnusuallyLong";
    info.ns_ = "http://example.com/ns/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "aVeryLongPrefixNameThatIsUnusuallyLong";

    EXPECT_TRUE(info == prefix);
}

// Test: operator== with Prefix - whitespace in prefix
TEST_F(XmpNsInfoTest_1241, PrefixEqualityWithWhitespace_1241) {
    XmpNsInfo info;
    info.prefix_ = "dc ";
    info.ns_ = "http://purl.org/dc/elements/1.1/";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "dc";

    EXPECT_FALSE(info == prefix);
}
