#include <gtest/gtest.h>
#include "Link.h"

// Test that isOk() returns true for LinkResetForm
TEST(LinkResetFormTest_334, IsOkReturnsTrue_334) {
    // Since we need to construct a LinkResetForm, we try with a nullptr
    // or a valid Object. Based on the interface, the constructor takes const Object*.
    Object obj;
    LinkResetForm form(&obj);
    EXPECT_TRUE(form.isOk());
}

// Test that getKind returns the appropriate LinkActionKind for ResetForm
TEST(LinkResetFormTest_334, GetKindReturnsResetForm_334) {
    Object obj;
    LinkResetForm form(&obj);
    EXPECT_EQ(form.getKind(), actionResetForm);
}

// Test that getFields returns a vector (possibly empty with default/null construction)
TEST(LinkResetFormTest_334, GetFieldsReturnsVector_334) {
    Object obj;
    LinkResetForm form(&obj);
    const std::vector<std::string> &fields = form.getFields();
    // With a default/empty object, we expect no fields
    EXPECT_TRUE(fields.empty());
}

// Test that getExclude returns a boolean value with default construction
TEST(LinkResetFormTest_334, GetExcludeReturnsBool_334) {
    Object obj;
    LinkResetForm form(&obj);
    bool exclude = form.getExclude();
    // With a default/empty object, exclude should default to false
    EXPECT_FALSE(exclude);
}

// Test construction with nullptr Object
TEST(LinkResetFormTest_334, ConstructWithNullObject_334) {
    LinkResetForm form(nullptr);
    // Even with nullptr, isOk should still return true based on the implementation shown
    EXPECT_TRUE(form.isOk());
}

// Test that getFields returns a const reference (compilation check and emptiness)
TEST(LinkResetFormTest_334, GetFieldsIsConstReference_334) {
    Object obj;
    LinkResetForm form(&obj);
    const auto &fields1 = form.getFields();
    const auto &fields2 = form.getFields();
    // Should return reference to the same internal vector
    EXPECT_EQ(&fields1, &fields2);
}

// Test with an array Object containing field names
TEST(LinkResetFormTest_334, ConstructWithArrayObject_334) {
    Object arrObj;
    // Create an array object with string entries to simulate field names
    arrObj = Object(new Array(nullptr));
    
    LinkResetForm form(&arrObj);
    EXPECT_TRUE(form.isOk());
    EXPECT_EQ(form.getKind(), actionResetForm);
}

// Test that multiple calls to isOk are consistent
TEST(LinkResetFormTest_334, IsOkConsistentAcrossCalls_334) {
    Object obj;
    LinkResetForm form(&obj);
    EXPECT_TRUE(form.isOk());
    EXPECT_TRUE(form.isOk());
    EXPECT_TRUE(form.isOk());
}

// Test that multiple calls to getExclude are consistent
TEST(LinkResetFormTest_334, GetExcludeConsistentAcrossCalls_334) {
    Object obj;
    LinkResetForm form(&obj);
    bool first = form.getExclude();
    bool second = form.getExclude();
    EXPECT_EQ(first, second);
}
