// TEST_ID: 618
#include <gtest/gtest.h>

#include <valarray>
#include <string>

#include <yaml-cpp/yaml.h>

// These tests target YAML::convert<std::valarray<T>>::decode(const Node&, std::valarray<T>&)
// as implemented in yaml-cpp/node/convert.h (valarray specialization).

namespace {

class ValarrayDecodeTest_618 : public ::testing::Test {
 protected:
  template <typename T>
  static bool DecodeFromYaml(const std::string& yaml, std::valarray<T>& out) {
    YAML::Node node = YAML::Load(yaml);
    return YAML::convert<std::valarray<T>>::decode(node, out);
  }
};

}  // namespace

TEST_F(ValarrayDecodeTest_618, DecodeNonSequenceReturnsFalse_618) {
  std::valarray<int> out(3);
  // Scalar node is not a sequence -> decode should fail.
  EXPECT_FALSE(DecodeFromYaml<int>("123", out));
}

TEST_F(ValarrayDecodeTest_618, DecodeEmptySequenceProducesEmptyValarray_618) {
  std::valarray<int> out(5);
  ASSERT_TRUE(DecodeFromYaml<int>("[]", out));
  EXPECT_EQ(out.size(), 0u);
}

TEST_F(ValarrayDecodeTest_618, DecodeSequenceResizesAndPopulatesIntValues_618) {
  std::valarray<int> out;  // starts empty
  ASSERT_TRUE(DecodeFromYaml<int>("[1, 2, 3, 4]", out));
  ASSERT_EQ(out.size(), 4u);

  EXPECT_EQ(out[0], 1);
  EXPECT_EQ(out[1], 2);
  EXPECT_EQ(out[2], 3);
  EXPECT_EQ(out[3], 4);
}

TEST_F(ValarrayDecodeTest_618, DecodeSequenceOverwritesExistingContents_618) {
  std::valarray<int> out(3);
  out[0] = 9;
  out[1] = 9;
  out[2] = 9;

  ASSERT_TRUE(DecodeFromYaml<int>("[7, 8]", out));
  ASSERT_EQ(out.size(), 2u);
  EXPECT_EQ(out[0], 7);
  EXPECT_EQ(out[1], 8);
}

TEST_F(ValarrayDecodeTest_618, DecodeSequenceIntoDoubleSupportsNonIntegers_618) {
  std::valarray<double> out;
  ASSERT_TRUE(DecodeFromYaml<double>("[1, 2.5, -3.25]", out));
  ASSERT_EQ(out.size(), 3u);

  EXPECT_DOUBLE_EQ(out[0], 1.0);
  EXPECT_DOUBLE_EQ(out[1], 2.5);
  EXPECT_DOUBLE_EQ(out[2], -3.25);
}

TEST_F(ValarrayDecodeTest_618, DecodeThrowsWhenElementConversionFails_618) {
  YAML::Node node = YAML::Load("[1, not_an_int, 3]");
  std::valarray<int> out;

  // decode internally calls node[i].as<T>(); conversion failure is observable as an exception.
  EXPECT_THROW((YAML::convert<std::valarray<int>>::decode(node, out)), YAML::BadConversion);
}

TEST_F(ValarrayDecodeTest_618, DecodeLargeSequenceMaintainsOrderAndSize_618) {
  // Build a moderately large sequence to exercise resizing and iteration.
  YAML::Node node(YAML::NodeType::Sequence);
  constexpr int kN = 1024;
  for (int i = 0; i < kN; ++i) {
    node.push_back(i);
  }

  std::valarray<int> out(1);
  ASSERT_TRUE(YAML::convert<std::valarray<int>>::decode(node, out));
  ASSERT_EQ(out.size(), static_cast<std::size_t>(kN));

  // Spot-check a few positions including boundaries.
  EXPECT_EQ(out[0], 0);
  EXPECT_EQ(out[1], 1);
  EXPECT_EQ(out[17], 17);
  EXPECT_EQ(out[kN - 2], kN - 2);
  EXPECT_EQ(out[kN - 1], kN - 1);
}