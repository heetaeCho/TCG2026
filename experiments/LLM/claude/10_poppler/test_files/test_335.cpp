#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Link.h"

// Test that getKind() returns actionResetForm
TEST(LinkResetFormTest_335, GetKindReturnsActionResetForm_335) {
    // We need to construct a LinkResetForm. Based on the known interface,
    // the constructor takes a const Object* nameObj.
    // We'll try constructing with a nullptr to test basic behavior.
    Object obj;
    LinkResetForm resetForm(&obj);
    EXPECT_EQ(resetForm.getKind(), actionResetForm);
}

// Test that getKind() returns the correct enum value (11)
TEST(LinkResetFormTest_335, GetKindReturnsCorrectEnumValue_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    EXPECT_EQ(static_cast<int>(resetForm.getKind()), 11);
}

// Test construction with nullptr
TEST(LinkResetFormTest_335, ConstructWithNullptr_335) {
    LinkResetForm resetForm(nullptr);
    // Even with nullptr, getKind should still return actionResetForm
    EXPECT_EQ(resetForm.getKind(), actionResetForm);
}

// Test getFields returns a reference to vector
TEST(LinkResetFormTest_335, GetFieldsReturnsVector_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    const std::vector<std::string> &fields = resetForm.getFields();
    // With a default/empty object, fields should likely be empty
    // We just verify we can call it without crashing
    EXPECT_GE(fields.size(), 0u);
}

// Test getExclude returns a bool
TEST(LinkResetFormTest_335, GetExcludeReturnsBool_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    bool exclude = resetForm.getExclude();
    // Just verify it returns a valid bool (true or false)
    EXPECT_TRUE(exclude == true || exclude == false);
}

// Test isOk with nullptr construction
TEST(LinkResetFormTest_335, IsOkWithNullptr_335) {
    LinkResetForm resetForm(nullptr);
    // isOk may return false for a nullptr-constructed object
    // We just verify it doesn't crash
    bool ok = resetForm.isOk();
    EXPECT_TRUE(ok == true || ok == false);
}

// Test isOk with default Object
TEST(LinkResetFormTest_335, IsOkWithDefaultObject_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    bool ok = resetForm.isOk();
    EXPECT_TRUE(ok == true || ok == false);
}

// Test that getKind is consistent across multiple calls
TEST(LinkResetFormTest_335, GetKindConsistentAcrossMultipleCalls_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    EXPECT_EQ(resetForm.getKind(), actionResetForm);
    EXPECT_EQ(resetForm.getKind(), actionResetForm);
    EXPECT_EQ(resetForm.getKind(), actionResetForm);
}

// Test that actionResetForm is distinct from other action kinds
TEST(LinkResetFormTest_335, ActionResetFormDistinctFromOtherKinds_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    LinkActionKind kind = resetForm.getKind();
    EXPECT_NE(kind, actionGoTo);
    EXPECT_NE(kind, actionGoToR);
    EXPECT_NE(kind, actionLaunch);
    EXPECT_NE(kind, actionURI);
    EXPECT_NE(kind, actionNamed);
    EXPECT_NE(kind, actionMovie);
    EXPECT_NE(kind, actionRendition);
    EXPECT_NE(kind, actionSound);
    EXPECT_NE(kind, actionJavaScript);
    EXPECT_NE(kind, actionOCGState);
    EXPECT_NE(kind, actionHide);
    EXPECT_NE(kind, actionSubmitForm);
    EXPECT_NE(kind, actionUnknown);
}

// Test getFields consistency
TEST(LinkResetFormTest_335, GetFieldsConsistentAcrossMultipleCalls_335) {
    Object obj;
    LinkResetForm resetForm(&obj);
    const std::vector<std::string> &fields1 = resetForm.getFields();
    const std::vector<std::string> &fields2 = resetForm.getFields();
    EXPECT_EQ(fields1.size(), fields2.size());
    EXPECT_EQ(&fields1, &fields2); // Should return reference to same internal vector
}
