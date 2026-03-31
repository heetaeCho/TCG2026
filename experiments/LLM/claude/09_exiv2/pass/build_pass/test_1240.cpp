#include <gtest/gtest.h>
#include <string>
#include "exiv2/properties.hpp"

using namespace Exiv2;

// Test fixture for XmpNsInfo
class XmpNsInfoTest_1240 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that operator== with Ns returns true when namespace strings match
TEST_F(XmpNsInfoTest_1240, NsEqualityMatchingNamespace_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/xap/1.0/";

    EXPECT_TRUE(info == ns);
}

// Test that operator== with Ns returns false when namespace strings do not match
TEST_F(XmpNsInfoTest_1240, NsEqualityNonMatchingNamespace_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/pdf/1.0/";

    EXPECT_FALSE(info == ns);
}

// Test that operator== with Ns returns false when Ns is empty and info ns_ is not
TEST_F(XmpNsInfoTest_1240, NsEqualityEmptyNsAgainstNonEmpty_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "";

    EXPECT_FALSE(info == ns);
}

// Test that operator== with Ns returns true when both are empty strings
TEST_F(XmpNsInfoTest_1240, NsEqualityBothEmpty_1240) {
    XmpNsInfo info;
    info.ns_ = "";
    info.prefix_ = "";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "";

    // ns_ is a const char* pointing to "", and ns.ns_ is std::string ""
    // The comparison is ns_ == ns.ns_, which compares const char* with std::string
    // std::string("") == "" should be true
    EXPECT_TRUE(info == ns);
}

// Test that operator== with Ns handles similar but different namespace strings
TEST_F(XmpNsInfoTest_1240, NsEqualitySimilarButDifferent_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/xap/1.0/";

    EXPECT_FALSE(info == ns);
}

// Test operator== with Ns where namespace differs only by case
TEST_F(XmpNsInfoTest_1240, NsEqualityCaseSensitive_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/XAP/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/xap/1.0/";

    EXPECT_FALSE(info == ns);
}

// Test operator== with Ns using a long namespace string
TEST_F(XmpNsInfoTest_1240, NsEqualityLongNamespace_1240) {
    std::string longNs(1000, 'a');
    XmpNsInfo info;
    info.ns_ = longNs.c_str();
    info.prefix_ = "test";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = longNs;

    EXPECT_TRUE(info == ns);
}

// Test operator== with Ns where one has trailing whitespace
TEST_F(XmpNsInfoTest_1240, NsEqualityTrailingWhitespace_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Ns ns;
    ns.ns_ = "http://ns.adobe.com/xap/1.0/ ";

    EXPECT_FALSE(info == ns);
}

// Test that operator== with Prefix returns true when prefix strings match
TEST_F(XmpNsInfoTest_1240, PrefixEqualityMatchingPrefix_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "xmp";

    EXPECT_TRUE(info == prefix);
}

// Test that operator== with Prefix returns false when prefix strings do not match
TEST_F(XmpNsInfoTest_1240, PrefixEqualityNonMatchingPrefix_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "dc";

    EXPECT_FALSE(info == prefix);
}

// Test that operator== with Prefix returns false when prefix is empty and info prefix_ is not
TEST_F(XmpNsInfoTest_1240, PrefixEqualityEmptyPrefixAgainstNonEmpty_1240) {
    XmpNsInfo info;
    info.ns_ = "http://ns.adobe.com/xap/1.0/";
    info.prefix_ = "xmp";
    info.xmpPropertyInfo_ = nullptr;

    XmpNsInfo::Prefix prefix;
    prefix.prefix_ = "";

    EXPECT_FALSE(info == prefix);
}
