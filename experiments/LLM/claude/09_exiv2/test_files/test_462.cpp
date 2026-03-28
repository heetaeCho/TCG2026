#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Minimal stubs for Exiv2 types needed by the interface
namespace Exiv2 {

// Minimal ExifData stub
class ExifData {};

// Translation macro stub
#ifndef EXV_HAVE_LIBINTL
#define _(String) String
#endif

// Minimal Value interface
class Value {
 public:
  virtual ~Value() = default;
  virtual std::string toString() const = 0;
  virtual std::ostream& write(std::ostream& os) const = 0;

  friend std::ostream& operator<<(std::ostream& os, const Value& v) {
    return v.write(os);
  }
};

namespace Internal {

class Nikon3MakerNote {
 public:
  std::ostream& print0x0007(std::ostream& os, const Value& value, const ExifData*) {
    std::string focus = value.toString();
    if (focus == "AF-C  ")
      return os << ("Continuous autofocus");
    if (focus == "AF-S  ")
      return os << ("Single autofocus");
    if (focus == "AF-A  ")
      return os << ("Automatic");
    return os << "(" << value << ")";
  }
};

}  // namespace Internal
}  // namespace Exiv2

// Mock for Value to control toString() and operator<< output
class MockValue : public Exiv2::Value {
 public:
  MOCK_METHOD(std::string, toString, (), (const, override));
  MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const, override));
};

class Nikon3MakerNoteTest_462 : public ::testing::Test {
 protected:
  Exiv2::Internal::Nikon3MakerNote maker_note_;
  std::ostringstream os_;
};

// Test: AF-C with trailing spaces returns "Continuous autofocus"
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_ContinuousAutofocus_462) {
  MockValue value;
  // Note: The code checks for "AF-C  " (AF-C followed by two spaces)
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-C  "));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "Continuous autofocus");
}

// Test: AF-S with trailing spaces returns "Single autofocus"
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_SingleAutofocus_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-S  "));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "Single autofocus");
}

// Test: AF-A with trailing spaces returns "Automatic"
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_Automatic_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-A  "));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "Automatic");
}

// Test: Unknown value falls through to default format "(value)"
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_UnknownValue_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("MF    "));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "MF    ";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(MF    )");
}

// Test: Empty string falls through to default format
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_EmptyString_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return(""));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "()");
}

// Test: AF-C without trailing spaces does NOT match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_AFC_NoTrailingSpaces_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-C"));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "AF-C";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(AF-C)");
}

// Test: AF-S without trailing spaces does NOT match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_AFS_NoTrailingSpaces_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-S"));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "AF-S";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(AF-S)");
}

// Test: AF-A without trailing spaces does NOT match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_AFA_NoTrailingSpaces_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-A"));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "AF-A";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(AF-A)");
}

// Test: Passing nullptr for ExifData does not cause a crash
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_NullExifData_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-C  "));

  EXPECT_NO_THROW(maker_note_.print0x0007(os_, value, nullptr));
  EXPECT_EQ(os_.str(), "Continuous autofocus");
}

// Test: AF-C with only one trailing space does NOT match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_AFC_OneTrailingSpace_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-C "));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "AF-C ";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(AF-C )");
}

// Test: Case sensitivity - lowercase "af-c  " should not match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_LowercaseAFC_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("af-c  "));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "af-c  ";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(af-c  )");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_ReturnsOstream_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-A  "));

  std::ostream& result = maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(&result, &os_);
}

// Test: AF-C with three trailing spaces does NOT match
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_AFC_ThreeTrailingSpaces_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("AF-C   "));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "AF-C   ";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(AF-C   )");
}

// Test: Random string falls through to default
TEST_F(Nikon3MakerNoteTest_462, PrintFocusMode_RandomString_462) {
  MockValue value;
  EXPECT_CALL(value, toString()).WillOnce(::testing::Return("SomeRandomFocusMode"));
  EXPECT_CALL(value, write(::testing::_)).WillOnce(::testing::Invoke([](std::ostream& os) -> std::ostream& {
    os << "SomeRandomFocusMode";
    return os;
  }));

  maker_note_.print0x0007(os_, value, nullptr);

  EXPECT_EQ(os_.str(), "(SomeRandomFocusMode)");
}
