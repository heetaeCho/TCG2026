// TEST_ID is 208
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

#include "Stream.h"

#if __has_include("Object.h")
#include "Object.h"
#endif

namespace {

class ASCIIHexEncoderTest_208 : public ::testing::Test {
protected:
  // Keep backing storage alive for streams that reference external buffers.
  std::string backing_;

  // Helper: build a MemStream over |backing_|.
  // This is intentionally written to tolerate small signature differences across Poppler versions.
  static std::unique_ptr<Stream> MakeMemStreamFrom(const std::string &data, std::string *backing_out) {
    *backing_out = data;
    const auto *buf = reinterpret_cast<const unsigned char *>(backing_out->data());
    const int len = static_cast<int>(backing_out->size());

#if __has_include("Object.h")
    Object dict; // Most Poppler builds default-construct to a "null" object.

    if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, int, Object &&>) {
      return std::make_unique<MemStream>(buf, 0, len, std::move(dict));
    } else if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, int, const Object &>) {
      return std::make_unique<MemStream>(buf, 0, len, dict);
    } else if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, int, Object *>) {
      return std::make_unique<MemStream>(buf, 0, len, &dict);
    } else if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, int>) {
      return std::make_unique<MemStream>(buf, 0, len);
    } else {
      static_assert(std::is_constructible_v<MemStream, const unsigned char *, int, int, Object &&> ||
                        std::is_constructible_v<MemStream, const unsigned char *, int, int, const Object &> ||
                        std::is_constructible_v<MemStream, const unsigned char *, int, int, Object *> ||
                        std::is_constructible_v<MemStream, const unsigned char *, int, int>,
                    "Unsupported MemStream constructor signature in this Poppler build.");
      return nullptr;
    }
#else
    // If Object isn't available in this build, try an Object-less MemStream signature.
    if constexpr (std::is_constructible_v<MemStream, const unsigned char *, int, int>) {
      return std::make_unique<MemStream>(buf, 0, len);
    } else {
      static_assert(std::is_constructible_v<MemStream, const unsigned char *, int, int>,
                    "Object.h not available and MemStream requires Object in this Poppler build.");
      return nullptr;
    }
#endif
  }
};

TEST_F(ASCIIHexEncoderTest_208, GetKindReturnsStrWeird_208) {
  auto in = MakeMemStreamFrom("hello", &backing_);
  ASSERT_NE(in, nullptr);

  ASCIIHexEncoder enc(in.get());
  EXPECT_EQ(enc.getKind(), strWeird);

  // Repeated calls should be stable.
  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(ASCIIHexEncoderTest_208, GetKindViaBaseStreamPointerReturnsStrWeird_208) {
  auto in = MakeMemStreamFrom("00ff", &backing_);
  ASSERT_NE(in, nullptr);

  ASCIIHexEncoder enc(in.get());
  Stream *as_stream = &enc;
  ASSERT_NE(as_stream, nullptr);

  EXPECT_EQ(as_stream->getKind(), strWeird);
}

TEST_F(ASCIIHexEncoderTest_208, GetKindWithEmptyInputReturnsStrWeird_208) {
  auto in = MakeMemStreamFrom("", &backing_);
  ASSERT_NE(in, nullptr);

  ASCIIHexEncoder enc(in.get());
  EXPECT_EQ(enc.getKind(), strWeird);
}

} // namespace