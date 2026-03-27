// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for ./TestProjects/exiv2/src/panasonicmn_int.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

// Treat implementation as black-box: declare only the interface we need and link to the real code.
namespace Exiv2::Internal {
class PanasonicMakerNote {
public:
  std::ostream& printPanasonicText(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
};
}  // namespace Exiv2::Internal

namespace {

class PanasonicMakerNoteTest_713 : public ::testing::Test {
protected:
  Exiv2::Internal::PanasonicMakerNote sut_;

  static Exiv2::Value::UniquePtr makeUndefinedValue(const std::vector<Exiv2::byte>& bytes) {
    auto v = Exiv2::Value::create(Exiv2::undefined);
    // For undefined data, byte order should not matter; provide a valid one anyway.
    if (!bytes.empty()) {
      v->read(bytes.data(), static_cast<long>(bytes.size()), Exiv2::littleEndian);
    } else {
      // Ensure size() == 0
      v->read(nullptr, 0, Exiv2::littleEndian);
    }
    return v;
  }

  template <typename SetFn>
  static Exiv2::Value::UniquePtr makeValue(Exiv2::TypeId type, SetFn&& setFn) {
    auto v = Exiv2::Value::create(type);
    setFn(*v);
    return v;
  }

  static std::string streamViaOperator(const Exiv2::Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static std::string streamViaSut(Exiv2::Internal::PanasonicMakerNote& sut, const Exiv2::Value& v,
                                  const Exiv2::ExifData* ed = nullptr) {
    std::ostringstream oss;
    sut.printPanasonicText(oss, v, ed);
    return oss.str();
  }
};

TEST_F(PanasonicMakerNoteTest_713, UndefinedPrintsCharsUntilFirstNull_713) {
  const std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>('A'),
      static_cast<Exiv2::byte>('B'),
      static_cast<Exiv2::byte>('C'),
      static_cast<Exiv2::byte>(0),
      static_cast<Exiv2::byte>('D'),
  };
  auto v = makeUndefinedValue(bytes);

  const std::string out = streamViaSut(sut_, *v, nullptr);
  EXPECT_EQ(out, "ABC");
}

TEST_F(PanasonicMakerNoteTest_713, UndefinedWithNoNullPrintsAllBytesAsChars_713) {
  const std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>('H'),
      static_cast<Exiv2::byte>('i'),
      static_cast<Exiv2::byte>('!'),
  };
  auto v = makeUndefinedValue(bytes);

  const std::string out = streamViaSut(sut_, *v, nullptr);
  EXPECT_EQ(out, "Hi!");
}

TEST_F(PanasonicMakerNoteTest_713, UndefinedEmptyFallsBackToOperatorOutput_713) {
  auto v = makeUndefinedValue({});  // size() == 0

  const std::string expected = streamViaOperator(*v);
  const std::string out = streamViaSut(sut_, *v, nullptr);
  EXPECT_EQ(out, expected);
}

TEST_F(PanasonicMakerNoteTest_713, NonUndefinedFallsBackToOperatorOutput_713) {
  // Use a non-undefined Value type and verify we get exactly what operator<< would emit.
  auto v = makeValue(Exiv2::asciiString, [](Exiv2::Value& vv) { vv.read("Hello"); });

  const std::string expected = streamViaOperator(*v);
  const std::string out = streamViaSut(sut_, *v, nullptr);
  EXPECT_EQ(out, expected);
}

TEST_F(PanasonicMakerNoteTest_713, ExifDataPointerIsOptionalAndDoesNotChangeOutput_713) {
  const std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>('T'),
      static_cast<Exiv2::byte>('e'),
      static_cast<Exiv2::byte>('s'),
      static_cast<Exiv2::byte>('t'),
      static_cast<Exiv2::byte>(0),
  };
  auto v = makeUndefinedValue(bytes);

  Exiv2::ExifData ed;
  const std::string out_with_null = streamViaSut(sut_, *v, nullptr);
  const std::string out_with_ptr = streamViaSut(sut_, *v, &ed);

  EXPECT_EQ(out_with_null, "Test");
  EXPECT_EQ(out_with_ptr, "Test");
  EXPECT_EQ(out_with_ptr, out_with_null);
}

}  // namespace