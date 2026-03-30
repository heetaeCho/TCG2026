// Decrypt_md5Start_ut_1622.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// NOTE:
// md5Start is declared 'static' inside Decrypt.cc (internal linkage).
// To test it through its real implementation (black-box), we include the .cc
// into this test translation unit so the symbol is visible here.
//
// If your build links Decrypt.cc separately into the test binary, including it
// here may cause duplicate symbols. In that case, compile this test without
// also compiling/linking Decrypt.cc as a separate object.
#include "Decrypt.cc"

namespace {

// Detection idiom (C++17) to avoid assuming the exact MD5State layout across versions.
template <typename T, typename = void>
struct HasBufLen : std::false_type {};
template <typename T>
struct HasBufLen<T, std::void_t<decltype(std::declval<T &>().bufLen)>> : std::true_type {};

} // namespace

class DecryptMd5StartTest_1622 : public ::testing::Test {};

TEST_F(DecryptMd5StartTest_1622, ResetsCoreStateWordsToExpectedConstants_1622)
{
  MD5State st{};

  // Pre-fill with non-default values to ensure the function actually resets them.
  st.a = 0xAAAAAAAAul;
  st.b = 0xBBBBBBBBul;
  st.c = 0xCCCCCCCCul;
  st.d = 0xDDDDDDDDul;
  st.msgLen = 12345;

  if constexpr (HasBufLen<MD5State>::value) {
    st.bufLen = 7;
  }

  md5Start(&st);

  EXPECT_EQ(st.a, 0x67452301ul);
  EXPECT_EQ(st.b, 0xefcdab89ul);
  EXPECT_EQ(st.c, 0x98badcfeul);
  EXPECT_EQ(st.d, 0x10325476ul);
  EXPECT_EQ(st.msgLen, 0);

  if constexpr (HasBufLen<MD5State>::value) {
    EXPECT_EQ(st.bufLen, 0);
  }
}

TEST_F(DecryptMd5StartTest_1622, IsIdempotentWhenCalledMultipleTimes_1622)
{
  MD5State st{};
  st.a = 1;
  st.b = 2;
  st.c = 3;
  st.d = 4;
  st.msgLen = -1;

  if constexpr (HasBufLen<MD5State>::value) {
    st.bufLen = 999;
  }

  md5Start(&st);
  // Mutate again to ensure a second call re-resets.
  st.a ^= 0xFFFFFFFFul;
  st.b ^= 0xFFFFFFFFul;
  st.c ^= 0xFFFFFFFFul;
  st.d ^= 0xFFFFFFFFul;
  st.msgLen = 42;
  if constexpr (HasBufLen<MD5State>::value) {
    st.bufLen = 123;
  }

  md5Start(&st);

  EXPECT_EQ(st.a, 0x67452301ul);
  EXPECT_EQ(st.b, 0xefcdab89ul);
  EXPECT_EQ(st.c, 0x98badcfeul);
  EXPECT_EQ(st.d, 0x10325476ul);
  EXPECT_EQ(st.msgLen, 0);

  if constexpr (HasBufLen<MD5State>::value) {
    EXPECT_EQ(st.bufLen, 0);
  }
}

TEST_F(DecryptMd5StartTest_1622, HandlesExtremePreexistingValues_1622)
{
  MD5State st{};
  st.a = ~0ul;
  st.b = ~0ul;
  st.c = ~0ul;
  st.d = ~0ul;
  st.msgLen = std::numeric_limits<int>::max();

  if constexpr (HasBufLen<MD5State>::value) {
    st.bufLen = std::numeric_limits<int>::max();
  }

  md5Start(&st);

  EXPECT_EQ(st.a, 0x67452301ul);
  EXPECT_EQ(st.b, 0xefcdab89ul);
  EXPECT_EQ(st.c, 0x98badcfeul);
  EXPECT_EQ(st.d, 0x10325476ul);
  EXPECT_EQ(st.msgLen, 0);

  if constexpr (HasBufLen<MD5State>::value) {
    EXPECT_EQ(st.bufLen, 0);
  }
}

TEST_F(DecryptMd5StartTest_1622, NullStatePointerDeathIfSupported_1622)
{
  // Exceptional/error case (observable): passing nullptr is invalid; the function
  // will typically crash due to dereference. We only assert this where supported.
  ASSERT_DEATH_IF_SUPPORTED(md5Start(nullptr), "");
}