// TEST_ID: 228
#include <climits>
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class IntAttributeTest_228 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }
};

}  // namespace

TEST_F(IntAttributeTest_228, ReturnsDefaultWhenAttributeMissing_228) {
    ASSERT_NE(elem_, nullptr);
    EXPECT_EQ(elem_->IntAttribute("missing", 123), 123);
}

TEST_F(IntAttributeTest_228, ReturnsValueWhenAttributePresentAsInt_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("a", 42);
    EXPECT_EQ(elem_->IntAttribute("a", -1), 42);
}

TEST_F(IntAttributeTest_228, ReturnsValueWhenAttributePresentAsNumericString_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("a", "17");
    EXPECT_EQ(elem_->IntAttribute("a", 999), 17);
}

TEST_F(IntAttributeTest_228, ReturnsValueForNegativeInteger_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("neg", -7);
    EXPECT_EQ(elem_->IntAttribute("neg", 0), -7);
}

TEST_F(IntAttributeTest_228, ReturnsValueForPlusSignedIntegerString_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("p", "+8");
    EXPECT_EQ(elem_->IntAttribute("p", 0), 8);
}

TEST_F(IntAttributeTest_228, ReturnsValueForWhitespacePaddedIntegerString_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("w", " \t\n  15  \r");
    EXPECT_EQ(elem_->IntAttribute("w", 0), 15);
}

TEST_F(IntAttributeTest_228, ReturnsDefaultWhenAttributePresentButNonNumeric_228) {
    ASSERT_NE(elem_, nullptr);
    elem_->SetAttribute("bad", "not_an_int");

    // Observable error case: library should not throw; result should fall back to default.
    EXPECT_EQ(elem_->IntAttribute("bad", 321), 321);
}

TEST_F(IntAttributeTest_228, ReturnsDefaultWhenNameIsEmptyAndNoSuchAttribute_228) {
    ASSERT_NE(elem_, nullptr);
    EXPECT_EQ(elem_->IntAttribute("", 55), 55);
}

TEST_F(IntAttributeTest_228, HandlesIntMinAndMax_228) {
    ASSERT_NE(elem_, nullptr);

    elem_->SetAttribute("minv", INT_MIN);
    elem_->SetAttribute("maxv", INT_MAX);

    EXPECT_EQ(elem_->IntAttribute("minv", 0), INT_MIN);
    EXPECT_EQ(elem_->IntAttribute("maxv", 0), INT_MAX);
}

TEST_F(IntAttributeTest_228, DefaultValueIsReturnedUnmodifiedWhenMissingAcrossDifferentDefaults_228) {
    ASSERT_NE(elem_, nullptr);

    EXPECT_EQ(elem_->IntAttribute("missing", 0), 0);
    EXPECT_EQ(elem_->IntAttribute("missing", -1), -1);
    EXPECT_EQ(elem_->IntAttribute("missing", INT_MAX), INT_MAX);
    EXPECT_EQ(elem_->IntAttribute("missing", INT_MIN), INT_MIN);
}
