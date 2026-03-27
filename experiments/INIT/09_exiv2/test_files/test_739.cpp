// File: test_exifdatum_setvalue_739.cpp
// Unit tests for Exiv2::Exifdatum::setValue(const Value*)
// TEST_ID: 739

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <atomic>
#include <memory>
#include <stdexcept>
#include <string>

namespace {

// A Value test-double that lets us observe whether Exifdatum::setValue()
// triggers cloning via Value::clone() (which dispatches to virtual clone_()).
class CountingCloneValue final : public Exiv2::Value {
 public:
  explicit CountingCloneValue(Exiv2::TypeId typeId) : Exiv2::Value(typeId) {}
  CountingCloneValue(const CountingCloneValue&) = default;
  ~CountingCloneValue() override = default;

  static void Reset() { clone_calls.store(0); }
  static int CloneCalls() { return clone_calls.load(); }

 private:
  // Value::clone() uses a virtual clone_() hook. Even though clone_() is private
  // in the base class, it can still be overridden.
  const Exiv2::Value* clone_() override {
    clone_calls.fetch_add(1);
    return new CountingCloneValue(*this);
  }

  static std::atomic<int> clone_calls;
};

std::atomic<int> CountingCloneValue::clone_calls{0};

class ThrowingCloneValue final : public Exiv2::Value {
 public:
  explicit ThrowingCloneValue(Exiv2::TypeId typeId) : Exiv2::Value(typeId) {}
  ThrowingCloneValue(const ThrowingCloneValue&) = default;
  ~ThrowingCloneValue() override = default;

 private:
  const Exiv2::Value* clone_() override { throw std::runtime_error("clone failed"); }
};

class ExifdatumSetValueTest_739 : public ::testing::Test {
 protected:
  ExifdatumSetValueTest_739()
      : key_("Exif.Image.Make"),
        datum_(key_, nullptr) {}

  Exiv2::ExifKey key_;
  Exiv2::Exifdatum datum_;
};

}  // namespace

TEST_F(ExifdatumSetValueTest_739, NullptrClearsStoredValue_739) {
  // Arrange: store an initial value
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(v));
  ASSERT_EQ(0, v->read(std::string("abc")));
  datum_.setValue(v.get());

  // Sanity: getValue() should be non-null after setting a non-null value
  auto before_clear = datum_.getValue();
  ASSERT_TRUE(static_cast<bool>(before_clear));

  // Act
  datum_.setValue(nullptr);

  // Assert: observable state via getValue()
  auto after_clear = datum_.getValue();
  EXPECT_FALSE(static_cast<bool>(after_clear));
}

TEST_F(ExifdatumSetValueTest_739, NonNullUsesCloneNotAlias_739) {
  // This test checks the *observable effect* of cloning: subsequent mutation of the
  // original Value must not change the Exifdatum's stored representation.
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(v));

  ASSERT_EQ(0, v->read(std::string("first")));
  datum_.setValue(v.get());

  // Mutate the original Value after setting it into Exifdatum.
  ASSERT_EQ(0, v->read(std::string("second")));

  // Exifdatum should remain "first" if it cloned rather than aliased.
  EXPECT_EQ(std::string("first"), datum_.toString());
}

TEST_F(ExifdatumSetValueTest_739, ReplacesPreviouslyStoredValue_739) {
  auto v1 = Exiv2::Value::create(Exiv2::asciiString);
  auto v2 = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(v1));
  ASSERT_TRUE(static_cast<bool>(v2));

  ASSERT_EQ(0, v1->read(std::string("one")));
  ASSERT_EQ(0, v2->read(std::string("two")));

  datum_.setValue(v1.get());
  EXPECT_EQ(std::string("one"), datum_.toString());

  datum_.setValue(v2.get());
  EXPECT_EQ(std::string("two"), datum_.toString());
}

TEST_F(ExifdatumSetValueTest_739, RepeatedNullptrIsIdempotent_739) {
  datum_.setValue(nullptr);
  auto v0 = datum_.getValue();
  EXPECT_FALSE(static_cast<bool>(v0));

  datum_.setValue(nullptr);
  auto v1 = datum_.getValue();
  EXPECT_FALSE(static_cast<bool>(v1));
}

TEST_F(ExifdatumSetValueTest_739, CallsCloneExactlyOncePerNonNullSet_739) {
  CountingCloneValue::Reset();

  CountingCloneValue cv(Exiv2::asciiString);
  datum_.setValue(&cv);
  EXPECT_EQ(1, CountingCloneValue::CloneCalls());

  datum_.setValue(&cv);
  EXPECT_EQ(2, CountingCloneValue::CloneCalls());
}

TEST_F(ExifdatumSetValueTest_739, DoesNotCallCloneWhenNullptr_739) {
  CountingCloneValue::Reset();

  datum_.setValue(nullptr);
  EXPECT_EQ(0, CountingCloneValue::CloneCalls());
}

TEST_F(ExifdatumSetValueTest_739, PropagatesExceptionIfCloneThrows_739) {
  ThrowingCloneValue tv(Exiv2::asciiString);
  EXPECT_THROW(datum_.setValue(&tv), std::runtime_error);
}

TEST_F(ExifdatumSetValueTest_739, AfterExceptionPreviouslyStoredValueRemainsUsable_739) {
  // Arrange: set a known good value first
  auto good = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(static_cast<bool>(good));
  ASSERT_EQ(0, good->read(std::string("stable")));
  datum_.setValue(good.get());
  EXPECT_EQ(std::string("stable"), datum_.toString());

  // Act: attempt to set a value whose clone throws
  ThrowingCloneValue bad(Exiv2::asciiString);
  EXPECT_THROW(datum_.setValue(&bad), std::runtime_error);

  // Assert: Exifdatum remains observable/usable via its public API
  // (If implementation provides strong/weak exception safety, this should still pass.)
  EXPECT_EQ(std::string("stable"), datum_.toString());
}