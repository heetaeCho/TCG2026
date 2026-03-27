// poppler-ps-file-init-test_2254.cc
//
// Tests for static poppler_ps_file_init() in poppler-document.cc.
//
// NOTE: poppler_ps_file_init() is a file-local (static) function, so to test it
// as implemented (without re-implementing logic), we include the production
// .cc file into this test translation unit.
//
// This is a common technique for unit-testing internal helpers while still
// treating them as a black box from the test's perspective (we only verify
// observable effects on the public struct fields).

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Detect whether PopplerPSFile has a member named `fd` (some versions do).
template <typename T, typename = void>
struct HasFdMember : std::false_type {};
template <typename T>
struct HasFdMember<T, std::void_t<decltype(std::declval<T&>().fd)>> : std::true_type {};

template <typename T, typename = void>
struct HasFirstLastPageMembers : std::false_type {};
template <typename T>
struct HasFirstLastPageMembers<
    T, std::void_t<decltype(std::declval<T&>().first_page), decltype(std::declval<T&>().last_page)>>
    : std::true_type {};

// Include the implementation to access the file-local function.
// Adjust include path if your build system requires a different relative path.
#include "poppler-document.cc"

namespace {

class PopplerPSFileInitTest_2254 : public ::testing::Test {};

TEST_F(PopplerPSFileInitTest_2254, SetsDefaultValuesOnFreshStruct_2254) {
  PopplerPSFile ps{};
  // Intentionally poison fields where possible before init to ensure init overwrites them.
  ps.out = reinterpret_cast<PSOutputDev*>(0x1);
  ps.filename = const_cast<char*>("not-null");
  ps.paper_width = 123.0;
  ps.paper_height = 456.0;
  ps.duplex = TRUE;

  if constexpr (HasFdMember<PopplerPSFile>::value) {
    ps.fd = 777;
  }

  poppler_ps_file_init(&ps);

  EXPECT_EQ(ps.out, nullptr);
  EXPECT_EQ(ps.filename, nullptr);
  EXPECT_EQ(ps.paper_width, -1);
  EXPECT_EQ(ps.paper_height, -1);
  EXPECT_EQ(ps.duplex, FALSE);

  if constexpr (HasFdMember<PopplerPSFile>::value) {
    EXPECT_EQ(ps.fd, -1);
  }
}

TEST_F(PopplerPSFileInitTest_2254, OverwritesPreExistingValues_2254) {
  PopplerPSFile ps{};
  // Fill with non-default values to ensure they get reset.
  ps.out = reinterpret_cast<PSOutputDev*>(0xDEADBEEF);
  ps.filename = reinterpret_cast<char*>(0xBAADF00D);
  ps.paper_width = 0.0;
  ps.paper_height = 0.0;
  ps.duplex = TRUE;

  if constexpr (HasFdMember<PopplerPSFile>::value) {
    ps.fd = 0;
  }

  poppler_ps_file_init(&ps);

  // Boundary-ish checks: ensure exact sentinel defaults are written.
  EXPECT_EQ(ps.out, nullptr);
  EXPECT_EQ(ps.filename, nullptr);
  EXPECT_DOUBLE_EQ(ps.paper_width, -1);
  EXPECT_DOUBLE_EQ(ps.paper_height, -1);
  EXPECT_EQ(ps.duplex, FALSE);

  if constexpr (HasFdMember<PopplerPSFile>::value) {
    EXPECT_EQ(ps.fd, -1);
  }
}

TEST_F(PopplerPSFileInitTest_2254, DoesNotModifyUnrelatedFieldsWhenPresent_2254) {
  PopplerPSFile ps{};

  // Some versions of PopplerPSFile contain document/first_page/last_page.
  // The provided init() snippet does not mention them; we only assert that
  // init() sets what it sets, and we avoid making assumptions about other fields.
  //
  // However, if first/last page members exist, we can safely ensure init() does
  // not accidentally clobber them by setting them to sentinel values and checking
  // they remain unchanged (observable behavior).
  if constexpr (HasFirstLastPageMembers<PopplerPSFile>::value) {
    ps.first_page = 11;
    ps.last_page = 22;
  }
  // document may exist; we avoid touching it unless present in type.
  // (No universal safe detection needed for this test.)

  poppler_ps_file_init(&ps);

  if constexpr (HasFirstLastPageMembers<PopplerPSFile>::value) {
    EXPECT_EQ(ps.first_page, 11);
    EXPECT_EQ(ps.last_page, 22);
  }
}

TEST_F(PopplerPSFileInitTest_2254, DeathOnNullPointer_2254) {
  // Exceptional/error case (observable): passing nullptr is invalid and should
  // crash/abort due to dereference. We verify this via a death test.
  //
  // If your build disables death tests or uses a different death style, you may
  // need to adjust gtest configuration.
  ASSERT_DEATH({ poppler_ps_file_init(nullptr); }, ".*");
}

}  // namespace