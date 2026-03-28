// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; -*-
// The TEST_ID is 161
//
// Unit tests for CachedFileStream::getStart() (black-box via public interface)

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <utility>

#include "poppler/Stream.h"

namespace {

class CachedFileStreamTest_161 : public ::testing::Test {
protected:
  // Helper to build a stream with minimal dependencies.
  static std::unique_ptr<CachedFileStream> MakeStream(Goffset start,
                                                      bool limited,
                                                      Goffset length) {
    std::shared_ptr<CachedFile> cc; // empty/null shared_ptr should be acceptable for getStart()
    Object dict;                    // default-constructed Object is sufficient as a placeholder
    return std::make_unique<CachedFileStream>(cc, start, limited, length, std::move(dict));
  }
};

TEST_F(CachedFileStreamTest_161, GetStartReturnsConstructorStart_161) {
  const Goffset start = static_cast<Goffset>(12345);
  auto stream = MakeStream(start, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(stream->getStart(), start);
}

TEST_F(CachedFileStreamTest_161, GetStartHandlesZeroStart_161) {
  const Goffset start = static_cast<Goffset>(0);
  auto stream = MakeStream(start, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(stream->getStart(), start);
}

TEST_F(CachedFileStreamTest_161, GetStartHandlesNegativeStart_161) {
  const Goffset start = static_cast<Goffset>(-7);
  auto stream = MakeStream(start, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(stream->getStart(), start);
}

TEST_F(CachedFileStreamTest_161, GetStartIsStableAndWorksViaBaseClass_161) {
  const Goffset start = std::numeric_limits<Goffset>::max();
  auto stream = MakeStream(start, /*limited=*/true, /*length=*/start);

  // Polymorphic dispatch check (observable behavior through the interface).
  BaseStream *base = stream.get();
  EXPECT_EQ(base->getStart(), start);

  // Stability: repeated calls should produce the same observable result.
  EXPECT_EQ(stream->getStart(), start);
  EXPECT_EQ(stream->getStart(), start);
}

} // namespace