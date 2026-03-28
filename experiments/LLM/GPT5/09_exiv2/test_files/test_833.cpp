// File: test_value_xmpvalue_size_833.cpp
#include <gtest/gtest.h>

#include <string>
#include <ostream>

// Exiv2 headers (as used by the real codebase)
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

namespace {

// A small test double that lets us observe how XmpValue::size() uses write(os).
class TestXmpValue833 : public Exiv2::XmpValue {
 public:
  // In Exiv2, Value-derived types typically require a TypeId at construction.
  // We pick a commonly-available XMP TypeId. If your build uses a different
  // TypeId constant for XMP text, replace Exiv2::xmpText accordingly.
  explicit TestXmpValue833(Exiv2::TypeId typeId = Exiv2::xmpText) : Exiv2::XmpValue(typeId) {}

  void setPayload(std::string s) { payload_ = std::move(s); }
  void setSetFailbit(bool v) { set_failbit_ = v; }

  int writeCalls() const { return write_calls_; }

  // Override write so we can control the bytes that XmpValue::size() will measure.
  const std::ostream& write(std::ostream& os) const override {
    ++write_calls_;
    if (set_failbit_) {
      os.setstate(std::ios::failbit);
      return os;
    }
    os << payload_;
    return os;
  }

 private:
  std::string payload_;
  bool set_failbit_{false};
  mutable int write_calls_{0};
};

}  // namespace

class XmpValueTest_833 : public ::testing::Test {};

TEST_F(XmpValueTest_833, SizeMatchesWriteOutputLength_833) {
  TestXmpValue833 v;
  v.setPayload("abc");

  const size_t sz = v.size();

  EXPECT_EQ(sz, 3u);
  EXPECT_EQ(v.writeCalls(), 1);
}

TEST_F(XmpValueTest_833, SizeIsZeroWhenWriteProducesEmpty_833) {
  TestXmpValue833 v;
  v.setPayload("");

  const size_t sz = v.size();

  EXPECT_EQ(sz, 0u);
  EXPECT_EQ(v.writeCalls(), 1);
}

TEST_F(XmpValueTest_833, SizeHandlesLargeOutput_833) {
  TestXmpValue833 v;
  const std::string big(4096, 'x');
  v.setPayload(big);

  const size_t sz = v.size();

  EXPECT_EQ(sz, big.size());
  EXPECT_EQ(v.writeCalls(), 1);
}

TEST_F(XmpValueTest_833, SizeDoesNotThrowIfWriteSetsStreamFailbit_833) {
  TestXmpValue833 v;
  v.setPayload("will-not-be-written");
  v.setSetFailbit(true);

  EXPECT_NO_THROW({
    const size_t sz = v.size();
    // Observable behavior: size is computed from the stream's accumulated string.
    // If write doesn't insert characters, size should be 0.
    EXPECT_EQ(sz, 0u);
  });

  EXPECT_EQ(v.writeCalls(), 1);
}