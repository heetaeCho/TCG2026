// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_remoteio_615.cpp
//
// Unit tests for Exiv2::RemoteIo (black-box tests based only on public interface)
//
// TEST_ID: 615

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

namespace {

class RemoteIoTest_615 : public ::testing::Test {
 protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_615, ErrorReturnsZeroByDefault_615) {
  // Observable behavior from provided implementation in basicio.cpp:
  // int RemoteIo::error() const { return 0; }
  EXPECT_EQ(0, io_.error());
}

TEST_F(RemoteIoTest_615, ErrorIsStableAcrossRepeatedCalls_615) {
  // Boundary-ish check: repeated calls should be consistent for a pure getter.
  const int first = io_.error();
  const int second = io_.error();
  const int third = io_.error();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(0, third);
}

TEST_F(RemoteIoTest_615, ErrorCallableThroughConstReference_615) {
  // Ensures const-correctness is usable from the interface.
  const Exiv2::RemoteIo& cref = io_;
  EXPECT_EQ(0, cref.error());
}

TEST_F(RemoteIoTest_615, ErrorCallableThroughBaseReferenceIfAvailable_615) {
  // If RemoteIo is a BasicIo, error() should be callable polymorphically.
  // This test only relies on the public interface (virtual override in header).
  Exiv2::BasicIo& base = io_;
  EXPECT_EQ(0, base.error());
}

}  // namespace