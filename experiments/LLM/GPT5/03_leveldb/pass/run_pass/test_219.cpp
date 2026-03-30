// copy_string_test_219.cc
#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>
#include <string>

// Bring the function under test into this translation unit.
// We do not modify the implementation; we only include it to access the interface.
#include "db/c.cc"

// --- Tests ---

// Verifies that the returned buffer contains exactly the same bytes (including embedded '\0')
// and is a distinct allocation from the source string's storage.
TEST(CopyStringTest_219, CopiesExactBytesWithEmbeddedNull_219) {
  const std::string src = std::string("ab\0cd", 5);  // bytes: 'a','b','\0','c','d'
  char* copied = CopyString(src);

  ASSERT_NE(copied, nullptr);               // Must return a buffer (size > 0 case)
  EXPECT_NE(copied, src.data());            // Should be a distinct allocation
  EXPECT_EQ(0, std::memcmp(copied, src.data(), src.size()));  // Exact byte match

  // Reconstruct a string from the returned bytes to validate equality at the interface level
  std::string roundtrip(copied, src.size());
  EXPECT_EQ(src, roundtrip);

  std::free(copied);
}

// Verifies independence: mutating the returned buffer does not change the original string.
TEST(CopyStringTest_219, ReturnedBufferIsIndependent_219) {
  std::string src = "hello";
  char* copied = CopyString(src);
  ASSERT_NE(copied, nullptr);

  // Change the first byte in the copied buffer
  copied[0] = 'H';

  // Original string must remain unchanged (observable via its public interface)
  EXPECT_EQ(std::string("hello"), src);

  // The modified buffer should reflect our change while length/bytes remain consistent
  EXPECT_EQ('H', copied[0]);
  EXPECT_EQ(0, std::memcmp(copied + 1, src.data() + 1, src.size() - 1));

  std::free(copied);
}

// Boundary case: empty input should be safely handled.
// malloc(0) may return nullptr or a unique pointer; both are valid. We only require that it is freeable.
TEST(CopyStringTest_219, HandlesEmptyStringSafely_219) {
  const std::string empty;
  char* copied = CopyString(empty);

  // Both outcomes are allowed by the C standard for malloc(0).
  // We only assert that freeing it is safe (free(nullptr) is also valid).
  // If the pointer is non-null, we cannot legally read/write any bytes (size is 0),
  // so we avoid any access and just free it.
  // The key check here is absence of crashes/UB at the interface level.
  std::free(copied);
  SUCCEED();
}

// Stress/size case: large input should copy correctly (byte-for-byte).
TEST(CopyStringTest_219, CopiesLargeStringCorrectly_219) {
  const size_t N = 1 << 20;  // 1 MiB
  std::string src;
  src.resize(N);
  for (size_t i = 0; i < N; ++i) {
    // Fill with a deterministic pattern; interface-wise we only care about byte equality.
    src[i] = static_cast<char>(i & 0xFF);
  }

  char* copied = CopyString(src);
  ASSERT_NE(copied, nullptr);

  EXPECT_EQ(0, std::memcmp(copied, src.data(), src.size()));

  std::free(copied);
}
