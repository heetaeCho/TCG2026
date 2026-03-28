// poppler-page-transition-data-test-2776.cc
#include <gtest/gtest.h>

#include <type_traits>

#include "Object.h"
#include "PageTransition.h"

// The production code defines this in poppler-page-transition.cc. We only redeclare
// the public interface exactly as provided so we can link against the real impl.
namespace Poppler {
class PageTransitionData {
public:
  ::PageTransition *pt;
  explicit PageTransitionData(Object *trans);
  PageTransitionData(const PageTransitionData &ptd);
  ~PageTransitionData();
  PageTransitionData &operator=(const PageTransitionData &) = delete;
};
} // namespace Poppler

namespace {

class PageTransitionDataTest_2776 : public ::testing::Test {
protected:
  static Object MakeTransitionObject_2776()
  {
    // Keep construction minimal and interface-driven:
    // default Object is commonly a "null" object in Poppler, and should be safe
    // to pass by pointer. We do not depend on internal parsing behavior.
    Object o;
    return o;
  }
};

TEST_F(PageTransitionDataTest_2776, TypeTraits_CopyConstructibleAndNotCopyAssignable_2776)
{
  static_assert(std::is_copy_constructible_v<Poppler::PageTransitionData>,
                "PageTransitionData should be copy constructible");
  static_assert(!std::is_copy_assignable_v<Poppler::PageTransitionData>,
                "PageTransitionData copy assignment must be deleted");
  SUCCEED();
}

TEST_F(PageTransitionDataTest_2776, ConstructWithObject_ProducesNonNullTransitionPointer_2776)
{
  Object trans = MakeTransitionObject_2776();

  Poppler::PageTransitionData d(&trans);

  // Observable behavior through the public data member.
  ASSERT_NE(d.pt, nullptr);

  // Also only uses public methods of ::PageTransition.
  // We don't assert ok-ness because that depends on the Object content.
  (void)d.pt->isOk();
}

TEST_F(PageTransitionDataTest_2776, CopyConstructor_DeepCopiesPointer_2776)
{
  Object trans = MakeTransitionObject_2776();
  Poppler::PageTransitionData original(&trans);
  ASSERT_NE(original.pt, nullptr);

  Poppler::PageTransitionData copied(original);

  ASSERT_NE(copied.pt, nullptr);
  EXPECT_NE(copied.pt, original.pt); // observable deep-copy expectation
}

TEST_F(PageTransitionDataTest_2776, CopyConstructor_PreservesObservableTransitionProperties_2776)
{
  Object trans = MakeTransitionObject_2776();
  Poppler::PageTransitionData original(&trans);
  ASSERT_NE(original.pt, nullptr);

  const auto type = original.pt->getType();
  const int duration = original.pt->getDuration();
  const auto alignment = original.pt->getAlignment();
  const auto direction = original.pt->getDirection();
  const int angle = original.pt->getAngle();
  const double scale = original.pt->getScale();
  const auto rectangular = original.pt->isRectangular();
  const auto ok = original.pt->isOk();

  Poppler::PageTransitionData copied(original);
  ASSERT_NE(copied.pt, nullptr);

  EXPECT_EQ(copied.pt->getType(), type);
  EXPECT_EQ(copied.pt->getDuration(), duration);
  EXPECT_EQ(copied.pt->getAlignment(), alignment);
  EXPECT_EQ(copied.pt->getDirection(), direction);
  EXPECT_EQ(copied.pt->getAngle(), angle);
  EXPECT_EQ(copied.pt->getScale(), scale);
  EXPECT_EQ(copied.pt->isRectangular(), rectangular);
  EXPECT_EQ(copied.pt->isOk(), ok);
}

TEST_F(PageTransitionDataTest_2776, CopyConstructor_MultipleCopiesAreIndependent_2776)
{
  Object trans = MakeTransitionObject_2776();
  Poppler::PageTransitionData original(&trans);
  ASSERT_NE(original.pt, nullptr);

  Poppler::PageTransitionData copy1(original);
  Poppler::PageTransitionData copy2(original);

  ASSERT_NE(copy1.pt, nullptr);
  ASSERT_NE(copy2.pt, nullptr);

  // Boundary-ish: ensure each copy allocates its own transition.
  EXPECT_NE(copy1.pt, original.pt);
  EXPECT_NE(copy2.pt, original.pt);
  EXPECT_NE(copy1.pt, copy2.pt);

  // And they remain consistent in observable properties.
  EXPECT_EQ(copy1.pt->getType(), original.pt->getType());
  EXPECT_EQ(copy2.pt->getType(), original.pt->getType());
  EXPECT_EQ(copy1.pt->getDuration(), original.pt->getDuration());
  EXPECT_EQ(copy2.pt->getDuration(), original.pt->getDuration());
}

} // namespace