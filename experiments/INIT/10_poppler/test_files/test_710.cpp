// Page_getBleedBox_710_test.cpp
// Unit tests for Page::getBleedBox() in ./TestProjects/poppler/poppler/Page.h
//
// Constraints respected:
// - Treat Page/PageAttrs as black boxes (no private access, no re-implementation).
// - Only use public interface and observable behavior.
// - Use death tests only for observable error behavior (nullptr dereference).

#include <gtest/gtest.h>

#include "Page.h"

namespace {

class PageTest_710 : public ::testing::Test {
protected:
  // Create a minimal Ref without assuming constructors beyond aggregate init.
  static Ref MakeRefZero() {
    Ref r{};
    return r;
  }
};

TEST_F(PageTest_710, Signature_ReturnsConstPDFRectanglePtr_710) {
  // Compile-time interface check: return type must be "const PDFRectangle*".
  using RetT = decltype(std::declval<const Page&>().getBleedBox());
  static_assert(std::is_same<RetT, const PDFRectangle*>::value,
                "Page::getBleedBox() must return const PDFRectangle*");
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PageTest_710, Death_NullAttrs_DereferenceIsObservable_710) {
  // Observable error case: passing a null attrs unique_ptr and calling getBleedBox()
  // should dereference a null pointer (as per the visible forwarding implementation).
  //
  // We intentionally leak the Page to avoid relying on destructor behavior
  // (constructor/destructor internals are out of scope for this interface test).
  PDFDoc* doc = nullptr;
  Object pageDict; // default-constructed placeholder
  Ref ref = MakeRefZero();

  auto page = new Page(doc, /*numA=*/1, std::move(pageDict), ref,
                       std::unique_ptr<PageAttrs>{}); // nullptr attrs

  EXPECT_DEATH(
      {
        (void)page->getBleedBox();
      },
      ".*");
}
#endif

TEST_F(PageTest_710, ForwardsToAttrsGetBleedBox_SamePointer_710) {
  // Normal operation: if we can construct Page with a non-null PageAttrs,
  // Page::getBleedBox() must forward to PageAttrs::getBleedBox().
  //
  // This checks observable behavior without inspecting internal state.
  PDFDoc* doc = nullptr;
  Object pageDict;
  Ref ref = MakeRefZero();

  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/nullptr);
  const PageAttrs* rawAttrs = attrs.get();

  // Leak Page to avoid relying on destructor behavior.
  auto page = new Page(doc, /*numA=*/1, std::move(pageDict), ref, std::move(attrs));

  const PDFRectangle* expected = rawAttrs->getBleedBox();
  const PDFRectangle* actual = page->getBleedBox();

  EXPECT_EQ(actual, expected);
}

TEST_F(PageTest_710, MultipleCalls_AreStableAndConsistent_710) {
  // Boundary/consistency: repeated calls should be consistent (no side effects observable).
  PDFDoc* doc = nullptr;
  Object pageDict;
  Ref ref = MakeRefZero();

  auto attrs = std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/nullptr);
  auto page = new Page(doc, /*numA=*/1, std::move(pageDict), ref, std::move(attrs));

  const PDFRectangle* first = page->getBleedBox();
  const PDFRectangle* second = page->getBleedBox();
  EXPECT_EQ(first, second);
}

} // namespace