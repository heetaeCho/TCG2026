// File: test_exifdatum_write_728.cpp
// Unit tests for Exiv2::Exifdatum::write (black-box via public interface)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

// A controllable Exiv2::Value for exercising Exifdatum::write behavior without
// relying on Exiv2 internals. Exifdatum is expected to clone the Value via Value::clone().
class ControlledValue final : public Exiv2::Value {
 public:
  ControlledValue(Exiv2::TypeId typeId, std::size_t count, std::string text,
                  bool throw_on_write, bool throw_on_toString_n)
      : Exiv2::Value(typeId),
        count_(count),
        text_(std::move(text)),
        throw_on_write_(throw_on_write),
        throw_on_toString_n_(throw_on_toString_n) {}

  ControlledValue(const ControlledValue&) = default;
  ControlledValue& operator=(const ControlledValue&) = default;
  ~ControlledValue() override = default;

  const size_t count() override { return count_; }

  const std::ostream& write(std::ostream& os) override {
    if (throw_on_write_) {
      throw std::out_of_range("ControlledValue::write out_of_range");
    }
    os << text_;
    return os;
  }

  const std::string toString(size_t /*n*/) override {
    if (throw_on_toString_n_) {
      throw std::out_of_range("ControlledValue::toString(n) out_of_range");
    }
    return text_;
  }

 private:
  // Value::clone() calls the private virtual clone_(). We override it to make cloning work.
  const Exiv2::Value* clone_() override { return new ControlledValue(*this); }

  std::size_t count_;
  std::string text_;
  bool throw_on_write_;
  bool throw_on_toString_n_;
};

class ExifdatumWriteTest_728 : public ::testing::Test {
 protected:
  static std::string WriteToString(const Exiv2::Exifdatum& d, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    d.write(oss, md);
    return oss.str();
  }
};

}  // namespace

TEST_F(ExifdatumWriteTest_728, CountZeroProducesNoOutput_728) {
  // If value().count() == 0, write() should return without writing anything.
  Exiv2::ExifKey key("Exif.Image.Make");
  ControlledValue v(/*typeId=*/Exiv2::asciiString,
                    /*count=*/0,
                    /*text=*/"SHOULD_NOT_APPEAR",
                    /*throw_on_write=*/true,
                    /*throw_on_toString_n=*/true);

  Exiv2::Exifdatum d(key, &v);

  EXPECT_NO_THROW({
    const std::string out = WriteToString(d, /*pMetadata=*/nullptr);
    EXPECT_TRUE(out.empty());
  });
}

TEST_F(ExifdatumWriteTest_728, OutOfRangeFromFormatterWritesBadValue_728) {
  // If the chosen formatter throws std::out_of_range, write() should append "Bad value".
  // We trigger this by providing a Value that throws from write()/toString(n), which are
  // typically used by Exiv2's formatting path.
  Exiv2::ExifKey key("Exif.Image.Make");
  ControlledValue v(/*typeId=*/Exiv2::asciiString,
                    /*count=*/1,
                    /*text=*/"IGNORED",
                    /*throw_on_write=*/true,
                    /*throw_on_toString_n=*/true);

  Exiv2::Exifdatum d(key, &v);

  EXPECT_NO_THROW({
    const std::string out = WriteToString(d, /*pMetadata=*/nullptr);
    // Be tolerant to any additional formatting behavior; the observable requirement is that
    // "Bad value" appears when std::out_of_range is caught.
    EXPECT_NE(out.find("Bad value"), std::string::npos);
  });
}

TEST_F(ExifdatumWriteTest_728, CommentTypeWritesValueToStringDirectly_728) {
  // For tags whose TagInfo typeId_ is comment, write() should output value().toString()
  // directly (per the provided implementation snippet).
  //
  // We use Exif.Photo.UserComment as a commonly-comment-typed tag in Exiv2.
  Exiv2::ExifKey key("Exif.Photo.UserComment");
  ControlledValue v(/*typeId=*/Exiv2::comment,
                    /*count=*/1,
                    /*text=*/"hello-comment",
                    /*throw_on_write=*/true,   // should not be used if comment-path is taken
                    /*throw_on_toString_n=*/false);

  Exiv2::Exifdatum d(key, &v);

  EXPECT_NO_THROW({
    const std::string out = WriteToString(d, /*pMetadata=*/nullptr);
    EXPECT_EQ(out, "hello-comment");
  });
}

TEST_F(ExifdatumWriteTest_728, NullMetadataPointerIsAccepted_728) {
  // pMetadata is an input pointer; writing should be safe with nullptr.
  Exiv2::ExifKey key("Exif.Image.Make");
  ControlledValue v(/*typeId=*/Exiv2::asciiString,
                    /*count=*/1,
                    /*text=*/"some-text",
                    /*throw_on_write=*/false,
                    /*throw_on_toString_n=*/false);

  Exiv2::Exifdatum d(key, &v);

  EXPECT_NO_THROW({
    const std::string out = WriteToString(d, /*pMetadata=*/nullptr);
    // We only assert that something is written in normal operation.
    EXPECT_FALSE(out.empty());
  });
}