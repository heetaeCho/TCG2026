// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID=130
//
// Unit tests for BaseStream::getFileName() from poppler/Stream.h
// Constraints respected:
// - Treat implementation as black box
// - Test only observable behavior via public interface
// - No private/internal state access

#include <gtest/gtest.h>

#include "Stream.h" // ./TestProjects/poppler/poppler/Stream.h

namespace {

class BaseStreamTest_130 : public ::testing::Test {};

// A small derived class to verify virtual dispatch behavior.
class DerivedBaseStream_130 : public BaseStream {
public:
  explicit DerivedBaseStream_130(const char *name)
      : fileName_(std::make_unique<GooString>(name)) {}

  GooString *getFileName() override { return fileName_.get(); }

  GooString *stored() const { return fileName_.get(); }

private:
  std::unique_ptr<GooString> fileName_;
};

} // namespace

TEST_F(BaseStreamTest_130, DefaultGetFileNameReturnsNullptr_130) {
  BaseStream s;
  EXPECT_EQ(s.getFileName(), nullptr);

  // Boundary-ish: repeated calls should remain safe and consistently return nullptr
  // for the default implementation (observable behavior).
  EXPECT_EQ(s.getFileName(), nullptr);
}

TEST_F(BaseStreamTest_130, VirtualDispatchUsesOverride_130) {
  DerivedBaseStream_130 derived("example.pdf");

  BaseStream *asBase = &derived;
  GooString *name = asBase->getFileName();

  ASSERT_NE(name, nullptr);
  EXPECT_EQ(name, derived.stored()); // ensures the override is actually used
}