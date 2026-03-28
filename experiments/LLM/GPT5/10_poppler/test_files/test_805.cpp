// TEST_ID 805
//
// Unit tests for AnnotMarkup::getExData()
// File: annotmarkup_getexdata_test_805.cc

#include <gtest/gtest.h>

#include <type_traits>

#include "poppler/Annot.h"

namespace {

// Detect whether T is default-constructible (some builds may provide a reduced/partial class).
template <typename T>
constexpr bool kDefaultConstructible = std::is_default_constructible<T>::value;

} // namespace

class AnnotMarkupTest_805 : public ::testing::Test {};

TEST_F(AnnotMarkupTest_805, GetExData_IsStableAcrossMultipleCalls_805) {
  if constexpr (!kDefaultConstructible<AnnotMarkup>) {
    GTEST_SKIP() << "AnnotMarkup is not default-constructible in this build; "
                    "cannot instantiate safely via public interface here.";
  } else {
    AnnotMarkup m;

    const AnnotExternalDataType v1 = m.getExData();
    const AnnotExternalDataType v2 = m.getExData();
    const AnnotExternalDataType v3 = m.getExData();

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v2, v3);
  }
}

TEST_F(AnnotMarkupTest_805, GetExData_WorksOnConstObject_805) {
  if constexpr (!kDefaultConstructible<AnnotMarkup>) {
    GTEST_SKIP() << "AnnotMarkup is not default-constructible in this build; "
                    "cannot instantiate safely via public interface here.";
  } else {
    const AnnotMarkup m;

    // Smoke + const-correctness: should compile and return an enum value.
    const AnnotExternalDataType v = m.getExData();
    (void)v;

    // Also ensure calling repeatedly on const object is stable.
    EXPECT_EQ(m.getExData(), m.getExData());
  }
}