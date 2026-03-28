// File: test_basememstream_makesubstream_165.cpp
// TEST_ID is 165

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "poppler/Object.h"
#include "poppler/Stream.h"

namespace {

class BaseMemStreamMakeSubStreamTest_165 : public ::testing::Test {
protected:
  using Byte = unsigned char;

  void SetUp() override
  {
    // Fill buffer with deterministic, non-zero content (not strictly required for makeSubStream,
    // but useful for future extensions / sanity).
    buf_.resize(64);
    for (size_t i = 0; i < buf_.size(); ++i) {
      buf_[i] = static_cast<Byte>(i ^ 0xA5);
    }
  }

  std::unique_ptr<BaseMemStream<Byte>> MakeBaseMemStream(Goffset start, Goffset length, Object &&dict)
  {
    // BaseMemStream stores a raw pointer to the backing buffer. Keep buf_ alive for test duration.
    return std::make_unique<BaseMemStream<Byte>>(buf_.data(), start, length, std::move(dict));
  }

  static Object MakeNullDict()
  {
    return Object::null();
  }

  // Helper to get BaseStream interface from any Stream.
  static BaseStream *AsBaseStream(Stream *s)
  {
    if (!s) {
      return nullptr;
    }
    return s->getBaseStream();
  }

  std::vector<Byte> buf_;
};

TEST_F(BaseMemStreamMakeSubStreamTest_165, MakeSubStream_NotLimited_UsesRemainingLength_165)
{
  // Arrange
  const Goffset start = 10;
  const Goffset length = 20; // stream covers [10, 30)
  auto base = MakeBaseMemStream(start, length, MakeNullDict());

  const Goffset subStart = 15;          // inside range
  const bool limited = false;           // not limited
  const Goffset requestedLength = 999;  // should be ignored when not limited

  // Act
  std::unique_ptr<Stream> sub = base->makeSubStream(subStart, limited, requestedLength, MakeNullDict());

  // Assert (observable via BaseStream accessors)
  ASSERT_NE(sub, nullptr);
  BaseStream *subBase = AsBaseStream(sub.get());
  ASSERT_NE(subBase, nullptr);

  EXPECT_EQ(subBase->getStart(), subStart);
  EXPECT_EQ(subBase->getLength(), (start + length) - subStart);
}

TEST_F(BaseMemStreamMakeSubStreamTest_165, MakeSubStream_LimitedWithinBounds_UsesRequestedLength_165)
{
  // Arrange
  const Goffset start = 0;
  const Goffset length = 50; // stream covers [0, 50)
  auto base = MakeBaseMemStream(start, length, MakeNullDict());

  const Goffset subStart = 5;
  const bool limited = true;
  const Goffset requestedLength = 10; // fully within [5, 15)

  // Act
  std::unique_ptr<Stream> sub = base->makeSubStream(subStart, limited, requestedLength, MakeNullDict());

  // Assert
  ASSERT_NE(sub, nullptr);
  BaseStream *subBase = AsBaseStream(sub.get());
  ASSERT_NE(subBase, nullptr);

  EXPECT_EQ(subBase->getStart(), subStart);
  EXPECT_EQ(subBase->getLength(), requestedLength);
}

TEST_F(BaseMemStreamMakeSubStreamTest_165, MakeSubStream_LimitedBeyondEnd_ClampsToRemainingLength_165)
{
  // Arrange
  const Goffset start = 100;
  const Goffset length = 25; // stream covers [100, 125)
  auto base = MakeBaseMemStream(start, length, MakeNullDict());

  const Goffset subStart = 120;         // near end (remaining 5)
  const bool limited = true;
  const Goffset requestedLength = 50;   // extends beyond end

  // Act
  std::unique_ptr<Stream> sub = base->makeSubStream(subStart, limited, requestedLength, MakeNullDict());

  // Assert
  ASSERT_NE(sub, nullptr);
  BaseStream *subBase = AsBaseStream(sub.get());
  ASSERT_NE(subBase, nullptr);

  EXPECT_EQ(subBase->getStart(), subStart);
  EXPECT_EQ(subBase->getLength(), (start + length) - subStart);
}

TEST_F(BaseMemStreamMakeSubStreamTest_165, MakeSubStream_StartAtEnd_YieldsZeroLength_165)
{
  // Arrange
  const Goffset start = 7;
  const Goffset length = 13; // stream covers [7, 20)
  auto base = MakeBaseMemStream(start, length, MakeNullDict());

  const Goffset subStart = start + length; // exactly at end
  const bool limited = true;
  const Goffset requestedLength = 5;

  // Act
  std::unique_ptr<Stream> sub = base->makeSubStream(subStart, limited, requestedLength, MakeNullDict());

  // Assert
  ASSERT_NE(sub, nullptr);
  BaseStream *subBase = AsBaseStream(sub.get());
  ASSERT_NE(subBase, nullptr);

  EXPECT_EQ(subBase->getStart(), subStart);
  EXPECT_EQ(subBase->getLength(), 0);
}

TEST_F(BaseMemStreamMakeSubStreamTest_165, MakeSubStream_AcceptsMovedDictObject_165)
{
  // Arrange
  auto base = MakeBaseMemStream(/*start=*/0, /*length=*/32, MakeNullDict());

  // Use an observable Object value type (int) so we can verify it survives the move into the substream.
  Object movedDict(123);

  // Act
  std::unique_ptr<Stream> sub = base->makeSubStream(/*startA=*/0, /*limited=*/true, /*lengthA=*/1, std::move(movedDict));

  // Assert
  ASSERT_NE(sub, nullptr);

  // The substream should expose its dict object via BaseStream::getDictObject().
  BaseStream *subBase = AsBaseStream(sub.get());
  ASSERT_NE(subBase, nullptr);

  Object *dictObj = subBase->getDictObject();
  ASSERT_NE(dictObj, nullptr);
  ASSERT_TRUE(dictObj->isInt());
  EXPECT_EQ(dictObj->getInt(), 123);
}

} // namespace