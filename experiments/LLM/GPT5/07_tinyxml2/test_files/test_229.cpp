// TEST_ID: 229
#include <climits>
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class UnsignedAttributeTest_229 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertFirstChild(elem);
    }
};

TEST_F(UnsignedAttributeTest_229, MissingAttributeReturnsDefault_229) {
    const unsigned defaultValue = 42u;
    EXPECT_EQ(elem->UnsignedAttribute("missing", defaultValue), defaultValue);
}

TEST_F(UnsignedAttributeTest_229, ExistingUnsignedReturnsValue_229) {
    elem->SetAttribute("a", 123u);
    EXPECT_EQ(elem->UnsignedAttribute("a", 999u), 123u);
}

TEST_F(UnsignedAttributeTest_229, BoundaryValuesZeroAndUintMax_229) {
    elem->SetAttribute("zero", 0u);
    elem->SetAttribute("max", UINT_MAX);

    EXPECT_EQ(elem->UnsignedAttribute("zero", 7u), 0u);
    EXPECT_EQ(elem->UnsignedAttribute("max", 7u), UINT_MAX);
}

TEST_F(UnsignedAttributeTest_229, NegativeStringValueReturnsDefault_229) {
    // Use string overload to ensure a negative textual value is stored.
    elem->SetAttribute("neg", "-1");

    const unsigned defaultValue = 77u;
    EXPECT_EQ(elem->UnsignedAttribute("neg", defaultValue), defaultValue);
}

TEST_F(UnsignedAttributeTest_229, NonNumericStringReturnsDefault_229) {
    elem->SetAttribute("str", "abc");

    const unsigned defaultValue = 88u;
    EXPECT_EQ(elem->UnsignedAttribute("str", defaultValue), defaultValue);
}

TEST_F(UnsignedAttributeTest_229, NullNameIsHandledOrCrashesPredictably_229) {
    // Behavior depends on the library's contract (may assert/crash on nullptr).
    // This test verifies the observable behavior in builds where death tests are supported.
#if GTEST_HAS_DEATH_TEST
    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)elem->UnsignedAttribute(nullptr, 1u);
        },
        ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}
