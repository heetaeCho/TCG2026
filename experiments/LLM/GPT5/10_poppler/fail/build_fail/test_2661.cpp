// File: test_pdfinfo_printStdTextString_2661.cc
#include <gtest/gtest.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Include Poppler's UnicodeMap so we can construct a real instance using a custom UnicodeMapFunc.
#include "poppler/UnicodeMap.h"

// The function under test is `static` in pdfinfo.cc. To test it as a black box via its interface,
// we include the implementation unit here so the symbol is visible in this translation unit.
//
// NOTE: This relies on the project layout shown in the prompt.
#include "utils/pdfinfo.cc"

namespace {

// --- Test double via UnicodeMapFunc (no mocking of internal behavior) ---
struct MapFuncState {
  std::atomic<int> calls{0};
  std::vector<Unicode> seen;
  std::string mode;  // "echo1", "zeroOnB", "eightBytes"
};

static MapFuncState g_state;

static int TestUnicodeMapFunc(Unicode u, char *buf, int bufSize) {
  g_state.calls.fetch_add(1, std::memory_order_relaxed);
  g_state.seen.push_back(u);

  if (g_state.mode == "zeroOnB") {
    // Return 0 bytes for 'B' to simulate "no output produced".
    if (u == static_cast<Unicode>('B')) {
      return 0;
    }
    if (bufSize <= 0) {
      return 0;
    }
    buf[0] = static_cast<char>(u & 0xFF);
    return 1;
  }

  if (g_state.mode == "eightBytes") {
    // Emit exactly 8 bytes per input character (fits the buf[8] used by the function under test).
    static const char kEight[8] = {'1','2','3','4','5','6','7','8'};
    if (bufSize < 8) {
      // Be defensive: emit as much as we can without overflow.
      const int n = bufSize < 0 ? 0 : bufSize;
      for (int i = 0; i < n; ++i) buf[i] = kEight[i];
      return n;
    }
    std::memcpy(buf, kEight, 8);
    return 8;
  }

  // Default: emit one byte echo of low 8 bits (good for ASCII expectations).
  if (bufSize <= 0) {
    return 0;
  }
  buf[0] = static_cast<char>(u & 0xFF);
  return 1;
}

class PrintStdTextStringTest_2661 : public ::testing::Test {
protected:
  void SetUp() override {
    g_state.calls.store(0, std::memory_order_relaxed);
    g_state.seen.clear();
    g_state.mode = "echo1";
  }

  // Helper: construct a UnicodeMap that uses our test map function.
  UnicodeMap MakeTestMap() {
    // encodingName can be arbitrary for this constructor path; unicodeOut flag also not relied on.
    return UnicodeMap("unit-test-map", /*unicodeOutA=*/false, &TestUnicodeMapFunc);
  }

  std::string CaptureStdoutOfPrint(const std::string &s, const UnicodeMap &map) {
    testing::internal::CaptureStdout();
    printStdTextString(s, &map);
    return testing::internal::GetCapturedStdout();
  }
};

TEST_F(PrintStdTextStringTest_2661, PrintsAsciiThroughUnicodeMap_2661) {
  UnicodeMap map = MakeTestMap();

  const std::string out = CaptureStdoutOfPrint("ABC", map);

  EXPECT_EQ(out, "ABC");
  EXPECT_EQ(g_state.calls.load(std::memory_order_relaxed), 3);

  ASSERT_EQ(g_state.seen.size(), 3u);
  EXPECT_EQ(g_state.seen[0], static_cast<Unicode>('A'));
  EXPECT_EQ(g_state.seen[1], static_cast<Unicode>('B'));
  EXPECT_EQ(g_state.seen[2], static_cast<Unicode>('C'));
}

TEST_F(PrintStdTextStringTest_2661, EmptyStringProducesNoOutputAndNoMapCalls_2661) {
  UnicodeMap map = MakeTestMap();

  const std::string out = CaptureStdoutOfPrint("", map);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(g_state.calls.load(std::memory_order_relaxed), 0);
  EXPECT_TRUE(g_state.seen.empty());
}

TEST_F(PrintStdTextStringTest_2661, MapUnicodeReturningZeroBytesSkipsOutputForThatCodepoint_2661) {
  g_state.mode = "zeroOnB";
  UnicodeMap map = MakeTestMap();

  const std::string out = CaptureStdoutOfPrint("ABC", map);

  // 'B' contributes 0 bytes; others echo 1 byte.
  EXPECT_EQ(out, "AC");
  EXPECT_EQ(g_state.calls.load(std::memory_order_relaxed), 3);

  ASSERT_EQ(g_state.seen.size(), 3u);
  EXPECT_EQ(g_state.seen[0], static_cast<Unicode>('A'));
  EXPECT_EQ(g_state.seen[1], static_cast<Unicode>('B'));
  EXPECT_EQ(g_state.seen[2], static_cast<Unicode>('C'));
}

TEST_F(PrintStdTextStringTest_2661, MultiByteOutputPerCodepointIsWrittenInFull_2661) {
  g_state.mode = "eightBytes";
  UnicodeMap map = MakeTestMap();

  const std::string out = CaptureStdoutOfPrint("AB", map);

  // 8 bytes per codepoint, twice.
  EXPECT_EQ(out.size(), 16u);
  EXPECT_EQ(out, std::string("12345678") + "12345678");
  EXPECT_EQ(g_state.calls.load(std::memory_order_relaxed), 2);

  ASSERT_EQ(g_state.seen.size(), 2u);
  EXPECT_EQ(g_state.seen[0], static_cast<Unicode>('A'));
  EXPECT_EQ(g_state.seen[1], static_cast<Unicode>('B'));
}

TEST_F(PrintStdTextStringTest_2661, HandlesUtf16BETextStringWithBom_2661) {
  // Many PDF "TextString" values are UTF-16BE with BOM 0xFE 0xFF.
  // This test checks that printStdTextString can process embedded NUL bytes
  // in the input string and still prints the expected mapped characters.
  UnicodeMap map = MakeTestMap();

  const std::string utf16be_with_bom =
      std::string("\xFE\xFF\x00\x41\x00\x42", 6);  // BOM + 'A' + 'B' in UTF-16BE

  const std::string out = CaptureStdoutOfPrint(utf16be_with_bom, map);

  // If TextStringToUCS4 recognizes the BOM, it should yield U+0041, U+0042.
  // Our map function echoes low 8 bits, so that becomes 'A' and 'B'.
  EXPECT_EQ(out, "AB");

  // External interaction: should map two Unicode codepoints.
  EXPECT_EQ(g_state.calls.load(std::memory_order_relaxed), 2);
  ASSERT_EQ(g_state.seen.size(), 2u);
  EXPECT_EQ(g_state.seen[0], static_cast<Unicode>('A'));
  EXPECT_EQ(g_state.seen[1], static_cast<Unicode>('B'));
}

}  // namespace