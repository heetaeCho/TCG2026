// SPDX-License-Identifier: GPL-2.0-or-later
// File: link_reset_form_test_334.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "./TestProjects/poppler/poppler/Link.h"

// Some Poppler builds may only forward-declare Object in headers.
// A pointer to an incomplete type is fine for our purposes.
class Object;

namespace {

// Create a LinkResetForm instance in a way that compiles across variants:
// - Some builds may allow default construction (as in the provided partial code snippet).
// - Some builds may require LinkResetForm(const Object*).
static std::unique_ptr<LinkResetForm> MakeLinkResetFormOrSkip() {
  if constexpr (std::is_default_constructible_v<LinkResetForm>) {
    return std::make_unique<LinkResetForm>();
  } else if constexpr (std::is_constructible_v<LinkResetForm, const Object*>) {
    return std::make_unique<LinkResetForm>(nullptr);
  } else {
    return nullptr;  // caller will skip
  }
}

class LinkResetFormTest_334 : public ::testing::Test {
protected:
  std::unique_ptr<LinkResetForm> makeOrSkip() {
    auto ptr = MakeLinkResetFormOrSkip();
    if (!ptr) {
      GTEST_SKIP() << "LinkResetForm is not constructible in this build configuration.";
    }
    return ptr;
  }
};

}  // namespace

TEST_F(LinkResetFormTest_334, IsOkReturnsTrue_334) {
  auto link = makeOrSkip();
  EXPECT_TRUE(link->isOk());
}

TEST_F(LinkResetFormTest_334, IsOkCallableOnConstInstance_334) {
  auto link = makeOrSkip();
  const LinkResetForm& cref = *link;
  EXPECT_TRUE(cref.isOk());
}

TEST_F(LinkResetFormTest_334, IsOkStableAcrossMultipleCalls_334) {
  auto link = makeOrSkip();
  EXPECT_TRUE(link->isOk());
  EXPECT_TRUE(link->isOk());
  EXPECT_TRUE(link->isOk());
}

TEST_F(LinkResetFormTest_334, IsOkRemainsTrueAfterCopyIfCopyable_334) {
  auto link = makeOrSkip();

  if constexpr (std::is_copy_constructible_v<LinkResetForm>) {
    LinkResetForm copy = *link;
    EXPECT_TRUE(copy.isOk());

    // Also verify original still behaves the same after copying.
    EXPECT_TRUE(link->isOk());
  } else {
    GTEST_SKIP() << "LinkResetForm is not copy-constructible in this build.";
  }
}

TEST_F(LinkResetFormTest_334, IsOkRemainsTrueAfterMoveIfMovable_334) {
  auto link = makeOrSkip();

  if constexpr (std::is_move_constructible_v<LinkResetForm>) {
    LinkResetForm moved = std::move(*link);
    EXPECT_TRUE(moved.isOk());
  } else {
    GTEST_SKIP() << "LinkResetForm is not move-constructible in this build.";
  }
}