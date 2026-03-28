// File: prefilter_dtor_test.cc
#include <gtest/gtest.h>
#include "re2/prefilter.h"

namespace {

using re2::Prefilter;

// Helper to create a Prefilter with a valid Op without depending on enum names.
// We avoid inferring semantics and just use a dummy enum value.
static Prefilter::Op AnyOp() {
  return static_cast<Prefilter::Op>(0);
}

// -----------------------------------------------------------------------------
// 1) Normal case: Construct and destroy with default state (subs_ is null).
// -----------------------------------------------------------------------------
TEST(PrefilterDestructor_536, DestroyWithNullSubs_DoesNotCrash_536) {
  // Construction & scope-based destruction should be safe with default state.
  { Prefilter p(AnyOp()); }
  SUCCEED();  // If we reach here, no crash occurred.
}

// -----------------------------------------------------------------------------
// 2) Boundary case: Explicitly set an empty subs_ vector, then destroy.
// -----------------------------------------------------------------------------
TEST(PrefilterDestructor_536, DestroyWithEmptySubsVector_DoesNotCrash_536) {
  Prefilter* parent = new Prefilter(AnyOp());
  // Give ownership of an empty vector to the object under test.
  auto* empty_vec = new std::vector<Prefilter*>();
  parent->set_subs(empty_vec);

  // Deleting parent should delete the vector it owns and not crash.
  delete parent;
  SUCCEED();
}

// -----------------------------------------------------------------------------
// 3) Ownership case: Set a non-empty subs_ vector of Prefilter* and destroy.
//    Expect the parent to clean up owned children and the vector without crash.
// -----------------------------------------------------------------------------
TEST(PrefilterDestructor_536, DestroyWithOwnedChildren_DoesNotCrash_536) {
  Prefilter* parent = new Prefilter(AnyOp());

  auto* subs = new std::vector<Prefilter*>();
  subs->push_back(new Prefilter(AnyOp()));
  subs->push_back(new Prefilter(AnyOp()));
  subs->push_back(new Prefilter(AnyOp()));

  parent->set_subs(subs);

  // Deleting parent should delete each child Prefilter* in subs and the vector.
  // We do NOT access children afterward (would be undefined behavior).
  delete parent;

  // If the destructor double-deleted or leaked in observable ways,
  // we would likely see a crash in typical test runners; here we just assert
  // the observable "no-crash" behavior per the interface.
  SUCCEED();
}

}  // namespace
