// File: ./TestProjects/re2/re2/tests/capture_names_walker_shortvisit_test.cc

#include <limits>
#include "gtest/gtest.h"

// Prefer including the actual headers if available in your build.
// The prompt's partial interface indicates these live in namespace re2.
#include "re2/regexp.h"   // For re2::Regexp (pointer type used by ShortVisit)

// Forward declaration in case CaptureNamesWalker is not exposed via a header
// but is available to the linker (as implied by the prompt). If your project
// provides a header that declares this type, include it instead and remove
// these forward declarations.
namespace re2 {
  typedef int Ignored;
  class CaptureNamesWalker {
   public:
    virtual Ignored ShortVisit(Regexp* re, Ignored ignored);
    virtual ~CaptureNamesWalker() = default;
  };
}  // namespace re2

namespace {

using re2::CaptureNamesWalker;
using re2::Ignored;
using re2::Regexp;

class CaptureNamesWalkerTest_365 : public ::testing::Test {
 protected:
  CaptureNamesWalker walker_;
};

// Ensures ShortVisit returns the same Ignored value when given a null Regexp*.
TEST_F(CaptureNamesWalkerTest_365, ShortVisit_ReturnsSameValue_WithNullRegexp_365) {
  Ignored input = 42;
  Regexp* re = nullptr;  // We do not depend on any internal Regexp behavior.

  Ignored out = walker_.ShortVisit(re, input);

  EXPECT_EQ(out, input);
}

// Verifies ShortVisit is a pure passthrough for a range of integer values.
TEST_F(CaptureNamesWalkerTest_365, ShortVisit_PassthroughForVariousValues_365) {
  Regexp* re = nullptr;

  // Normal values
  EXPECT_EQ(walker_.ShortVisit(re, 0), 0);
  EXPECT_EQ(walker_.ShortVisit(re, 1), 1);
  EXPECT_EQ(walker_.ShortVisit(re, -1), -1);
  EXPECT_EQ(walker_.ShortVisit(re, 123456), 123456);

  // Boundary values
  EXPECT_EQ(walker_.ShortVisit(re, std::numeric_limits<int>::max()),
            std::numeric_limits<int>::max());
  EXPECT_EQ(walker_.ShortVisit(re, std::numeric_limits<int>::min()),
            std::numeric_limits<int>::min());
}

// (Optional) If you want to also ensure it behaves the same with a non-null
// Regexp* without depending on Regexp internals, you can pass a dummy pointer.
// WARNING: Do NOT dereference; just verify passthrough behavior.
TEST_F(CaptureNamesWalkerTest_365, ShortVisit_IgnoresRegexpPointer_365) {
  // Use a dummy address cast; never dereference it.
  Regexp* fake = reinterpret_cast<Regexp*>(0x1);
  Ignored input = -123;

  Ignored out = walker_.ShortVisit(fake, input);

  EXPECT_EQ(out, input);
}

}  // namespace
