// build_named_test_2295.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>

// -----------------------------------------------------------------------------
// Test seam for the static helper in poppler-action.cc
//
// We want to test build_named(PopplerAction*, const LinkNamed*) as a black box,
// while avoiding constructing real poppler::LinkNamed (which requires core
// Poppler objects).
//
// We do this by:
//  1) Providing a tiny fake class that matches the *used* interface: getName().
//  2) Preprocessor-renaming LinkNamed inside poppler-action.cc to our fake type.
// -----------------------------------------------------------------------------

class PopplerActionBuildNamed_TestLinkNamed {
public:
  explicit PopplerActionBuildNamed_TestLinkNamed(std::string name) : name_(std::move(name)) {}
  const std::string &getName() const { return name_; }

private:
  std::string name_;
};

// Try to prevent the real Link.h from interfering (guard names vary by project).
// Even if these don't match upstream, the LinkNamed rename below ensures the
// symbol used by build_named becomes our fake type within this TU.
#ifndef POPPLER_LINK_H
#define POPPLER_LINK_H 1
#endif
#ifndef _POPPLER_LINK_H_
#define _POPPLER_LINK_H_ 1
#endif
#ifndef LINK_H
#define LINK_H 1
#endif

#define LinkNamed PopplerActionBuildNamed_TestLinkNamed

// Include the implementation under test so we can reach the internal static.
#include "./TestProjects/poppler/glib/poppler-action.cc"

#undef LinkNamed

#include "./TestProjects/poppler/glib/poppler-action.h"

namespace {

class BuildNamedTest_2295 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure we don't leak if a test forgets to free.
    if (action_.named.named_dest) {
      g_free(action_.named.named_dest);
      action_.named.named_dest = nullptr;
    }
  }

  PopplerAction action_{}; // zero-init; named.named_dest should start nullptr.
};

TEST_F(BuildNamedTest_2295, CopiesNonEmptyNameIntoNamedDest_2295) {
  PopplerActionBuildNamed_TestLinkNamed link("DestA");

  ASSERT_EQ(action_.named.named_dest, nullptr);

  build_named(&action_, &link);

  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_STREQ(action_.named.named_dest, "DestA");
}

TEST_F(BuildNamedTest_2295, CopiesEmptyStringNameIntoNamedDest_2295) {
  PopplerActionBuildNamed_TestLinkNamed link("");

  ASSERT_EQ(action_.named.named_dest, nullptr);

  build_named(&action_, &link);

  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_STREQ(action_.named.named_dest, "");
}

TEST_F(BuildNamedTest_2295, CopiesUnicodeUtf8NameIntoNamedDest_2295) {
  // UTF-8 literal (Korean + emoji) to ensure it is treated as bytes and preserved.
  const char *kUtf8Name = u8"목적지-📄";
  PopplerActionBuildNamed_TestLinkNamed link(std::string(kUtf8Name));

  build_named(&action_, &link);

  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_STREQ(action_.named.named_dest, kUtf8Name);
}

TEST_F(BuildNamedTest_2295, OverwritesPointerWithNewDuplicateOnSecondCall_2295) {
  PopplerActionBuildNamed_TestLinkNamed link1("First");
  PopplerActionBuildNamed_TestLinkNamed link2("Second");

  build_named(&action_, &link1);
  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_STREQ(action_.named.named_dest, "First");

  gchar *first_ptr = action_.named.named_dest;

  build_named(&action_, &link2);
  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_STREQ(action_.named.named_dest, "Second");

  // Observable behavior: destination now matches the second name.
  // Also check pointer changed to indicate a new allocation (typical for g_strdup).
  // If an implementation reuses the same buffer, this check may fail; therefore
  // it is written as a non-fatal expectation.
  EXPECT_NE(action_.named.named_dest, first_ptr);

  // Free the latest pointer in TearDown(). If pointers differ, free the old one here.
  if (first_ptr && first_ptr != action_.named.named_dest) {
    g_free(first_ptr);
  }
}

TEST_F(BuildNamedTest_2295, HandlesVeryLongName_2295) {
  std::string long_name(4096, 'a');
  long_name.replace(0, 12, "very-long--");

  PopplerActionBuildNamed_TestLinkNamed link(long_name);

  build_named(&action_, &link);

  ASSERT_NE(action_.named.named_dest, nullptr);
  EXPECT_EQ(std::string(action_.named.named_dest), long_name);
}

} // namespace