// ============================================================================
// TEST_ID 914
// File: test_canonmn_int_914.cpp
// ----------------------------------------------------------------------------
// Unit tests for Exiv2::Internal::CanonMakerNote (partial interface)
// Constraints respected:
//  - Treat implementation as a black box
//  - Test only observable behavior via public/static interface
//  - No private/internal state access
// ============================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>
#include <utility>
#include <vector>

#include "canonmn_int.hpp"

// Exiv2 public headers for Value / ExifData construction
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

// --- SFINAE helpers (C++17) --------------------------------------------------

template <typename T, typename = void>
struct HasEqualOperator : std::false_type {};
template <typename T>
struct HasEqualOperator<T, decltype(void(std::declval<T>() == std::declval<T>()))> : std::true_type {};
template <typename T>
constexpr bool HasEqualOperator_v = HasEqualOperator<T>::value;

template <typename T>
using DecayedT = typename std::decay<T>::type;

// --- Value construction helpers ---------------------------------------------

// Creates a Value with optional components. Uses Exiv2's factory if available.
static Exiv2::Value::UniquePtr makeUShortValue(std::initializer_list<uint16_t> comps) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  for (uint16_t x : comps) {
    v->read(reinterpret_cast<const Exiv2::byte*>(&x), sizeof(x), Exiv2::littleEndian);
  }
  return v;
}

static Exiv2::Value::UniquePtr makeUShortValueBySet(std::initializer_list<uint16_t> comps) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  // Prefer set() if available/works; fall back to read() above in case set is not supported.
  // This path is used only in tests that want "some value present" without assuming encoding.
  if (!comps.size()) return v;
  // Build a string like "1 2 3" which many Exiv2 Value types accept.
  std::ostringstream os;
  bool first = true;
  for (auto x : comps) {
    if (!first) os << ' ';
    os << x;
    first = false;
  }
  (void)v->read(os.str());
  return v;
}

// --- Print function pointer type --------------------------------------------

using PrintFn = std::ostream& (*)(std::ostream&, const Exiv2::Value&, const Exiv2::ExifData*);

struct PrintCase {
  const char* name;
  PrintFn fn;
};

// Keep the list small-but-representative while still covering multiple entry points.
static std::vector<PrintCase> allPrintFns() {
  using Exiv2::Internal::CanonMakerNote;
  return {
      {"printFiFileNumber", &CanonMakerNote::printFiFileNumber},
      {"printFocalLength", &CanonMakerNote::printFocalLength},
      {"print0x0008", &CanonMakerNote::print0x0008},
      {"print0x000a", &CanonMakerNote::print0x000a},
      {"print0x000c", &CanonMakerNote::print0x000c},
      {"printCs0x0002", &CanonMakerNote::printCs0x0002},
      {"printCsLensType", &CanonMakerNote::printCsLensType},
      {"printCsLens", &CanonMakerNote::printCsLens},
      {"printLe0x0000", &CanonMakerNote::printLe0x0000},
      {"printSi0x0001", &CanonMakerNote::printSi0x0001},
      {"printSi0x0002", &CanonMakerNote::printSi0x0002},
      {"printSi0x0003", &CanonMakerNote::printSi0x0003},
      {"printSi0x0009", &CanonMakerNote::printSi0x0009},
      {"printSi0x000c", &CanonMakerNote::printSi0x000c},
      {"printSi0x000d", &CanonMakerNote::printSi0x000d},
      {"printSi0x000e", &CanonMakerNote::printSi0x000e},
      {"printSi0x0013", &CanonMakerNote::printSi0x0013},
      {"printSi0x0015", &CanonMakerNote::printSi0x0015},
      {"printSi0x0016", &CanonMakerNote::printSi0x0016},
      {"printSi0x0017", &CanonMakerNote::printSi0x0017},
      {"printSi0x0018", &CanonMakerNote::printSi0x0018},
      {"printFiFocusDistance", &CanonMakerNote::printFiFocusDistance},
  };
}

class CanonMakerNoteTest_914 : public ::testing::Test {};

