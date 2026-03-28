// =================================================================================================
// TEST_ID: 617
// File: test_remoteio_path_617.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "exiv2/basicio.hpp"

namespace {

class RemoteIoPathTest_617 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoPathTest_617, NoexceptAtCompileTime_617) {
  // The partial implementation explicitly marks path() as noexcept.
  static_assert(noexcept(std::declval<const Exiv2::RemoteIo&>().path()),
                "RemoteIo::path() must be noexcept");
}

TEST_F(RemoteIoPathTest_617, ReturnsSameReferenceAcrossCalls_617) {
  const Exiv2::RemoteIo& cio = io_;

  const std::string& p1 = cio.path();
  const std::string& p2 = cio.path();

  // Observable behavior: repeated calls should refer to the same string object.
  EXPECT_EQ(&p1, &p2);

  // Minimal sanity: the returned reference is usable.
  // (We intentionally do not assume any specific content like empty/non-empty.)
  EXPECT_EQ(p1, p2);
}

TEST_F(RemoteIoPathTest_617, UsableOnConstObject_617) {
  const Exiv2::RemoteIo& cio = io_;
  EXPECT_NO_THROW({
    const std::string& p = cio.path();
    (void)p;
  });
}

TEST_F(RemoteIoPathTest_617, StableAcrossOpenCloseCalls_617) {
  const std::string& before = io_.path();

  // We don't assume open/close succeed or what they do internally; we only verify
  // that calling path() remains well-defined and stable as an observable handle.
  EXPECT_NO_THROW({
    (void)io_.open();
    (void)io_.close();
  });

  const std::string& after = io_.path();

  // Path reference should still be valid and (as a reference) stable.
  EXPECT_EQ(&before, &after);
  EXPECT_EQ(before, after);
}

}  // namespace