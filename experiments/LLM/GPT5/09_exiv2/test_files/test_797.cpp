// File: test_data_value_write_797.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class DataValueTest_797 : public ::testing::Test {
 protected:
  // Use a commonly valid Exiv2 TypeId for DataValue construction.
  Exiv2::DataValue MakeValue() { return Exiv2::DataValue(Exiv2::unsignedByte); }
};

TEST_F(DataValueTest_797, WriteEmptyValueProducesNoOutput_797) {
  Exiv2::DataValue v = MakeValue();

  std::ostringstream os;
  std::ostream& ret = v.write(os);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "");
}

TEST_F(DataValueTest_797, WriteSingleElementHasNoSpaces_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(7));

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), "7");
}

TEST_F(DataValueTest_797, WriteMultipleElementsAreSpaceSeparatedNoTrailingSpace_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(1));
  v.value_.push_back(static_cast<Exiv2::byte>(2));
  v.value_.push_back(static_cast<Exiv2::byte>(3));

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), "1 2 3");
  EXPECT_FALSE(!os.str().empty() && os.str().back() == ' ');
}

TEST_F(DataValueTest_797, WritePreservesExistingStreamContentsByAppending_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(9));
  v.value_.push_back(static_cast<Exiv2::byte>(10));

  std::ostringstream os;
  os << "prefix:";

  v.write(os);

  EXPECT_EQ(os.str(), "prefix:9 10");
}

TEST_F(DataValueTest_797, WriteHandlesBoundaryByteValues_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(0));
  v.value_.push_back(static_cast<Exiv2::byte>(255));

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), "0 255");
}

TEST_F(DataValueTest_797, WriteReturnsSameOstreamReference_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(42));

  std::ostringstream os;
  std::ostream& ret = v.write(os);

  EXPECT_EQ(&ret, &os);
}

TEST_F(DataValueTest_797, WriteDoesNotClearFailStateOnStream_797) {
  Exiv2::DataValue v = MakeValue();
  v.value_.push_back(static_cast<Exiv2::byte>(1));
  v.value_.push_back(static_cast<Exiv2::byte>(2));

  std::ostringstream os;
  os.setstate(std::ios::failbit);

  std::ostream& ret = v.write(os);

  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.fail());
}

}  // namespace