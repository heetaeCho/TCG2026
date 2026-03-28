// TEST_ID: 594
// File: test_memio_path_594.cpp

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "exiv2/basicio.hpp"

namespace {

using Exiv2::MemIo;

class MemIoTest_594 : public ::testing::Test {};

TEST_F(MemIoTest_594, PathIsNoexcept_594) {
  static_assert(noexcept(std::declval<const MemIo&>().path()),
                "MemIo::path() must be noexcept");
}

TEST_F(MemIoTest_594, PathReturnsExpectedValue_594) {
  MemIo io;
  EXPECT_EQ(io.path(), std::string("MemIo"));
}

TEST_F(MemIoTest_594, PathWorksOnConstObject_594) {
  const MemIo io;
  EXPECT_EQ(io.path(), std::string("MemIo"));
}

TEST_F(MemIoTest_594, PathIsStableAcrossMultipleCallsOnSameObject_594) {
  MemIo io;

  const std::string& p1 = io.path();
  const std::string& p2 = io.path();

  EXPECT_EQ(p1, std::string("MemIo"));
  EXPECT_EQ(p2, std::string("MemIo"));

  // Since the API returns a reference, repeated calls on the same object should
  // consistently reference the same string object (observable via address).
  EXPECT_EQ(&p1, &p2);
}

TEST_F(MemIoTest_594, PathMatchesAcrossDifferentObjects_594) {
  MemIo io1;
  MemIo io2;

  EXPECT_EQ(io1.path(), std::string("MemIo"));
  EXPECT_EQ(io2.path(), std::string("MemIo"));
  EXPECT_EQ(io1.path(), io2.path());
}

}  // namespace