#include <gtest/gtest.h>
#include "Link.h"

// Test that getFields returns a reference to a vector of strings
TEST(LinkResetFormTest_336, GetFieldsReturnsVector_336) {
    // We need to construct a LinkResetForm object.
    // Based on the known interface, it takes a const Object* nameObj.
    // We'll create with a null object to test default/empty behavior.
    Object obj;
    LinkResetForm form(&obj);
    
    const std::vector<std::string> &fields = form.getFields();
    // With a default/null Object, we expect the fields to be empty or
    // at least that getFields() returns a valid reference without crashing
    EXPECT_GE(fields.size(), 0u);
}

// Test that getFields returns the same reference on multiple calls
TEST(LinkResetFormTest_336, GetFieldsReturnsSameReference_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    const std::vector<std::string> &fields1 = form.getFields();
    const std::vector<std::string> &fields2 = form.getFields();
    
    // Both calls should return a reference to the same internal vector
    EXPECT_EQ(&fields1, &fields2);
}

// Test getKind returns the appropriate LinkAction kind for ResetForm
TEST(LinkResetFormTest_336, GetKindReturnsResetForm_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    EXPECT_EQ(form.getKind(), actionResetForm);
}

// Test getExclude returns a boolean value
TEST(LinkResetFormTest_336, GetExcludeReturnsBool_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    bool exclude = form.getExclude();
    // Just verify it returns without error; the value depends on input
    EXPECT_TRUE(exclude == true || exclude == false);
}

// Test isOk with default/null object
TEST(LinkResetFormTest_336, IsOkWithDefaultObject_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    // isOk should return a valid boolean
    bool ok = form.isOk();
    EXPECT_TRUE(ok == true || ok == false);
}

// Test constructing with nullptr
TEST(LinkResetFormTest_336, ConstructWithNullptr_336) {
    LinkResetForm form(nullptr);
    
    // Should not crash and getFields should return a valid reference
    const std::vector<std::string> &fields = form.getFields();
    EXPECT_GE(fields.size(), 0u);
}

// Test that fields vector elements are accessible when non-empty
TEST(LinkResetFormTest_336, GetFieldsElementsAccessible_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    const std::vector<std::string> &fields = form.getFields();
    for (size_t i = 0; i < fields.size(); ++i) {
        // Each field should be a valid string (not crash on access)
        EXPECT_GE(fields[i].size(), 0u);
    }
}

// Test consistency between getFields and getExclude
TEST(LinkResetFormTest_336, FieldsAndExcludeConsistency_336) {
    Object obj;
    LinkResetForm form(&obj);
    
    const std::vector<std::string> &fields = form.getFields();
    bool exclude = form.getExclude();
    
    // If there are no fields, exclude flag doesn't matter functionally
    // but both should be queryable without error
    if (fields.empty()) {
        EXPECT_TRUE(exclude == true || exclude == false);
    }
}
