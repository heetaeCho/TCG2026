// File: prog_bytemap_test.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

class ProgBytemapTest_129 : public ::testing::Test {
protected:
  Prog prog_;  // Default-constructed; we only use public API.
};

// 1) Basic contract: returns a non-null pointer.
TEST_F(ProgBytemapTest_129, BytemapReturnsNonNull_129) {
  const uint8_t* p = prog_.bytemap();
  ASSERT_NE(p, nullptr) << "bytemap() should return a valid pointer";
}

// 2) Stability: multiple calls return the same pointer (interface-level stability).
TEST_F(ProgBytemapTest_129, BytemapPointerStableAcrossCalls_129) {
  const uint8_t* p1 = prog_.bytemap();
  const uint8_t* p2 = prog_.bytemap();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2) << "bytemap() should consistently return the same address for a given Prog instance";
}

// 3) Distinct instances: pointers from different objects may be different.
// We don't *require* they differ (implementations could share storage),
// but it's valid to allow equality, so we only assert both are non-null.
TEST_F(ProgBytemapTest_129, BytemapFromDifferentInstancesIsValid_129) {
  Prog other;
  const uint8_t* p_this = prog_.bytemap();
  const uint8_t* p_other = other.bytemap();
  ASSERT_NE(p_this, nullptr);
  ASSERT_NE(p_other, nullptr);
  // No expectation on equality vs. inequality to avoid assuming internal storage strategy.
}

// 4) Const-correctness / read-only behavior from the interface perspective:
// We ensure the function is callable and returns a pointer-to-const.
// (We do not attempt to write through it or assume size/layout.)
TEST_F(ProgBytemapTest_129, BytemapIsPointerToConst_129) {
  const uint8_t* p = prog_.bytemap();
  static_assert(std::is_same<decltype(p), const uint8_t*>::value,
                "bytemap() must return const uint8_t*");
  ASSERT_NE(p, nullptr);
}

}  // namespace re2
