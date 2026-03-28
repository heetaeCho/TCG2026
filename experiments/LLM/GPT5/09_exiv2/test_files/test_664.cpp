// =================================================================================================
// TestProjects/exiv2/src/iptc_test_664.cpp
// Unit tests for Exiv2::Iptcdatum::write (partial interface provided)
// TEST_ID: 664
// =================================================================================================

#include <gtest/gtest.h>

#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {

// Minimal stub to satisfy the interface: the production code takes `const ExifData*`.
// We do NOT assume anything about ExifData other than it being a type.
struct ExifData {};

// The provided partial implementation (treated as the interface we can observe).
class Iptcdatum {
public:
  std::ostream& write(std::ostream& os, const ExifData*) const { return os << value(); }

  // Not provided in the prompt, but required for compilation of `write()`.
  // We keep this as a minimal, controllable surface for testing `write()` behavior.
  virtual std::string value() const = 0;

  virtual ~Iptcdatum() = default;
};

}  // namespace Exiv2

namespace {

// Concrete test double that lets us control `value()` without inferring internal logic.
class TestIptcdatum final : public Exiv2::Iptcdatum {
public:
  explicit TestIptcdatum(std::string v) : v_(std::move(v)) {}
  std::string value() const override { return v_; }

private:
  std::string v_;
};

class IptcdatumWriteTest_664 : public ::testing::Test {};

TEST_F(IptcdatumWriteTest_664, WritesValueToStream_664) {
  TestIptcdatum datum("Hello IPTC");
  std::ostringstream os;

  Exiv2::ExifData exif;  // non-null pointer case (should be ignored per observable behavior)
  std::ostream& ret = datum.write(os, &exif);

  EXPECT_EQ(os.str(), "Hello IPTC");
  EXPECT_EQ(&ret, &os);  // must return the same stream reference (observable)
}

TEST_F(IptcdatumWriteTest_664, WritesEmptyValueProducesNoOutput_664) {
  TestIptcdatum datum("");
  std::ostringstream os;

  std::ostream& ret = datum.write(os, nullptr);

  EXPECT_EQ(os.str(), "");
  EXPECT_EQ(&ret, &os);
}

TEST_F(IptcdatumWriteTest_664, PreservesExistingStreamContentAndAppends_664) {
  TestIptcdatum datum("XYZ");
  std::ostringstream os;
  os << "prefix:";

  std::ostream& ret = datum.write(os, nullptr);

  EXPECT_EQ(os.str(), "prefix:XYZ");
  EXPECT_EQ(&ret, &os);
}

TEST_F(IptcdatumWriteTest_664, WorksWithNonNullExifDataPointerAndNullPointerEqually_664) {
  TestIptcdatum datum("same");
  std::ostringstream os1;
  std::ostringstream os2;

  Exiv2::ExifData exif;
  datum.write(os1, &exif);
  datum.write(os2, nullptr);

  EXPECT_EQ(os1.str(), "same");
  EXPECT_EQ(os2.str(), "same");
}

TEST_F(IptcdatumWriteTest_664, WritesUnicodeUtf8TextAsIs_664) {
  // Boundary-ish: non-ASCII / UTF-8 content should be streamed verbatim.
  // We only validate observable bytes in the stream, not any internal encoding logic.
  const std::string utf8 = u8"한글-✓-é";
  TestIptcdatum datum(utf8);
  std::ostringstream os;

  datum.write(os, nullptr);

  EXPECT_EQ(os.str(), utf8);
}

TEST_F(IptcdatumWriteTest_664, StreamFailureStateIsObservableAfterWrite_664) {
  // Exceptional/error case (observable through interface): writing into a stream that
  // already has failbit set should keep the stream in a failed state.
  // We don't assume how operator<< behaves internally; we only observe flags.
  TestIptcdatum datum("data");
  std::ostringstream os;
  os.setstate(std::ios::failbit);

  std::ostream& ret = datum.write(os, nullptr);

  EXPECT_TRUE(os.fail());
  EXPECT_EQ(&ret, &os);
}

}  // namespace