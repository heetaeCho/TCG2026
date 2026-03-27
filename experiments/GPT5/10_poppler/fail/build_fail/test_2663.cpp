// pdfinfo_printUCS4String_test_2663.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

// The production code uses `Unicode` (Poppler typically typedefs this).
// For the purpose of these black-box tests, we only need a concrete scalar type
// that can be stored in std::vector and passed through to mapUnicode.
using Unicode = uint32_t;

// A minimal external collaborator stub that matches the only observable
// dependency used by printUCS4String(): UnicodeMap::mapUnicode().
class UnicodeMap {
public:
  struct Call {
    Unicode u;
    int bufSize;
  };

  // Configure deterministic mapping behavior for tests.
  // Each entry is (Unicode codepoint -> bytes to write, return count = bytes.size()).
  void SetMapping(std::vector<std::pair<Unicode, std::string>> mapping) {
    mapping_ = std::move(mapping);
  }

  const std::vector<Call>& calls() const { return calls_; }

  // Signature matches the dependency used by printUCS4String.
  int mapUnicode(Unicode u, char* buf, int bufSize) const {
    calls_.push_back(Call{u, bufSize});

    for (const auto& kv : mapping_) {
      if (kv.first == u) {
        const std::string& out = kv.second;
        const int n = static_cast<int>(out.size());
        const int toCopy = (n <= bufSize) ? n : bufSize;
        if (toCopy > 0) {
          std::memcpy(buf, out.data(), static_cast<size_t>(toCopy));
        }
        // Return what would be written by a real mapper: a count of produced bytes.
        // Clamp to bufSize to keep behavior well-defined for the caller.
        return toCopy;
      }
    }
    // Default: map to nothing.
    return 0;
  }

private:
  std::vector<std::pair<Unicode, std::string>> mapping_;
  mutable std::vector<Call> calls_;
};

// ---- Code under test (provided snippet) ----
// We compile exactly the function body as provided to enable exercising it.
// (It is `static` in the production TU, so tests must compile it to call it.)
static void printUCS4String(const std::vector<Unicode> &u, const UnicodeMap *uMap) {
  char buf[8];
  for (auto i : u) {
    int n = uMap->mapUnicode(i, buf, sizeof(buf));
    fwrite(buf, 1, n, stdout);
  }
}

// -------------------- Tests --------------------

TEST(printUCS4StringTest_2663, WritesMappedBytesInOrder_2663) {
  UnicodeMap map;
  map.SetMapping({
      {1u, "A"},
      {2u, "B"},
      {3u, "C"},
  });

  const std::vector<Unicode> input = {1u, 2u, 3u};

  testing::internal::CaptureStdout();
  printUCS4String(input, &map);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "ABC");

  ASSERT_EQ(map.calls().size(), 3u);
  EXPECT_EQ(map.calls()[0].u, 1u);
  EXPECT_EQ(map.calls()[1].u, 2u);
  EXPECT_EQ(map.calls()[2].u, 3u);
  EXPECT_EQ(map.calls()[0].bufSize, 8);
  EXPECT_EQ(map.calls()[1].bufSize, 8);
  EXPECT_EQ(map.calls()[2].bufSize, 8);
}

TEST(printUCS4StringTest_2663, EmptyInputProducesNoOutputAndNoCalls_2663) {
  UnicodeMap map;
  map.SetMapping({
      {1u, "X"},
  });

  const std::vector<Unicode> input; // empty

  testing::internal::CaptureStdout();
  printUCS4String(input, &map);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(out.empty());
  EXPECT_TRUE(map.calls().empty());
}

TEST(printUCS4StringTest_2663, UnmappedCodepointProducesNoBytesButStillInvokesMapper_2663) {
  UnicodeMap map;
  map.SetMapping({
      {10u, "Z"},
  });

  const std::vector<Unicode> input = {999u}; // unmapped -> mapUnicode returns 0

  testing::internal::CaptureStdout();
  printUCS4String(input, &map);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(out.empty());

  ASSERT_EQ(map.calls().size(), 1u);
  EXPECT_EQ(map.calls()[0].u, 999u);
  EXPECT_EQ(map.calls()[0].bufSize, 8);
}

TEST(printUCS4StringTest_2663, RespectsMapperReturnCountIncludingMaxBufferSize_2663) {
  UnicodeMap map;
  // 8 bytes exactly: should be written fully (buf size is 8).
  map.SetMapping({
      {42u, "12345678"},
  });

  const std::vector<Unicode> input = {42u};

  testing::internal::CaptureStdout();
  printUCS4String(input, &map);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "12345678");
  ASSERT_EQ(map.calls().size(), 1u);
  EXPECT_EQ(map.calls()[0].u, 42u);
  EXPECT_EQ(map.calls()[0].bufSize, 8);
}

TEST(printUCS4StringTest_2663, MultipleElementsWithMixedEmptyAndNonEmptyMappings_2663) {
  UnicodeMap map;
  map.SetMapping({
      {1u, "A"},
      {2u, ""},     // explicitly maps to zero bytes
      {3u, "BC"},
  });

  const std::vector<Unicode> input = {1u, 2u, 3u};

  testing::internal::CaptureStdout();
  printUCS4String(input, &map);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "ABC");

  ASSERT_EQ(map.calls().size(), 3u);
  EXPECT_EQ(map.calls()[0].u, 1u);
  EXPECT_EQ(map.calls()[1].u, 2u);
  EXPECT_EQ(map.calls()[2].u, 3u);
}