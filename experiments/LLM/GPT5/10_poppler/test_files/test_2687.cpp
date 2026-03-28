// File: test_pdfsig_textstringtoutf8_2687.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

// ---- Test seams for external deps used by TextStringToUTF8() ----
// We intentionally provide minimal stand-ins for the dependencies that
// TextStringToUTF8() uses (globalParams, UnicodeMap, TextStringToUCS4).
// This is NOT re-implementing the function under test; it only supplies
// collaborators so we can observe interactions.

using Unicode = std::uint32_t;

class UnicodeMap {
public:
  virtual ~UnicodeMap() = default;
  virtual int mapUnicode(Unicode u, char *buf, int bufSize) const = 0;
};

class GlobalParams {
public:
  virtual ~GlobalParams() = default;
  virtual const UnicodeMap *getUtf8Map() const = 0;
};

// The function under test references `globalParams` directly.
GlobalParams *globalParams = nullptr;

// The function under test references `TextStringToUCS4(str)`.
static std::function<std::vector<Unicode>(const std::string &)> g_TextStringToUCS4Hook;

static std::vector<Unicode> TextStringToUCS4(const std::string &str) {
  if (g_TextStringToUCS4Hook) {
    return g_TextStringToUCS4Hook(str);
  }
  return {};
}

class MockUnicodeMap final : public UnicodeMap {
public:
  MOCK_METHOD(int, mapUnicode, (Unicode u, char *buf, int bufSize), (const, override));
};

class MockGlobalParams final : public GlobalParams {
public:
  MOCK_METHOD(const UnicodeMap *, getUtf8Map, (), (const, override));
};

// ---- Include the implementation TU so we can call the file-local static ----
// This is the standard technique to test file-local `static` helpers.
#include "TestProjects/poppler/utils/pdfsig.cc"

// ---- Tests ----

class TextStringToUTF8Test_2687 : public ::testing::Test {
protected:
  void TearDown() override {
    // Reset global seam state so tests don't affect each other.
    globalParams = nullptr;
    g_TextStringToUCS4Hook = nullptr;
  }
};

TEST_F(TextStringToUTF8Test_2687, EmptyUCS4VectorReturnsEmptyAndDoesNotMap_2687) {
  StrictMock<MockGlobalParams> gp;
  StrictMock<MockUnicodeMap> map;

  globalParams = &gp;

  EXPECT_CALL(gp, getUtf8Map()).WillOnce(Return(&map));
  EXPECT_CALL(map, mapUnicode(_, _, _)).Times(0);

  g_TextStringToUCS4Hook = [](const std::string &) { return std::vector<Unicode>{}; };

  const std::string out = TextStringToUTF8("anything");
  EXPECT_TRUE(out.empty());
}

TEST_F(TextStringToUTF8Test_2687, SingleCodepointAppendsMappedBytes_2687) {
  StrictMock<MockGlobalParams> gp;
  StrictMock<MockUnicodeMap> map;

  globalParams = &gp;

  EXPECT_CALL(gp, getUtf8Map()).WillOnce(Return(&map));

  // One Unicode codepoint -> one call to mapUnicode with bufSize == 8.
  EXPECT_CALL(map, mapUnicode(0x0041u /* 'A' */, _, 8))
      .WillOnce([](Unicode, char *buf, int bufSize) -> int {
        // Write "A" as UTF-8.
        EXPECT_EQ(bufSize, 8);
        buf[0] = 'A';
        return 1;
      });

  g_TextStringToUCS4Hook = [](const std::string &) { return std::vector<Unicode>{0x0041u}; };

  const std::string out = TextStringToUTF8("ignored-by-hook");
  EXPECT_EQ(out, "A");
}

TEST_F(TextStringToUTF8Test_2687, MultipleCodepointsConcatenateInOrder_2687) {
  StrictMock<MockGlobalParams> gp;
  StrictMock<MockUnicodeMap> map;

  globalParams = &gp;

  EXPECT_CALL(gp, getUtf8Map()).WillOnce(Return(&map));

  g_TextStringToUCS4Hook = [](const std::string &) {
    return std::vector<Unicode>{0x0041u /*A*/, 0x2262u /*≢*/, 0x0042u /*B*/};
  };

  InSequence seq;

  EXPECT_CALL(map, mapUnicode(0x0041u, _, 8))
      .WillOnce([](Unicode, char *buf, int) -> int {
        buf[0] = 'A';
        return 1;
      });

  // Return a multi-byte UTF-8 sequence for ≢ (U+2262) => E2 89 A2
  EXPECT_CALL(map, mapUnicode(0x2262u, _, 8))
      .WillOnce([](Unicode, char *buf, int bufSize) -> int {
        EXPECT_EQ(bufSize, 8);
        const unsigned char bytes[3] = {0xE2, 0x89, 0xA2};
        std::memcpy(buf, bytes, 3);
        return 3;
      });

  EXPECT_CALL(map, mapUnicode(0x0042u, _, 8))
      .WillOnce([](Unicode, char *buf, int) -> int {
        buf[0] = 'B';
        return 1;
      });

  const std::string out = TextStringToUTF8("ignored");
  ASSERT_EQ(out.size(), 1u + 3u + 1u);
  EXPECT_EQ(out, std::string("A") + std::string("\xE2\x89\xA2", 3) + std::string("B"));
}

TEST_F(TextStringToUTF8Test_2687, MapUnicodeReturningZeroAppendsNothingButStillCallsPerCodepoint_2687) {
  StrictMock<MockGlobalParams> gp;
  StrictMock<MockUnicodeMap> map;

  globalParams = &gp;

  EXPECT_CALL(gp, getUtf8Map()).WillOnce(Return(&map));

  g_TextStringToUCS4Hook = [](const std::string &) {
    return std::vector<Unicode>{0x0041u /*A*/, 0x1234u /*unmapped*/, 0x0042u /*B*/};
  };

  InSequence seq;

  EXPECT_CALL(map, mapUnicode(0x0041u, _, 8))
      .WillOnce([](Unicode, char *buf, int) -> int {
        buf[0] = 'A';
        return 1;
      });

  // Simulate "no output" for this codepoint.
  EXPECT_CALL(map, mapUnicode(0x1234u, _, 8))
      .WillOnce([](Unicode, char *, int) -> int { return 0; });

  EXPECT_CALL(map, mapUnicode(0x0042u, _, 8))
      .WillOnce([](Unicode, char *buf, int) -> int {
        buf[0] = 'B';
        return 1;
      });

  const std::string out = TextStringToUTF8("ignored");
  EXPECT_EQ(out, "AB");
}

TEST_F(TextStringToUTF8Test_2687, Utf8MapFetchedOnceEvenForMultipleCodepoints_2687) {
  StrictMock<MockGlobalParams> gp;
  StrictMock<MockUnicodeMap> map;

  globalParams = &gp;

  // Should only be fetched once per function call.
  EXPECT_CALL(gp, getUtf8Map()).Times(1).WillOnce(Return(&map));

  g_TextStringToUCS4Hook = [](const std::string &) {
    return std::vector<Unicode>{0x0041u, 0x0042u, 0x0043u};
  };

  EXPECT_CALL(map, mapUnicode(_, _, 8))
      .Times(3)
      .WillRepeatedly([](Unicode u, char *buf, int) -> int {
        // Map 0x41/0x42/0x43 to ASCII A/B/C for a deterministic output.
        buf[0] = static_cast<char>(u & 0xFF);
        return 1;
      });

  const std::string out = TextStringToUTF8("ignored");
  EXPECT_EQ(out, "ABC");
}