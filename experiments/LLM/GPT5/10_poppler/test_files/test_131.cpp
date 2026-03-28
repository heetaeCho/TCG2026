// TEST_ID: 131
//
// Unit tests for BaseStream::getLength() (black-box via public interface).
//
// Constraints honored:
// - No re-implementation/inference of internal logic beyond observable behavior.
// - Tests rely only on the public constructor + getLength().
// - No private/internal state access.

#include <gtest/gtest.h>

#include "poppler/Stream.h"

namespace {

// Helper: create a "null" Object across Poppler versions (API varies).
template <typename T>
auto has_initNull(int) -> decltype(std::declval<T&>().initNull(), std::true_type{});
template <typename T>
auto has_initNull(...) -> std::false_type;

static Object MakeNullObject()
{
  Object obj;
  if constexpr (decltype(has_initNull<Object>(0))::value) {
    obj.initNull();
  }
  // If initNull() doesn't exist, we assume default construction yields a valid
  // "empty/null-ish" object for BaseStream's ctor in this build.
  return obj;
}

class BaseStreamGetLengthTest_131 : public ::testing::Test {
protected:
  static std::unique_ptr<BaseStream> MakeBaseStreamWithLength(Goffset len)
  {
    Object dict = MakeNullObject();
    return std::make_unique<BaseStream>(std::move(dict), len);
  }
};

} // namespace

TEST_F(BaseStreamGetLengthTest_131, ReturnsZeroWhenConstructedWithZero_131)
{
  auto bs = MakeBaseStreamWithLength(static_cast<Goffset>(0));
  EXPECT_EQ(bs->getLength(), static_cast<Goffset>(0));
}

TEST_F(BaseStreamGetLengthTest_131, ReturnsPositiveLengthWhenConstructedWithPositive_131)
{
  auto bs = MakeBaseStreamWithLength(static_cast<Goffset>(12345));
  EXPECT_EQ(bs->getLength(), static_cast<Goffset>(12345));
}

TEST_F(BaseStreamGetLengthTest_131, ReturnsLargeLengthValue_131)
{
  // Boundary-ish: a large value that should still be representable in Goffset.
  // Avoid assuming exact bit-width; use a value that's large but conservative.
  const Goffset kLarge = static_cast<Goffset>(1) << 30; // ~1 GiB offset
  auto bs = MakeBaseStreamWithLength(kLarge);
  EXPECT_EQ(bs->getLength(), kLarge);
}

TEST_F(BaseStreamGetLengthTest_131, ReturnsNegativeLengthIfConstructedWithNegative_131)
{
  // Boundary/edge: if Goffset is signed, negative lengths may be representable.
  // We only assert the observable behavior: getLength reflects construction arg.
  const Goffset kNeg = static_cast<Goffset>(-1);
  auto bs = MakeBaseStreamWithLength(kNeg);
  EXPECT_EQ(bs->getLength(), kNeg);
}