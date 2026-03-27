// TEST_ID 1499
// Unit tests for Exiv2::Internal::SonyMnHeader
//
// Constraints honored:
// - Treat implementation as black box (no internal assumptions beyond public interface).
// - Test only observable behavior via the public API.
// - No access to private state.

#include <gtest/gtest.h>

#include "makernote_int.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::SonyMnHeader;

class SonyMnHeaderTest_1499 : public ::testing::Test {};

TEST_F(SonyMnHeaderTest_1499, SizeOfSignature_IsDeterministic_1499) {
  const size_t a = SonyMnHeader::sizeOfSignature();
  const size_t b = SonyMnHeader::sizeOfSignature();
  EXPECT_EQ(a, b);
}

TEST_F(SonyMnHeaderTest_1499, SizeConst_EqualsSizeOfSignature_1499) {
  const SonyMnHeader hdr;
  const size_t s = hdr.size();
  const size_t sig = SonyMnHeader::sizeOfSignature();
  EXPECT_EQ(s, sig);
}

TEST_F(SonyMnHeaderTest_1499, SizeViaConstRef_EqualsSizeOfSignature_1499) {
  SonyMnHeader hdr;
  const SonyMnHeader& chdr = hdr;
  EXPECT_EQ(chdr.size(), SonyMnHeader::sizeOfSignature());
}

TEST_F(SonyMnHeaderTest_1499, Read_WithZeroSize_DoesNotThrow_1499) {
  SonyMnHeader hdr;

  // Use a non-null pointer even when size==0.
  const unsigned char dummy[1] = {0};

  bool ok = false;
  EXPECT_NO_THROW({
    ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(dummy), 0, Exiv2::littleEndian);
  });

  // Observable behavior: returns a bool. No stronger assumption about true/false.
  (void)ok;
}

TEST_F(SonyMnHeaderTest_1499, Read_WithSmallBuffers_DoesNotThrow_1499) {
  SonyMnHeader hdr;

  const size_t sig = SonyMnHeader::sizeOfSignature();
  // Cover boundary-like sizes around signature size (if sig is 0, still fine).
  const size_t sizes[] = {
      size_t{0},
      size_t{1},
      sig > 0 ? sig - 1 : size_t{0},
      sig,
      sig + 1,
  };

  // Provide a buffer large enough for the largest "size" we pass.
  const size_t maxSize = sig + 1;
  std::vector<unsigned char> buf(maxSize > 0 ? maxSize : 1, 0);

  for (size_t n : sizes) {
    bool ok = false;
    EXPECT_NO_THROW({
      ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(buf.data()), n, Exiv2::littleEndian);
    }) << "read() threw for size=" << n;
    (void)ok;
  }
}

TEST_F(SonyMnHeaderTest_1499, IfdOffset_IsDeterministicAcrossCalls_1499) {
  const SonyMnHeader hdr;

  size_t a = 0, b = 0;
  EXPECT_NO_THROW({ a = hdr.ifdOffset(); });
  EXPECT_NO_THROW({ b = hdr.ifdOffset(); });

  EXPECT_EQ(a, b);
}

}  // namespace