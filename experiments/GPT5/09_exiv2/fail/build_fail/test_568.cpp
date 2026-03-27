// SPDX-License-Identifier: MIT
// TEST_ID 568
//
// Unit tests for Exiv2::FileIo::path() const noexcept
//
// Constraints respected:
// - Black-box testing via public interface only
// - No private/internal state access
// - No re-implementation of logic

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "exiv2/basicio.hpp"

namespace {

class FileIoPathTest_568 : public ::testing::Test {};

TEST_F(FileIoPathTest_568, PathReturnsConstructorArgument_568) {
  const std::string initial = "some/relative/path.jpg";
  Exiv2::FileIo io(initial);

  EXPECT_EQ(io.path(), initial);

  const Exiv2::FileIo& cio = io;
  EXPECT_EQ(cio.path(), initial);
}

TEST_F(FileIoPathTest_568, PathAcceptsEmptyString_568) {
  const std::string initial;
  Exiv2::FileIo io(initial);

  EXPECT_TRUE(io.path().empty());

  const Exiv2::FileIo& cio = io;
  EXPECT_TRUE(cio.path().empty());
}

TEST_F(FileIoPathTest_568, SetPathUpdatesReturnedPath_568) {
  Exiv2::FileIo io("before.dat");
  EXPECT_EQ(io.path(), "before.dat");

  const std::string after = "after.dat";
  io.setPath(after);

  EXPECT_EQ(io.path(), after);

  const Exiv2::FileIo& cio = io;
  EXPECT_EQ(cio.path(), after);
}

TEST_F(FileIoPathTest_568, PathHandlesLongString_568) {
  std::string longPath(4096, 'a');
  longPath += ".bin";

  Exiv2::FileIo io(longPath);
  EXPECT_EQ(io.path(), longPath);

  const Exiv2::FileIo& cio = io;
  EXPECT_EQ(cio.path(), longPath);
}

TEST_F(FileIoPathTest_568, PathHandlesNonAsciiCharacters_568) {
  // Use a UTF-8 string literal; behavior tested is purely that the same bytes are returned.
  const std::string utf8Path = u8"경로/파일/이미지-테스트.jpg";

  Exiv2::FileIo io(utf8Path);
  EXPECT_EQ(io.path(), utf8Path);

  io.setPath(std::string(u8"변경/후/경로.png"));
  EXPECT_EQ(io.path(), std::string(u8"변경/후/경로.png"));
}

TEST_F(FileIoPathTest_568, ConstPathIsNoexcept_568) {
  // This verifies the observable interface contract (noexcept) for the const overload.
  static_assert(noexcept(std::declval<const Exiv2::FileIo&>().path()),
                "Exiv2::FileIo::path() const should be noexcept");
}

TEST_F(FileIoPathTest_568, PathReturnsAReference_568) {
  Exiv2::FileIo io("ref-test.txt");

  const std::string& r = io.path();
  EXPECT_EQ(r, "ref-test.txt");

  // Verify it's a reference type at compile-time (interface-level property).
  static_assert(std::is_reference_v<decltype(std::declval<Exiv2::FileIo&>().path())>,
                "Exiv2::FileIo::path() should return a reference");
  static_assert(std::is_same_v<decltype(std::declval<Exiv2::FileIo&>().path()), const std::string&>,
                "Exiv2::FileIo::path() should return const std::string&");
}

}  // namespace