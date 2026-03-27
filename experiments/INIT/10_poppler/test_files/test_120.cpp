// TEST_ID: 120
// Unit tests for Stream::fillString(std::string&)
//
// File: Stream_fillString_120_test.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

// Adjust include path as needed for your build.
#include "Stream.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Return;

namespace {

class MockStreamFillString_120 : public Stream {
public:
  MockStreamFillString_120() = default;
  ~MockStreamFillString_120() override = default;

  MOCK_METHOD(bool, rewind, (), (override));

  // These are private virtuals in Stream, but overriding them in a derived class is allowed.
  MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));
  MOCK_METHOD(bool, hasGetChars, (), (override));
};

static void CopyToBuffer(unsigned char *dst, const std::string &src, int n) {
  ASSERT_NE(dst, nullptr);
  ASSERT_GE(n, 0);
  ASSERT_LE(static_cast<size_t>(n), src.size());
  if (n > 0) {
    std::memcpy(dst, src.data(), static_cast<size_t>(n));
  }
}

class StreamFillStringTest_120 : public ::testing::Test {
protected:
  // Sets up getChars() to return the provided chunks sequentially, then 0.
  static void SetupChunkedReads(MockStreamFillString_120 &ms,
                                std::vector<std::string> chunks) {
    // Keep state in a shared object captured by lambdas.
    struct State {
      std::vector<std::string> chunks;
      size_t idx = 0;
    };
    auto state = std::make_shared<State>();
    state->chunks = std::move(chunks);

    ON_CALL(ms, hasGetChars()).WillByDefault(Return(true));
    ON_CALL(ms, getChars(_, _))
        .WillByDefault(Invoke([state](int nChars, unsigned char *buffer) -> int {
          if (state->idx >= state->chunks.size()) {
            return 0;
          }
          const std::string &chunk = state->chunks[state->idx++];
          const int toCopy =
              std::min<int>(nChars, static_cast<int>(chunk.size()));
          CopyToBuffer(buffer, chunk, toCopy);
          return toCopy;
        }));
  }
};

} // namespace

TEST_F(StreamFillStringTest_120, RewindFalseClearsStringAndDoesNotRead_120) {
  MockStreamFillString_120 ms;
  std::string s = "already here";

  EXPECT_CALL(ms, rewind()).WillOnce(Return(false));
  EXPECT_CALL(ms, hasGetChars()).Times(0);
  EXPECT_CALL(ms, getChars(_, _)).Times(0);

  ms.fillString(s);
  EXPECT_TRUE(s.empty());
}

TEST_F(StreamFillStringTest_120, EmptyStreamProducesEmptyString_120) {
  MockStreamFillString_120 ms;
  std::string s; // initially empty

  EXPECT_CALL(ms, rewind()).WillOnce(Return(true));
  EXPECT_CALL(ms, hasGetChars()).WillRepeatedly(Return(true));
  EXPECT_CALL(ms, getChars(_, _))
      .WillOnce(Return(0)); // immediate EOF

  ms.fillString(s);
  EXPECT_TRUE(s.empty());
}

TEST_F(StreamFillStringTest_120, AppendsToExistingStringOnSuccessfulRewind_120) {
  MockStreamFillString_120 ms;
  std::string s = "prefix-";

  SetupChunkedReads(ms, {"abc", "DEF"});

  EXPECT_CALL(ms, rewind()).WillOnce(Return(true));
  // We expect reads until 0; the default handler returns 0 after chunks consumed.
  EXPECT_CALL(ms, getChars(_, _)).Times(3);

  ms.fillString(s);
  EXPECT_EQ(s, "prefix-abcDEF");
}

TEST_F(StreamFillStringTest_120, ReadsMultipleChunksAndConcatenatesInOrder_120) {
  MockStreamFillString_120 ms;
  std::string s;

  SetupChunkedReads(ms, {"Hello", ", ", "world", "!"});

  EXPECT_CALL(ms, rewind()).WillOnce(Return(true));
  EXPECT_CALL(ms, getChars(_, _)).Times(5);

  ms.fillString(s);
  EXPECT_EQ(s, "Hello, world!");
}

TEST_F(StreamFillStringTest_120, HandlesLargeDataWithMultipleReadIterations_120) {
  MockStreamFillString_120 ms;
  std::string s;

  // Create > 4096 bytes to force looping.
  std::string a(4096, 'A');
  std::string b(123, 'B');
  SetupChunkedReads(ms, {a, b});

  EXPECT_CALL(ms, rewind()).WillOnce(Return(true));

  // Verify the size argument passed to getChars is never <= 0 and buffer is non-null.
  // We avoid assuming it is exactly 4096 (implementation detail of doGetChars).
  EXPECT_CALL(ms, getChars(_, _))
      .WillRepeatedly(Invoke([&](int nChars, unsigned char *buffer) -> int {
        EXPECT_GT(nChars, 0);
        EXPECT_NE(buffer, nullptr);

        static int call = 0;
        ++call;
        if (call == 1) {
          const int toCopy = std::min<int>(nChars, static_cast<int>(a.size()));
          CopyToBuffer(buffer, a, toCopy);
          return toCopy;
        }
        if (call == 2) {
          const int toCopy = std::min<int>(nChars, static_cast<int>(b.size()));
          CopyToBuffer(buffer, b, toCopy);
          return toCopy;
        }
        return 0;
      }));

  ms.fillString(s);
  EXPECT_EQ(s.size(), a.size() + b.size());
  EXPECT_EQ(s.substr(0, a.size()), a);
  EXPECT_EQ(s.substr(a.size()), b);
}

TEST_F(StreamFillStringTest_120, CallsRewindBeforeAnyReads_120) {
  MockStreamFillString_120 ms;
  std::string s;

  SetupChunkedReads(ms, {"X"});

  InSequence seq;
  EXPECT_CALL(ms, rewind()).WillOnce(Return(true));
  EXPECT_CALL(ms, getChars(_, _)).Times(2); // "X", then 0 from default handler

  ms.fillString(s);
  EXPECT_EQ(s, "X");
}