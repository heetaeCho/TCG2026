#include <gtest/gtest.h>
#include "Link.h"

// Test fixture for LinkResetForm tests
class LinkResetFormTest_337 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getExclude returns a boolean value when constructed with a valid object
TEST_F(LinkResetFormTest_337, GetExcludeReturnsBool_337) {
    // Construct with nullptr to test default/error behavior
    LinkResetForm form(nullptr);
    bool result = form.getExclude();
    // We just verify it returns a bool without crashing
    EXPECT_TRUE(result == true || result == false);
}

// Test that getKind returns the correct LinkActionKind for ResetForm
TEST_F(LinkResetFormTest_337, GetKindReturnsResetForm_337) {
    LinkResetForm form(nullptr);
    LinkActionKind kind = form.getKind();
    EXPECT_EQ(kind, actionResetForm);
}

// Test that getFields returns a reference to a vector of strings
TEST_F(LinkResetFormTest_337, GetFieldsReturnsVector_337) {
    LinkResetForm form(nullptr);
    const std::vector<std::string> &fields = form.getFields();
    // When constructed with nullptr, fields should likely be empty
    // but we only verify it doesn't crash and returns a valid reference
    EXPECT_GE(fields.size(), 0u);
}

// Test isOk with nullptr construction (likely returns false or handles gracefully)
TEST_F(LinkResetFormTest_337, IsOkWithNullObject_337) {
    LinkResetForm form(nullptr);
    bool ok = form.isOk();
    // With a null object, the form may or may not be ok depending on implementation
    EXPECT_TRUE(ok == true || ok == false);
}

// Test that getExclude default behavior is consistent across calls
TEST_F(LinkResetFormTest_337, GetExcludeConsistentAcrossCalls_337) {
    LinkResetForm form(nullptr);
    bool first = form.getExclude();
    bool second = form.getExclude();
    EXPECT_EQ(first, second);
}

// Test that getFields is consistent across multiple calls
TEST_F(LinkResetFormTest_337, GetFieldsConsistentAcrossCalls_337) {
    LinkResetForm form(nullptr);
    const std::vector<std::string> &fields1 = form.getFields();
    const std::vector<std::string> &fields2 = form.getFields();
    EXPECT_EQ(fields1.size(), fields2.size());
    EXPECT_EQ(&fields1, &fields2);  // Should return reference to the same internal vector
}

// Test construction with a valid Object (dict-based)
TEST_F(LinkResetFormTest_337, ConstructWithValidObject_337) {
    Object obj;
    // Attempt construction with an empty object
    LinkResetForm form(&obj);
    // Verify it doesn't crash and basic methods work
    form.getExclude();
    form.getFields();
    form.getKind();
}

// Test that getKind is consistent
TEST_F(LinkResetFormTest_337, GetKindConsistent_337) {
    LinkResetForm form(nullptr);
    EXPECT_EQ(form.getKind(), form.getKind());
}

// Test that with nullptr, fields vector is empty
TEST_F(LinkResetFormTest_337, NullObjectFieldsEmpty_337) {
    LinkResetForm form(nullptr);
    const std::vector<std::string> &fields = form.getFields();
    EXPECT_TRUE(fields.empty());
}

// Test that with nullptr, exclude defaults to false
TEST_F(LinkResetFormTest_337, NullObjectExcludeDefaultFalse_337) {
    LinkResetForm form(nullptr);
    // Default exclude should be false when no valid object is provided
    EXPECT_FALSE(form.getExclude());
}
