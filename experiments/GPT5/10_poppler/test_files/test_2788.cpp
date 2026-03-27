// TextLink_test_2788.cc
#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

// Forward declaration is sufficient because TextLink only takes an AnnotLink*.
class AnnotLink;

// Include the production header if available in your build.
// If TextLink is only available via including TextOutputDev.cc or another header,
// adjust the include accordingly.
#include "TextOutputDev.h" // <-- Update this include to the correct path in your project.

namespace {

class TextLinkTest_2788 : public ::testing::Test {};

TEST_F(TextLinkTest_2788, TypeTraits_ConstructibleAndDestructible_2788)
{
  // Interface-level checks only (no assumptions about internal behavior).
  static_assert(std::is_constructible_v<TextLink, int, int, int, int, AnnotLink *>,
                "TextLink must be constructible with (int,int,int,int,AnnotLink*).");
  static_assert(std::is_destructible_v<TextLink>, "TextLink must be destructible.");
}

TEST_F(TextLinkTest_2788, ConstructWithNullLinkPointer_2788)
{
  // Normal operation: constructing with a null link pointer should be allowed
  // (at least it is representable by the interface).
  EXPECT_NO_THROW({
    TextLink link(0, 0, 10, 10, nullptr);
    (void)link;
  });
}

TEST_F(TextLinkTest_2788, ConstructWithAllZeroCoordinates_2788)
{
  // Boundary-ish: zeros.
  EXPECT_NO_THROW({
    TextLink link(0, 0, 0, 0, nullptr);
    (void)link;
  });
}

TEST_F(TextLinkTest_2788, ConstructWithNegativeCoordinates_2788)
{
  // Boundary: negative coordinates should not crash on construction.
  EXPECT_NO_THROW({
    TextLink link(-10, -20, -1, -2, nullptr);
    (void)link;
  });
}

TEST_F(TextLinkTest_2788, ConstructWithMinMaxIntCoordinates_2788)
{
  // Boundary: extreme int ranges.
  const int kMin = std::numeric_limits<int>::min();
  const int kMax = std::numeric_limits<int>::max();

  EXPECT_NO_THROW({
    TextLink link(kMin, kMin, kMax, kMax, nullptr);
    (void)link;
  });
}

TEST_F(TextLinkTest_2788, ConstructWithInvertedMinMaxCoordinates_2788)
{
  // Error-ish/boundary: "inverted" rectangles (min > max). We cannot assume it errors,
  // but we can ensure construction is safe/doesn't throw (observable behavior).
  EXPECT_NO_THROW({
    TextLink link(100, 100, 0, 0, nullptr);
    (void)link;
  });
}

} // namespace