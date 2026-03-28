// File: test_fnvhash_2790.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// NOTE:
// FNVHash is defined/implemented in poppler/poppler/GfxFont.cc.
// In many Poppler builds, this helper class is not exposed via a public header.
// So we declare the interface here (no implementation) and rely on linking
// against the Poppler objects that provide the real definitions.
//
// If your build already exposes FNVHash via some header, remove this declaration
// and include the proper header instead.
class FNVHash {
private:
  unsigned int h;

public:
  FNVHash();
  void hash(char c);
  void hash(const char *p, int n);
  int get31() const;
};

class FNVHashTest_2790 : public ::testing::Test {
protected:
  static int HashByBuffer(const std::vector<char> &bytes)
  {
    FNVHash h;
    // Safe even for empty vector (n=0, p may be nullptr).
    const char *p = bytes.empty() ? nullptr : bytes.data();
    h.hash(p, static_cast<int>(bytes.size()));
    return h.get31();
  }

  static int HashByChars(const std::vector<char> &bytes)
  {
    FNVHash h;
    for (char c : bytes) {
      h.hash(c);
    }
    return h.get31();
  }

  static int HashIncrementalBuffers(const std::vector<std::vector<char>> &chunks)
  {
    FNVHash h;
    for (const auto &chunk : chunks) {
      const char *p = chunk.empty() ? nullptr : chunk.data();
      h.hash(p, static_cast<int>(chunk.size()));
    }
    return h.get31();
  }
};

TEST_F(FNVHashTest_2790, DefaultConstructedObjectsHaveSameGet31_2790)
{
  FNVHash a;
  FNVHash b;

  EXPECT_EQ(a.get31(), b.get31());
}

TEST_F(FNVHashTest_2790, Get31IsStableAcrossRepeatedCalls_2790)
{
  FNVHash h;
  h.hash('x');

  const int v1 = h.get31();
  const int v2 = h.get31();
  EXPECT_EQ(v1, v2);
}

TEST_F(FNVHashTest_2790, HashCharAndHashBufferProduceSameResultForSameBytes_2790)
{
  // Include a mix of bytes, including 0 and values that may be negative if char is signed.
  const std::vector<char> bytes = {
      'A',
      '\0',
      'z',
      static_cast<char>(static_cast<unsigned char>(0x7F)),
      static_cast<char>(static_cast<unsigned char>(0x80)),
      static_cast<char>(static_cast<unsigned char>(0xFF)),
  };

  const int byBuf = HashByBuffer(bytes);
  const int byChar = HashByChars(bytes);

  EXPECT_EQ(byBuf, byChar);
}

TEST_F(FNVHashTest_2790, HashBufferIncrementalMatchesSingleConcatenatedBuffer_2790)
{
  const std::vector<char> part1 = {'a', 'b', 'c'};
  const std::vector<char> part2 = {'d', 'e', 'f', '\0', 'g'};
  std::vector<char> all;
  all.insert(all.end(), part1.begin(), part1.end());
  all.insert(all.end(), part2.begin(), part2.end());

  const int inc = HashIncrementalBuffers({part1, part2});
  const int oneShot = HashByBuffer(all);

  EXPECT_EQ(inc, oneShot);
}

TEST_F(FNVHashTest_2790, HashBufferWithZeroLengthIsHandledAndDeterministic_2790)
{
  // Boundary: n = 0 with nullptr pointer.
  FNVHash h1;
  h1.hash(nullptr, 0);
  const int v1 = h1.get31();

  // Boundary: n = 0 with non-null pointer.
  const char dummy = 'Q';
  FNVHash h2;
  h2.hash(&dummy, 0);
  const int v2 = h2.get31();

  // We don't assume whether hashing zero bytes changes state or not,
  // only that behavior is deterministic for the same call pattern.
  FNVHash h3;
  h3.hash(nullptr, 0);
  const int v3 = h3.get31();

  EXPECT_EQ(v1, v3);
  // No assertion between v1 and v2 (implementation may treat pointer value differently or ignore it).
}

TEST_F(FNVHashTest_2790, Get31IsNonNegativeAfterHashingSomeData_2790)
{
  FNVHash h;
  const char data[] = {'P', 'o', 'p', 'p', 'l', 'e', 'r', '\0'};
  h.hash(data, static_cast<int>(sizeof(data)));

  EXPECT_GE(h.get31(), 0);
}