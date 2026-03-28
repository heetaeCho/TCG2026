// TEST_ID 788
// File: value_toString_test_788.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <ios>
#include <ostream>
#include <string>

namespace {

// Avoid depending on specific TypeId enumerators.
inline Exiv2::TypeId AnyTypeId() {
  return static_cast<Exiv2::TypeId>(0);
}

// A simple controllable Value for black-box testing of Value::toString().
class ControlledWriteValue : public Exiv2::Value {
 public:
  enum class Mode {
    kWriteTextOk,
    kWriteEmptyOk,
    kSetFailBitAfterWrite,
    kSetBadBitImmediately,
  };

  explicit ControlledWriteValue(Mode mode, std::string text = "")
      : Exiv2::Value(AnyTypeId()), mode_(mode), text_(std::move(text)) {}

  const std::ostream& write(std::ostream& os) override {
    switch (mode_) {
      case Mode::kWriteTextOk:
        os << text_;
        break;
      case Mode::kWriteEmptyOk:
        // Write nothing; keep stream state good.
        break;
      case Mode::kSetFailBitAfterWrite:
        os << text_;
        os.setstate(std::ios::failbit);
        break;
      case Mode::kSetBadBitImmediately:
        os.setstate(std::ios::badbit);
        break;
    }
    return os;
  }

  void setMode(Mode mode) { mode_ = mode; }
  void setText(std::string text) { text_ = std::move(text); }

 private:
  Mode mode_;
  std::string text_;
};

class MockValue : public Exiv2::Value {
 public:
  MockValue() : Exiv2::Value(AnyTypeId()) {}

  MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (override));
};

class ValueToStringTest_788 : public ::testing::Test {};

}  // namespace

TEST_F(ValueToStringTest_788, ToStringReturnsWrittenContentAndOkTrue_788) {
  ControlledWriteValue v(ControlledWriteValue::Mode::kWriteTextOk, "hello");
  const std::string s = v.toString();

  EXPECT_EQ(s, "hello");
  EXPECT_TRUE(v.ok());
}

TEST_F(ValueToStringTest_788, ToStringWhenWriteOutputsEmptyStringOkTrue_788) {
  ControlledWriteValue v(ControlledWriteValue::Mode::kWriteEmptyOk);
  const std::string s = v.toString();

  EXPECT_EQ(s, "");
  EXPECT_TRUE(v.ok());
}

TEST_F(ValueToStringTest_788, ToStringWhenWriteSetsFailBitOkBecomesFalse_788) {
  ControlledWriteValue v(ControlledWriteValue::Mode::kSetFailBitAfterWrite, "x");
  const std::string s = v.toString();

  // The returned string is observable output; stream may still have captured text.
  EXPECT_EQ(s, "x");
  EXPECT_FALSE(v.ok());
}

TEST_F(ValueToStringTest_788, ToStringWhenWriteSetsBadBitOkBecomesFalse_788) {
  ControlledWriteValue v(ControlledWriteValue::Mode::kSetBadBitImmediately);
  const std::string s = v.toString();

  // If the stream is put into a bad state immediately, the produced string may be empty.
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(v.ok());
}

TEST_F(ValueToStringTest_788, ToStringCalledTwiceUpdatesOkEachTime_788) {
  ControlledWriteValue v(ControlledWriteValue::Mode::kSetFailBitAfterWrite, "first");
  EXPECT_EQ(v.toString(), "first");
  EXPECT_FALSE(v.ok());

  v.setMode(ControlledWriteValue::Mode::kWriteTextOk);
  v.setText("second");
  EXPECT_EQ(v.toString(), "second");
  EXPECT_TRUE(v.ok());
}

TEST_F(ValueToStringTest_788, ToStringInvokesWriteOncePerCall_788) {
  using ::testing::Invoke;
  using ::testing::StrictMock;

  StrictMock<MockValue> v;

  EXPECT_CALL(v, write(::testing::_))
      .Times(1)
      .WillOnce(Invoke([](std::ostream& os) -> const std::ostream& {
        os << "abc";
        return os;
      }));

  const std::string s = v.toString();
  EXPECT_EQ(s, "abc");
  EXPECT_TRUE(v.ok());
}