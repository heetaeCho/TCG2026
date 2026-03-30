// File: LinkRendition_test_308.cpp
#include <gtest/gtest.h>

#if __has_include("poppler/Link.h")
#include "poppler/Link.h"
#elif __has_include("Link.h")
#include "Link.h"
#else
#error "Cannot find poppler/Link.h (or Link.h). Adjust include paths for your build."
#endif

namespace {

class LinkRenditionTest_308 : public ::testing::Test {};

TEST_F(LinkRenditionTest_308, DefaultConstructed_IsOkReturnsTrue_308) {
  LinkRendition rendition;
  EXPECT_TRUE(rendition.isOk());
}

TEST_F(LinkRenditionTest_308, IsOkCallableOnConstObject_308) {
  const LinkRendition rendition;
  EXPECT_TRUE(rendition.isOk());
}

TEST_F(LinkRenditionTest_308, IsOkIsIdempotent_MultipleCallsReturnSameValue_308) {
  LinkRendition rendition;

  const bool first = rendition.isOk();
  const bool second = rendition.isOk();
  const bool third = rendition.isOk();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_TRUE(first);
}

TEST_F(LinkRenditionTest_308, MultipleInstances_AllReportOk_308) {
  // Boundary-style coverage: many instances should be independently usable.
  constexpr int kCount = 128;
  for (int i = 0; i < kCount; ++i) {
    LinkRendition rendition;
    EXPECT_TRUE(rendition.isOk()) << "Instance index: " << i;
  }
}

}  // namespace