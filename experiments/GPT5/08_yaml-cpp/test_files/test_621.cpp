// File: yaml_cpp_node_convert_binary_encode_test_621.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class BinaryEncodeTest_621 : public ::testing::Test {
protected:
  static std::string EncodeToScalar(const YAML::Binary& bin) {
    YAML::Node n = YAML::encode(bin);
    EXPECT_TRUE(n.IsScalar());
    return n.Scalar();
  }
};

TEST_F(BinaryEncodeTest_621, EmptyBinaryEncodesToEmptyString_621) {
  const YAML::Binary empty;
  const std::string out = EncodeToScalar(empty);
  EXPECT_EQ(out, "");
}

TEST_F(BinaryEncodeTest_621, AsciiManEncodesToTWFu_621) {
  const unsigned char data[] = {'M', 'a', 'n'};
  const YAML::Binary bin(data, sizeof(data));

  const std::string out = EncodeToScalar(bin);
  EXPECT_EQ(out, "TWFu");
}

TEST_F(BinaryEncodeTest_621, SingleZeroByteEncodesToAAEqEq_621) {
  const unsigned char data[] = {0x00};
  const YAML::Binary bin(data, sizeof(data));

  const std::string out = EncodeToScalar(bin);
  EXPECT_EQ(out, "AA==");
}

TEST_F(BinaryEncodeTest_621, TwoBytesFFEEEncodesToSlashPlus4Eq_621) {
  const unsigned char data[] = {0xFF, 0xEE};
  const YAML::Binary bin(data, sizeof(data));

  const std::string out = EncodeToScalar(bin);
  EXPECT_EQ(out, "/+4=");
}

TEST_F(BinaryEncodeTest_621, OwnedAndUnownedBinaryProduceSameScalar_621) {
  // Unowned: constructed from external buffer
  const unsigned char data[] = {'M', 'a', 'n'};
  const YAML::Binary unowned(data, sizeof(data));

  // Owned: move bytes into Binary via swap(std::vector<unsigned char>&)
  std::vector<unsigned char> v = {'M', 'a', 'n'};
  YAML::Binary owned;
  owned.swap(v);

  const std::string out_unowned = EncodeToScalar(unowned);
  const std::string out_owned = EncodeToScalar(owned);

  EXPECT_EQ(out_owned, out_unowned);
}

}  // namespace