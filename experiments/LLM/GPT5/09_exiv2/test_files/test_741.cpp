// File: test_exifdatum_setdataarea_741.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace {

// A small test double for Exiv2::Value that supports cloning and records calls to setDataArea.
// This is an external collaborator of Exiv2::Exifdatum (owned via unique_ptr inside Exifdatum).
class RecordingValue final : public Exiv2::Value {
 public:
  explicit RecordingValue(Exiv2::TypeId typeId, int return_code)
      : Exiv2::Value(typeId), return_code_(return_code) {}

  // Records arguments and returns a configurable code.
  int setDataArea(const Exiv2::byte* buf, size_t len) override {
    ++setDataArea_calls_;
    last_buf_ = buf;
    last_len_ = len;
    return return_code_;
  }

  // Used to verify forwarding.
  int calls() const { return setDataArea_calls_; }
  const Exiv2::byte* last_buf() const { return last_buf_; }
  size_t last_len() const { return last_len_; }

  void set_return_code(int rc) { return_code_ = rc; }

 private:
  // Exiv2::Value cloning uses a private virtual clone_() in the base. Overriding is allowed.
  const Exiv2::Value* clone_() override { return new RecordingValue(*this); }

  int return_code_{0};
  int setDataArea_calls_{0};
  const Exiv2::byte* last_buf_{nullptr};
  size_t last_len_{0};
};

class ExifdatumTest_741 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Exiv2::ExifKey commonly supports construction from a key string in the public API.
    return Exiv2::ExifKey("Exif.Image.Make");
  }
};

}  // namespace

TEST_F(ExifdatumTest_741, ReturnsMinusOneWhenNoValue_741) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum d(key, nullptr);

  const Exiv2::byte buf[4] = {0x01, 0x02, 0x03, 0x04};
  EXPECT_EQ(-1, d.setDataArea(buf, sizeof(buf)));
  EXPECT_EQ(-1, d.setDataArea(nullptr, 0u));  // boundary: null buffer with zero length
}

TEST_F(ExifdatumTest_741, ForwardsArgumentsAndReturnsUnderlyingCode_741) {
  const Exiv2::ExifKey key = MakeKey();

  RecordingValue v(Exiv2::unsignedByte, /*return_code=*/7);
  Exiv2::Exifdatum d(key, &v);

  const Exiv2::byte buf[6] = {0, 1, 2, 3, 4, 5};
  const int rc = d.setDataArea(buf, sizeof(buf));

  EXPECT_EQ(7, rc);

  // Verify the call was forwarded (observable interaction via the external collaborator).
  EXPECT_EQ(1, v.calls());
  EXPECT_EQ(buf, v.last_buf());
  EXPECT_EQ(sizeof(buf), v.last_len());
}

TEST_F(ExifdatumTest_741, ForwardsZeroLengthBoundary_741) {
  const Exiv2::ExifKey key = MakeKey();

  RecordingValue v(Exiv2::unsignedByte, /*return_code=*/0);
  Exiv2::Exifdatum d(key, &v);

  const Exiv2::byte buf[1] = {0xAB};
  const int rc = d.setDataArea(buf, 0u);  // boundary: length=0

  EXPECT_EQ(0, rc);
  EXPECT_EQ(1, v.calls());
  EXPECT_EQ(buf, v.last_buf());
  EXPECT_EQ(0u, v.last_len());
}

TEST_F(ExifdatumTest_741, ForwardsNullBufferWithNonZeroLengthAndPropagatesError_741) {
  const Exiv2::ExifKey key = MakeKey();

  RecordingValue v(Exiv2::unsignedByte, /*return_code=*/-5);
  Exiv2::Exifdatum d(key, &v);

  const int rc = d.setDataArea(nullptr, 3u);  // boundary/edge: null buf, non-zero len

  EXPECT_EQ(-5, rc);
  EXPECT_EQ(1, v.calls());
  EXPECT_EQ(nullptr, v.last_buf());
  EXPECT_EQ(3u, v.last_len());
}

TEST_F(ExifdatumTest_741, PropagatesDifferentReturnCodesAcrossCalls_741) {
  const Exiv2::ExifKey key = MakeKey();

  RecordingValue v(Exiv2::unsignedByte, /*return_code=*/1);
  Exiv2::Exifdatum d(key, &v);

  const Exiv2::byte bufA[2] = {0x10, 0x11};
  EXPECT_EQ(1, d.setDataArea(bufA, sizeof(bufA)));
  EXPECT_EQ(1, v.calls());

  v.set_return_code(-2);
  const Exiv2::byte bufB[3] = {0x20, 0x21, 0x22};
  EXPECT_EQ(-2, d.setDataArea(bufB, sizeof(bufB)));
  EXPECT_EQ(2, v.calls());

  EXPECT_EQ(bufB, v.last_buf());
  EXPECT_EQ(sizeof(bufB), v.last_len());
}