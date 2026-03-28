// ============================================================================
// TEST_ID: 688
// File: test_iptcdatum_operator_assign_string_688.cpp
// Unit tests for Exiv2::Iptcdatum::operator=(const std::string&)
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>

#include <cstddef>
#include <stdexcept>
#include <string>

namespace {

class SpyIptcdatum_688 : public Exiv2::Iptcdatum {
 public:
  explicit SpyIptcdatum_688(const Exiv2::IptcKey& key, const Exiv2::Value* v = nullptr)
      : Exiv2::Iptcdatum(key, v) {
  }

  // Observe forwarding behavior from operator= without relying on internal state.
  int setValue(const std::string& value) override {
    ++set_value_calls_;
    last_value_ = value;
    if (throw_on_set_) {
      throw std::runtime_error("setValue forced throw");
    }
    return return_code_;
  }

  int set_value_calls() const { return set_value_calls_; }
  const std::string& last_value() const { return last_value_; }

  void set_throw_on_set(bool v) { throw_on_set_ = v; }
  void set_return_code(int rc) { return_code_ = rc; }

 private:
  int set_value_calls_{0};
  std::string last_value_;
  bool throw_on_set_{false};
  int return_code_{0};
};

class IptcdatumOperatorAssignStringTest_688 : public ::testing::Test {
 protected:
  // Use a well-known IPTC key string; exact semantics are irrelevant to these black-box tests.
  static Exiv2::IptcKey MakeKey() {
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumOperatorAssignStringTest_688, ForwardsToSetValueOnceAndReturnsSelf_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  const std::string v = "hello";
  Exiv2::Iptcdatum& ret = (d = v);

  EXPECT_EQ(&ret, &d);                 // operator= returns *this
  EXPECT_EQ(d.set_value_calls(), 1);   // forwards exactly once
  EXPECT_EQ(d.last_value(), v);        // forwards the same string
}

TEST_F(IptcdatumOperatorAssignStringTest_688, AssignEmptyString_ForwardsToSetValue_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  const std::string v;
  (void)(d = v);

  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value(), v);
}

TEST_F(IptcdatumOperatorAssignStringTest_688, AssignLongString_ForwardsToSetValue_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  const std::string v(1024 * 16, 'x');
  (void)(d = v);

  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value().size(), v.size());
  EXPECT_EQ(d.last_value(), v);
}

TEST_F(IptcdatumOperatorAssignStringTest_688, AssignStringWithEmbeddedNull_ForwardsToSetValue_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  std::string v("ab");
  v.push_back('\0');
  v += "cd";

  (void)(d = v);

  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value().size(), v.size());
  EXPECT_EQ(d.last_value(), v);
}

TEST_F(IptcdatumOperatorAssignStringTest_688, AssignUtf8String_ForwardsToSetValue_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  const std::string v = u8"한글-テスト-emoji🙂";
  (void)(d = v);

  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value(), v);
}

TEST_F(IptcdatumOperatorAssignStringTest_688, IfSetValueThrows_ExceptionPropagates_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);
  d.set_throw_on_set(true);

  EXPECT_THROW(
      {
        // operator= should not swallow exceptions thrown by setValue
        (void)(d = std::string("boom"));
      },
      std::runtime_error);

  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value(), "boom");
}

TEST_F(IptcdatumOperatorAssignStringTest_688, RepeatedAssignments_ForwardEachTime_688) {
  SpyIptcdatum_688 d(MakeKey(), nullptr);

  (void)(d = std::string("one"));
  EXPECT_EQ(d.set_value_calls(), 1);
  EXPECT_EQ(d.last_value(), "one");

  (void)(d = std::string("two"));
  EXPECT_EQ(d.set_value_calls(), 2);
  EXPECT_EQ(d.last_value(), "two");
}

}  // namespace