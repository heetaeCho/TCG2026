// Links_getLinks_tests_346.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include "poppler/Link.h" // Adjust include path if your build uses a different include style

namespace {

// ---- Compile-time (interface) checks ----

TEST(LinksTest_346, GetLinks_ReturnTypeIsConstVectorSharedPtrRef_346) {
  using ReturnT = decltype(std::declval<const Links&>().getLinks());
  using ExpectedT = const std::vector<std::shared_ptr<AnnotLink>>&;
  static_assert(std::is_same_v<ReturnT, ExpectedT>,
                "Links::getLinks() must return "
                "const std::vector<std::shared_ptr<AnnotLink>>&");
  SUCCEED();
}

TEST(LinksTest_346, GetLinks_CanBeCalledOnConstObject_346) {
  // If this compiles, the method is callable on const.
  (void)std::declval<const Links&>().getLinks();
  SUCCEED();
}

// ---- Runtime observable behavior checks ----
//
// Note: Links has an explicit constructor Links(Annots*).
// We pass nullptr as a boundary input. These tests intentionally do NOT
// assume internal logic beyond observable behavior through the public API.

TEST(LinksTest_346, ConstructWithNullAnnots_GetLinksIsCallable_346) {
  Links links(nullptr);

  // Should be safe to call and return a reference.
  const auto& v = links.getLinks();
  (void)v;

  SUCCEED();
}

TEST(LinksTest_346, GetLinks_ReturnsStableReferenceAcrossCalls_346) {
  Links links(nullptr);

  const auto& v1 = links.getLinks();
  const auto& v2 = links.getLinks();

  // Observable: both calls should refer to the same underlying container object.
  EXPECT_EQ(std::addressof(v1), std::addressof(v2));
}

TEST(LinksTest_346, GetLinks_SizeIsConsistentAcrossCalls_346) {
  Links links(nullptr);

  const auto& v1 = links.getLinks();
  const auto& v2 = links.getLinks();

  EXPECT_EQ(v1.size(), v2.size());
}

}  // namespace