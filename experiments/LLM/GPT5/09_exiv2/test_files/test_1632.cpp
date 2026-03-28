// File: test_tiffvisitor_int_tifffinder_visitdataentry_1632.cpp
// Unit tests for Exiv2::Internal::TiffFinder::visitDataEntry
//
// Constraints honored:
// - Treat implementation as black box
// - Only test observable behavior via public interface
// - No private-state access
// - Boundary/error cases: nullptr input, repeated calls, re-init

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"   // Exiv2::Internal::TiffFinder, TiffDataEntry
#include "types.hpp"             // Exiv2::IfdId (expected to exist in Exiv2)

namespace {

class TiffFinderVisitDataEntryTest_1632 : public ::testing::Test {
protected:
  static Exiv2::IfdId AnyIfd() {
    // Avoid relying on specific enumerators; use a well-defined cast.
    return static_cast<Exiv2::IfdId>(0);
  }
};

TEST_F(TiffFinderVisitDataEntryTest_1632, ConstructAndResultCallable_1632) {
  Exiv2::Internal::TiffFinder finder(/*tag=*/0, AnyIfd());

  // Observable behavior: result() is callable and returns a pointer.
  // We do not assume what the pointer should be beyond type-safety.
  Exiv2::Internal::TiffComponent* res = nullptr;
  EXPECT_NO_THROW(res = finder.result());
  (void)res;
}

TEST_F(TiffFinderVisitDataEntryTest_1632, VisitDataEntryAcceptsNullptr_1632) {
  Exiv2::Internal::TiffFinder finder(/*tag=*/0, AnyIfd());

  // Boundary / error-style case: nullptr passed through interface.
  // Expectation: call should be safe (no crash/throw) as an observable contract.
  EXPECT_NO_THROW(finder.visitDataEntry(nullptr));
}

TEST_F(TiffFinderVisitDataEntryTest_1632, VisitDataEntryNullptrDoesNotCorruptResultCallable_1632) {
  Exiv2::Internal::TiffFinder finder(/*tag=*/0, AnyIfd());

  Exiv2::Internal::TiffComponent* before = nullptr;
  Exiv2::Internal::TiffComponent* after  = nullptr;

  EXPECT_NO_THROW(before = finder.result());
  EXPECT_NO_THROW(finder.visitDataEntry(nullptr));
  EXPECT_NO_THROW(after = finder.result());

  // We do not infer internal matching logic. For nullptr input, a conservative
  // observable check is that result() remains a valid pointer value and is stable.
  EXPECT_EQ(before, after);
}

TEST_F(TiffFinderVisitDataEntryTest_1632, RepeatedVisitDataEntryNullptrIsStable_1632) {
  Exiv2::Internal::TiffFinder finder(/*tag=*/0, AnyIfd());

  Exiv2::Internal::TiffComponent* r0 = nullptr;
  Exiv2::Internal::TiffComponent* r1 = nullptr;
  Exiv2::Internal::TiffComponent* r2 = nullptr;

  EXPECT_NO_THROW(r0 = finder.result());
  EXPECT_NO_THROW(finder.visitDataEntry(nullptr));
  EXPECT_NO_THROW(r1 = finder.result());
  EXPECT_NO_THROW(finder.visitDataEntry(nullptr));
  EXPECT_NO_THROW(r2 = finder.result());

  EXPECT_EQ(r0, r1);
  EXPECT_EQ(r1, r2);
}

TEST_F(TiffFinderVisitDataEntryTest_1632, InitThenVisitDataEntryNullptrDoesNotThrow_1632) {
  Exiv2::Internal::TiffFinder finder(/*tag=*/1, AnyIfd());

  // Normal operation: init() is part of the public interface; verify it is callable.
  EXPECT_NO_THROW(finder.init(/*tag=*/2, AnyIfd()));

  // Boundary: nullptr input after re-init.
  EXPECT_NO_THROW(finder.visitDataEntry(nullptr));

  // And result remains callable.
  EXPECT_NO_THROW((void)finder.result());
}

}  // namespace