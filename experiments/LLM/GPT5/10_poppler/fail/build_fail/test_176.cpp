// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for EmbedStream::getKind()
// The TEST_ID is 176

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler/Stream.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Poppler's Stream interface is large, but (in the real codebase) it provides
// default implementations for most virtual functions. For these tests we only
// need to control/observe getKind().
class MockStreamForKind_176 : public Stream {
public:
  MOCK_METHOD(StreamKind, getKind, (), (const, override));
};

class EmbedStreamTest_176 : public ::testing::Test {
protected:
  static Object MakeEmptyDictObject_176()
  {
    // We intentionally do not assume any internal semantics; we just need an
    // Object instance to satisfy the constructor signature.
    //
    // In Poppler, Object is a value type; default construction should be valid.
    Object o;
    return o;
  }
};

TEST_F(EmbedStreamTest_176, GetKindDelegatesToWrappedStream_176)
{
  StrictMock<MockStreamForKind_176> wrapped;

  // Choose any StreamKind enumerator that exists in the codebase.
  // We avoid guessing enum values; just use a valid one.
  const StreamKind expectedKind = strWeird; // commonly present in Poppler

  EXPECT_CALL(wrapped, getKind()).Times(1).WillOnce(Return(expectedKind));

  Object dict = MakeEmptyDictObject_176();
  EmbedStream es(&wrapped, std::move(dict), /*limitedA=*/false, /*lengthA=*/0, /*reusableA=*/false);

  EXPECT_EQ(es.getKind(), expectedKind);
}

TEST_F(EmbedStreamTest_176, GetKindMultipleCallsForwardEachTime_176)
{
  StrictMock<MockStreamForKind_176> wrapped;

  const StreamKind firstKind = strWeird;
  const StreamKind secondKind = strWeird;

  // Observable behavior: calling EmbedStream::getKind() should consult the wrapped
  // stream. We verify the external interaction via call counts.
  EXPECT_CALL(wrapped, getKind())
      .Times(2)
      .WillOnce(Return(firstKind))
      .WillOnce(Return(secondKind));

  Object dict = MakeEmptyDictObject_176();
  EmbedStream es(&wrapped, std::move(dict), /*limitedA=*/false, /*lengthA=*/0, /*reusableA=*/false);

  EXPECT_EQ(es.getKind(), firstKind);
  EXPECT_EQ(es.getKind(), secondKind);
}

} // namespace