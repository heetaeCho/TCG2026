// File: ./TestProjects/tinyxml2/test_xmlutil_setboolserialization_161.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace {

class XMLUtilSetBoolSerializationTest_161 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure a known starting state for each test.
        tinyxml2::XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }

    void TearDown() override {
        // Restore defaults so tests don't leak global/static configuration.
        tinyxml2::XMLUtil::SetBoolSerialization(nullptr, nullptr);
    }

    static std::string ToBoolString(bool v) {
        char buf[256] = {0};
        tinyxml2::XMLUtil::ToStr(v, buf, static_cast<int>(sizeof(buf)));
        return std::string(buf);
    }

    static std::string ToBoolStringWithBuffer(bool v, int bufferSize) {
        // Create a buffer larger than bufferSize, but pass bufferSize to ToStr.
        // This helps us observe what ToStr writes without relying on internals.
        char buf[512];
        std::memset(buf, 0, sizeof(buf));
        tinyxml2::XMLUtil::ToStr(v, buf, bufferSize);
        return std::string(buf);
    }
};

TEST_F(XMLUtilSetBoolSerializationTest_161, DefaultSerializationProducesTrueFalse_161) {
    // Force defaults (also validates nullptr handling on both args).
    tinyxml2::XMLUtil::SetBoolSerialization(nullptr, nullptr);

    EXPECT_EQ(ToBoolString(true), "true");
    EXPECT_EQ(ToBoolString(false), "false");
}

TEST_F(XMLUtilSetBoolSerializationTest_161, CustomSerializationChangesToStrOutput_161) {
    tinyxml2::XMLUtil::SetBoolSerialization("YES", "NO");

    EXPECT_EQ(ToBoolString(true), "YES");
    EXPECT_EQ(ToBoolString(false), "NO");
}

TEST_F(XMLUtilSetBoolSerializationTest_161, NullTrueUsesDefaultTrueButCustomFalse_161) {
    tinyxml2::XMLUtil::SetBoolSerialization(nullptr, "N");

    EXPECT_EQ(ToBoolString(true), "true");   // default true
    EXPECT_EQ(ToBoolString(false), "N");     // custom false
}

TEST_F(XMLUtilSetBoolSerializationTest_161, CustomTrueButNullFalseUsesDefaultFalse_161) {
    tinyxml2::XMLUtil::SetBoolSerialization("Y", nullptr);

    EXPECT_EQ(ToBoolString(true), "Y");        // custom true
    EXPECT_EQ(ToBoolString(false), "false");   // default false
}

TEST_F(XMLUtilSetBoolSerializationTest_161, EmptyStringsAreAcceptedAsSerializationTokens_161) {
    tinyxml2::XMLUtil::SetBoolSerialization("", "");

    EXPECT_EQ(ToBoolString(true), "");
    EXPECT_EQ(ToBoolString(false), "");
}

TEST_F(XMLUtilSetBoolSerializationTest_161, LongCustomStringsAreReflectedWhenBufferIsLargeEnough_161) {
    const std::string t(120, 'T');
    const std::string f(110, 'F');

    tinyxml2::XMLUtil::SetBoolSerialization(t.c_str(), f.c_str());

    EXPECT_EQ(ToBoolString(true), t);
    EXPECT_EQ(ToBoolString(false), f);
}

TEST_F(XMLUtilSetBoolSerializationTest_161, ChangingSerializationMultipleTimesTakesEffectImmediately_161) {
    tinyxml2::XMLUtil::SetBoolSerialization("ON", "OFF");
    EXPECT_EQ(ToBoolString(true), "ON");
    EXPECT_EQ(ToBoolString(false), "OFF");

    tinyxml2::XMLUtil::SetBoolSerialization("1", "0");
    EXPECT_EQ(ToBoolString(true), "1");
    EXPECT_EQ(ToBoolString(false), "0");

    // Reset to defaults and verify.
    tinyxml2::XMLUtil::SetBoolSerialization(nullptr, nullptr);
    EXPECT_EQ(ToBoolString(true), "true");
    EXPECT_EQ(ToBoolString(false), "false");
}

TEST_F(XMLUtilSetBoolSerializationTest_161, ToStrHonorsSerializationEvenWithSmallerBufferSizes_161) {
    // Observable/error-ish case: ensure the call works with smaller buffers and
    // still reflects the chosen serialization (possibly truncated by implementation).
    tinyxml2::XMLUtil::SetBoolSerialization("TRUE_TOKEN", "FALSE_TOKEN");

    const std::string outTrue = ToBoolStringWithBuffer(true, 5);
    const std::string outFalse = ToBoolStringWithBuffer(false, 6);

    // We do NOT assume exact truncation rules, but we can assert the output
    // is a prefix of the configured token when the buffer is small.
    EXPECT_TRUE(std::string("TRUE_TOKEN").rfind(outTrue, 0) == 0);   // prefix
    EXPECT_TRUE(std::string("FALSE_TOKEN").rfind(outFalse, 0) == 0); // prefix
}

} // namespace
