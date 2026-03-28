#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>
#include <string>
#include <vector>

// Include necessary headers
#include "poppler-action.h"
#include "Link.h"

// Since build_reset_form is static, we need to include the .cc or use a test helper.
// For testing purposes, we declare it as accessible or include the source.
// In practice, this might require a test-friend approach or exposing via a test header.

// Mock for LinkResetForm
class MockLinkResetForm : public LinkResetForm {
public:
    MockLinkResetForm() : LinkResetForm(nullptr) {}
    MOCK_METHOD(const std::vector<std::string>&, getFields, (), (const));
    MOCK_METHOD(bool, getExclude, (), (const));
    MOCK_METHOD(bool, isOk, (), (const, override));
    MOCK_METHOD(LinkActionKind, getKind, (), (const, override));
};

// Forward declare the function under test (it's static in the .cc, so we may need
// to include the source or use a workaround)
extern void build_reset_form(PopplerAction *action, const LinkResetForm *link);

class BuildResetFormTest_2299 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&action, 0, sizeof(PopplerAction));
        action.reset_form.fields = nullptr;
    }

    void TearDown() override {
        if (action.reset_form.fields != nullptr) {
            g_list_free_full(action.reset_form.fields, g_free);
            action.reset_form.fields = nullptr;
        }
    }

    PopplerAction action;
};

TEST_F(BuildResetFormTest_2299, EmptyFieldsList_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> emptyFields;

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(emptyFields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    EXPECT_EQ(action.reset_form.fields, nullptr);
    EXPECT_FALSE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, SingleField_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"field1"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(true));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 1u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "field1");
    EXPECT_TRUE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, MultipleFields_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"name", "address", "email"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 3u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "name");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 1)), "address");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 2)), "email");
    EXPECT_FALSE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, ExcludeTrue_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"test"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(true));

    build_reset_form(&action, &mockLink);

    EXPECT_TRUE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, ExcludeFalse_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"test"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    EXPECT_FALSE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, PreExistingFieldsAreFreed_2299) {
    // Pre-populate with existing fields
    action.reset_form.fields = g_list_append(nullptr, g_strdup("old_field1"));
    action.reset_form.fields = g_list_append(action.reset_form.fields, g_strdup("old_field2"));

    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"new_field"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 1u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "new_field");
}

TEST_F(BuildResetFormTest_2299, PreExistingFieldsReplacedWithEmpty_2299) {
    action.reset_form.fields = g_list_append(nullptr, g_strdup("old_field"));

    MockLinkResetForm mockLink;
    std::vector<std::string> emptyFields;

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(emptyFields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(true));

    build_reset_form(&action, &mockLink);

    EXPECT_EQ(action.reset_form.fields, nullptr);
    EXPECT_TRUE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, FieldWithEmptyString_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {""};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 1u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "");
}

TEST_F(BuildResetFormTest_2299, FieldsWithSpecialCharacters_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"field with spaces", "field\twith\ttabs", "field\nwith\nnewlines", "日本語フィールド"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 4u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "field with spaces");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 1)), "field\twith\ttabs");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 2)), "field\nwith\nnewlines");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 3)), "日本語フィールド");
}

TEST_F(BuildResetFormTest_2299, CalledTwiceReplacesFields_2299) {
    MockLinkResetForm mockLink1;
    std::vector<std::string> fields1 = {"first", "second"};

    EXPECT_CALL(mockLink1, getFields())
        .WillOnce(::testing::ReturnRef(fields1));
    EXPECT_CALL(mockLink1, getExclude())
        .WillOnce(::testing::Return(true));

    build_reset_form(&action, &mockLink1);

    ASSERT_EQ(g_list_length(action.reset_form.fields), 2u);
    EXPECT_TRUE(action.reset_form.exclude);

    MockLinkResetForm mockLink2;
    std::vector<std::string> fields2 = {"third"};

    EXPECT_CALL(mockLink2, getFields())
        .WillOnce(::testing::ReturnRef(fields2));
    EXPECT_CALL(mockLink2, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink2);

    ASSERT_EQ(g_list_length(action.reset_form.fields), 1u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "third");
    EXPECT_FALSE(action.reset_form.exclude);
}

TEST_F(BuildResetFormTest_2299, NullFieldsPointerInitially_2299) {
    // action.reset_form.fields is already nullptr from SetUp
    ASSERT_EQ(action.reset_form.fields, nullptr);

    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"a", "b"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_NE(action.reset_form.fields, nullptr);
    EXPECT_EQ(g_list_length(action.reset_form.fields), 2u);
}

TEST_F(BuildResetFormTest_2299, FieldOrderPreserved_2299) {
    MockLinkResetForm mockLink;
    std::vector<std::string> fields = {"z", "a", "m", "b", "y"};

    EXPECT_CALL(mockLink, getFields())
        .WillOnce(::testing::ReturnRef(fields));
    EXPECT_CALL(mockLink, getExclude())
        .WillOnce(::testing::Return(false));

    build_reset_form(&action, &mockLink);

    ASSERT_EQ(g_list_length(action.reset_form.fields), 5u);
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 0)), "z");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 1)), "a");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 2)), "m");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 3)), "b");
    EXPECT_STREQ(static_cast<char*>(g_list_nth_data(action.reset_form.fields, 4)), "y");
}
