// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 761
//
// Unit tests for Exiv2::Exifdatum::toFloat(size_t)
//
// Constraints honored:
// - Treat implementation as black box
// - Use only public interfaces / observable behavior
// - Use a test Value subclass only as an external collaborator injected via ctor
// - No access to private state

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <limits>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace {

using ::testing::ElementsAre;

struct ToFloatState {
  std::vector<size_t> calls;
  std::unordered_map<size_t, float> returns;
  float default_return = 0.0f;
};

class RecordingValue final : public Exiv2::Value {
 public:
  explicit RecordingValue(std::shared_ptr<ToFloatState> st, Exiv2::TypeId typeId = Exiv2::unsignedLong)
      : Exiv2::Value(typeId), st_(std::move(st)) {}

  float toFloat(size_t n) const override {
    st_->calls.push_back(n);
    auto it = st_->returns.find(n);
    return (it != st_->returns.end()) ? it->second : st_->default_return;
  }

 private:
  // Note: Value has a private virtual clone_() in Exiv2; Exifdatum typically clones Values.
  // We override it so cloning preserves our shared state (observable through calls/returns).
  const Exiv2::Value* clone_() override { return new RecordingValue(*this); }

  std::shared_ptr<ToFloatState> st_;
};

class ThrowingValue final : public Exiv2::Value {
 public:
  explicit ThrowingValue(Exiv2::TypeId typeId = Exiv2::unsignedLong) : Exiv2::Value(typeId) {}

  float toFloat(size_t /*n*/) const override { throw std::runtime_error("toFloat failed"); }

 private:
  const Exiv2::Value* clone_() override { return new ThrowingValue(*this); }
};

class ExifdatumToFloatTest_761 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Any syntactically valid Exif key should work for constructing Exifdatum.
    return Exiv2::ExifKey("Exif.Image.ImageDescription");
  }
};

TEST_F(ExifdatumToFloatTest_761, ReturnsMinusOneWhenValueIsNull_IndexZero_761) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_FLOAT_EQ(datum.toFloat(0), -1.0f);
}

TEST_F(ExifdatumToFloatTest_761, ReturnsMinusOneWhenValueIsNull_IndexMax_761) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_FLOAT_EQ(datum.toFloat(std::numeric_limits<size_t>::max()), -1.0f);
}

TEST_F(ExifdatumToFloatTest_761, ForwardsIndexAndReturnsUnderlyingValue_NormalOperation_761) {
  const Exiv2::ExifKey key = MakeKey();

  auto st = std::make_shared<ToFloatState>();
  st->default_return = 3.25f;
  st->returns[0] = 1.0f;
  st->returns[5] = -7.5f;

  auto* injected = new RecordingValue(st);  // Exifdatum takes/duplicates it; see next test.
  Exiv2::Exifdatum datum(key, injected);

  // If Exifdatum clones, deleting the injected object is safe and datum still works.
  delete injected;

  EXPECT_FLOAT_EQ(datum.toFloat(0), 1.0f);
  EXPECT_FLOAT_EQ(datum.toFloat(5), -7.5f);
  EXPECT_FLOAT_EQ(datum.toFloat(2), 3.25f);

  ASSERT_EQ(st->calls.size(), 3u);
  EXPECT_THAT(st->calls, ElementsAre(0u, 5u, 2u));
}

TEST_F(ExifdatumToFloatTest_761, SupportsVeryLargeIndex_ForwardedToValue_761) {
  const Exiv2::ExifKey key = MakeKey();

  auto st = std::make_shared<ToFloatState>();
  st->default_return = 9.0f;

  const size_t kBig = std::numeric_limits<size_t>::max();

  auto* injected = new RecordingValue(st);
  Exiv2::Exifdatum datum(key, injected);
  delete injected;

  EXPECT_FLOAT_EQ(datum.toFloat(kBig), 9.0f);

  ASSERT_EQ(st->calls.size(), 1u);
  EXPECT_EQ(st->calls[0], kBig);
}

TEST_F(ExifdatumToFloatTest_761, PropagatesExceptionFromUnderlyingValue_761) {
  const Exiv2::ExifKey key = MakeKey();

  auto* injected = new ThrowingValue();
  Exiv2::Exifdatum datum(key, injected);
  delete injected;

  EXPECT_THROW((void)datum.toFloat(0), std::runtime_error);
}

TEST_F(ExifdatumToFloatTest_761, NullValueDoesNotThrowEvenForLargeIndex_761) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_NO_THROW((void)datum.toFloat(std::numeric_limits<size_t>::max()));
  EXPECT_FLOAT_EQ(datum.toFloat(std::numeric_limits<size_t>::max()), -1.0f);
}

}  // namespace