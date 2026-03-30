// BoundRefTest_659.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the provided interface header (path per your repo layout)
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::BoundRef;

// ---- Compile-time interface checks (do not re-implement logic) ----

// BoundRef should be non-copyable (inherits NonCopyable).
static_assert(!std::is_copy_constructible<BoundRef>::value,
              "BoundRef must not be copy-constructible");
static_assert(!std::is_copy_assignable<BoundRef>::value,
              "BoundRef must not be copy-assignable");

// BoundRef declares a virtual destructor in the interface.
static_assert(std::has_virtual_destructor<BoundRef>::value,
              "BoundRef should have a virtual destructor");

class BoundRefTest_659 : public ::testing::Test {
protected:
  // Helper derived type used only to verify virtual dispatch of isFlag()
  // (does not simulate internal behavior of BoundRef).
  struct DerivedTrueFlag final : BoundRef {
    // Override through the public virtual interface to ensure calls dispatch.
    bool isFlag() const override { return true; }
    // Note: We do NOT override or call any other behavior.
  };
};

// Normal operation: default isFlag() behavior from the implementation should be observable.
TEST_F(BoundRefTest_659, DefaultIsFlagFalse_659) {
  const BoundRef obj;
  // Observable behavior: return value from public interface.
  EXPECT_FALSE(obj.isFlag()) << "BoundRef::isFlag() should report not-a-flag by default";
}

// Boundary-ish / const-correctness: ensure calling on a const object works.
TEST_F(BoundRefTest_659, IsFlagCallableOnConstObject_659) {
  const BoundRef obj;
  // Just exercise the API on a const instance and assert the observable return.
  EXPECT_FALSE(obj.isFlag());
}

// Virtual dispatch verification: calling through base should respect overrides.
TEST_F(BoundRefTest_659, IsFlagVirtualDispatch_659) {
  const BoundRefTest_659::DerivedTrueFlag derived;
  const BoundRef& as_base = derived;  // upcast to interface
  // Observable effect: overridden return value is seen via the base reference.
  EXPECT_TRUE(as_base.isFlag());
}

// Non-copyable contract (runtime-enforced via type traits; compile-time already checked above).
TEST_F(BoundRefTest_659, NonCopyableContract_659) {
  EXPECT_FALSE((std::is_copy_constructible<BoundRef>::value));
  EXPECT_FALSE((std::is_copy_assignable<BoundRef>::value));
}

// Destructor contract: verify via type trait at runtime (complements static_assert).
TEST_F(BoundRefTest_659, HasVirtualDestructor_659) {
  EXPECT_TRUE((std::has_virtual_destructor<BoundRef>::value));
}
