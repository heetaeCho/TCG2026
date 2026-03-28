// File: poppler-action-build-reset-form-test_2299.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-action.h"
#include "poppler/Link.h"
#include "poppler/Object.h"

// Include the implementation file to access the internal static function
// (keeps the function as a black box; we only validate observable effects).
#include "poppler-action.cc"

namespace {

class BuildResetFormTest_2299 : public ::testing::Test {
protected:
  static void FreeFieldsList(GList **list_ptr) {
    if (!list_ptr || !*list_ptr) {
      return;
    }
    g_list_free_full(*list_ptr, g_free);
    *list_ptr = nullptr;
  }

  static std::vector<std::string> ToVectorOfStrings(GList *list) {
    std::vector<std::string> out;
    for (GList *l = list; l != nullptr; l = l->next) {
      const char *s = static_cast<const char *>(l->data);
      out.emplace_back(s ? s : "");
    }
    return out;
  }

  void TearDown() override { FreeFieldsList(&action_.reset_form.fields); }

  PopplerAction action_{}; // zero-init; union field defaults to all-zero
};

TEST_F(BuildResetFormTest_2299, NullExistingFields_EmptyLinkFields_LeavesFieldsNull_2299) {
  // Arrange
  ASSERT_EQ(action_.reset_form.fields, nullptr);

  Object obj;
  obj.initNull(); // Provide a valid Object instance; LinkResetForm handles parsing internally.
  LinkResetForm link(&obj);

  const auto &expected_fields = link.getFields();
  const bool expected_exclude = link.getExclude();

  // Act
  build_reset_form(&action_, &link);

  // Assert (observable effects only)
  EXPECT_EQ(action_.reset_form.exclude, expected_exclude);

  // If LinkResetForm yields no fields, PopplerAction list must remain nullptr.
  if (expected_fields.empty()) {
    EXPECT_EQ(action_.reset_form.fields, nullptr);
  } else {
    // If fields exist, they must be copied into a newly built GList in the same order.
    const std::vector<std::string> actual = ToVectorOfStrings(action_.reset_form.fields);
    EXPECT_EQ(actual.size(), expected_fields.size());
    for (size_t i = 0; i < expected_fields.size(); ++i) {
      EXPECT_EQ(actual[i], expected_fields[i]);
    }
  }
}

TEST_F(BuildResetFormTest_2299, ReplacesAndClearsExistingFields_WhenLinkHasNoFields_2299) {
  // Arrange: pre-populate action_.reset_form.fields with some strings.
  action_.reset_form.fields = g_list_append(action_.reset_form.fields, g_strdup("fieldA"));
  action_.reset_form.fields = g_list_append(action_.reset_form.fields, g_strdup("fieldB"));
  ASSERT_NE(action_.reset_form.fields, nullptr);

  Object obj;
  obj.initNull();
  LinkResetForm link(&obj);

  const auto &expected_fields = link.getFields();
  const bool expected_exclude = link.getExclude();

  // Act
  build_reset_form(&action_, &link);

  // Assert
  EXPECT_EQ(action_.reset_form.exclude, expected_exclude);

  if (expected_fields.empty()) {
    // Observable behavior: existing list must be freed and pointer reset to nullptr.
    EXPECT_EQ(action_.reset_form.fields, nullptr);
  } else {
    // Otherwise, list must be replaced with the link-provided fields (not old contents).
    const std::vector<std::string> actual = ToVectorOfStrings(action_.reset_form.fields);
    EXPECT_EQ(actual.size(), expected_fields.size());
    for (size_t i = 0; i < expected_fields.size(); ++i) {
      EXPECT_EQ(actual[i], expected_fields[i]);
    }
    // And it should not still contain the old values if they are not present in expected_fields.
    // (We avoid assuming what expected_fields contains; we only check that output matches it.)
  }
}

TEST_F(BuildResetFormTest_2299, IdempotentWithSameLink_RebuildsListContentConsistently_2299) {
  // Arrange
  Object obj;
  obj.initNull();
  LinkResetForm link(&obj);

  const auto &expected_fields = link.getFields();
  const bool expected_exclude = link.getExclude();

  // Act: call twice
  build_reset_form(&action_, &link);
  const std::vector<std::string> first = ToVectorOfStrings(action_.reset_form.fields);
  const bool first_exclude = action_.reset_form.exclude;

  build_reset_form(&action_, &link);
  const std::vector<std::string> second = ToVectorOfStrings(action_.reset_form.fields);
  const bool second_exclude = action_.reset_form.exclude;

  // Assert: observable results remain consistent with the link getters.
  EXPECT_EQ(first_exclude, expected_exclude);
  EXPECT_EQ(second_exclude, expected_exclude);

  if (expected_fields.empty()) {
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
    EXPECT_EQ(action_.reset_form.fields, nullptr);
  } else {
    EXPECT_EQ(first.size(), expected_fields.size());
    EXPECT_EQ(second.size(), expected_fields.size());
    for (size_t i = 0; i < expected_fields.size(); ++i) {
      EXPECT_EQ(first[i], expected_fields[i]);
      EXPECT_EQ(second[i], expected_fields[i]);
    }
  }
}

TEST_F(BuildResetFormTest_2299, HandlesPreExistingFieldsPointer_WhenCalledMultipleTimes_2299) {
  // Arrange: start with a non-null list.
  action_.reset_form.fields = g_list_append(action_.reset_form.fields, g_strdup("old1"));
  ASSERT_NE(action_.reset_form.fields, nullptr);

  Object obj;
  obj.initNull();
  LinkResetForm link(&obj);

  const auto &expected_fields = link.getFields();
  const bool expected_exclude = link.getExclude();

  // Act
  build_reset_form(&action_, &link);

  // Assert
  EXPECT_EQ(action_.reset_form.exclude, expected_exclude);

  // The resulting list must reflect the link-provided fields exactly (or be null if none).
  if (expected_fields.empty()) {
    EXPECT_EQ(action_.reset_form.fields, nullptr);
  } else {
    const std::vector<std::string> actual = ToVectorOfStrings(action_.reset_form.fields);
    EXPECT_EQ(actual.size(), expected_fields.size());
    for (size_t i = 0; i < expected_fields.size(); ++i) {
      EXPECT_EQ(actual[i], expected_fields[i]);
    }
  }
}

} // namespace