// -----------------------------------------------------------------------------
// tagListTi() tests
// -----------------------------------------------------------------------------

TEST_F(CanonMakerNoteTest_914, TagListTi_IsCallableAndStableAcrossCalls_914) {
  using Exiv2::Internal::CanonMakerNote;

  // Must be callable.
  auto a = CanonMakerNote::tagListTi();
  auto b = CanonMakerNote::tagListTi();

  // If comparable, it should be stable across repeated calls.
  using T = DecayedT<decltype(a)>;
  if constexpr (std::is_pointer<T>::value) {
    EXPECT_EQ(a, b);
  } else if constexpr (HasEqualOperator_v<T>) {
    EXPECT_TRUE(a == b);
  } else {
    // Not comparable: we can still assert that the type is consistent and the call succeeds.
    SUCCEED();
  }
}

TEST_F(CanonMakerNoteTest_914, TagListTi_CanBeUsedInConstexprContext_914) {
  using Exiv2::Internal::CanonMakerNote;

  // This test is compile-time oriented: if the return can be constexpr-initialized, it compiles.
  // We avoid asserting specific contents or sizes (black-box constraint).
  constexpr auto v = CanonMakerNote::tagListTi();
  (void)v;

  SUCCEED();
}

// -----------------------------------------------------------------------------
// print*() tests (normal / boundary / error-ish cases via nullptr metadata)
// -----------------------------------------------------------------------------

TEST_F(CanonMakerNoteTest_914, PrintFunctions_ReturnSameStreamAndDoNotThrow_WithNullMetadata_914) {
  const auto cases = allPrintFns();

  // "Normal operation": provide a non-empty Value and null metadata pointer.
  auto vOwned = makeUShortValueBySet({1});
  ASSERT_TRUE(vOwned.get() != nullptr);
  const Exiv2::Value& v = *vOwned;

  for (const auto& c : cases) {
    SCOPED_TRACE(c.name);

    std::ostringstream os;
    std::ostream* osAddrBefore = &os;

    EXPECT_NO_THROW({
      std::ostream& out = c.fn(os, v, nullptr);
      EXPECT_EQ(&out, osAddrBefore);  // observable behavior: returns the same stream reference
    });

    // Do not assume output content, but stream should remain usable.
    EXPECT_FALSE(os.fail());
  }
}

TEST_F(CanonMakerNoteTest_914, PrintFunctions_HandleEmptyValue_BoundaryCase_914) {
  const auto cases = allPrintFns();

  // "Boundary": empty Value (no components).
  auto emptyOwned = makeUShortValueBySet({});
  ASSERT_TRUE(emptyOwned.get() != nullptr);
  const Exiv2::Value& emptyV = *emptyOwned;

  Exiv2::ExifData exif;  // empty metadata object

  for (const auto& c : cases) {
    SCOPED_TRACE(c.name);

    std::ostringstream os;
    std::ostream* osAddrBefore = &os;

    EXPECT_NO_THROW({
      std::ostream& out = c.fn(os, emptyV, &exif);
      EXPECT_EQ(&out, osAddrBefore);
    });

    // Still should be a valid stream after invocation.
    EXPECT_FALSE(os.bad());
  }
}

TEST_F(CanonMakerNoteTest_914, PrintFunctions_TolerateNullMetadataPointer_AsErrorCaseSurface_914) {
  const auto cases = allPrintFns();

  // "Exceptional or error case (if observable)": pass nullptr metadata and a Value that may be
  // minimally initialized. We only assert no-throw and stream reference behavior.
  auto vOwned = makeUShortValueBySet({0});  // often a boundary-like value
  ASSERT_TRUE(vOwned.get() != nullptr);
  const Exiv2::Value& v = *vOwned;

  for (const auto& c : cases) {
    SCOPED_TRACE(c.name);

    std::ostringstream os;
    std::ostream* osAddrBefore = &os;

    EXPECT_NO_THROW({
      std::ostream& out = c.fn(os, v, nullptr);
      EXPECT_EQ(&out, osAddrBefore);
    });
  }
}