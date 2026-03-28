// TEST_ID: 186
#include <gtest/gtest.h>

#include <iterator>  // std::next
#include <yaml-cpp/yaml.h>

namespace {

using YAML::Node;

class NodeIteratorPostfixIncrementTest_186 : public ::testing::Test {
 protected:
  static Node MakeSequence123() {
    Node n(YAML::NodeType::Sequence);
    n.push_back(1);
    n.push_back(2);
    n.push_back(3);
    return n;
  }
};

TEST_F(NodeIteratorPostfixIncrementTest_186, PostIncrementReturnsPreviousIterator_186) {
  Node seq = MakeSequence123();

  auto it0 = seq.begin();
  auto it = it0;

  auto ret = it++;  // node_iterator_base<V>::operator++(int)

  // Returned iterator represents the original position.
  EXPECT_EQ(ret, it0);

  // The iterator being incremented advanced.
  EXPECT_NE(it, it0);
}

TEST_F(NodeIteratorPostfixIncrementTest_186, PostIncrementAdvancesToNextElementInSequence_186) {
  Node seq = MakeSequence123();

  auto it = seq.begin();
  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 1);

  auto prev = it++;
  ASSERT_NE(prev, seq.end());
  EXPECT_EQ(prev->as<int>(), 1);

  ASSERT_NE(it, seq.end());
  EXPECT_EQ(it->as<int>(), 2);
}

TEST_F(NodeIteratorPostfixIncrementTest_186, MultiplePostIncrementsProgressSequentially_186) {
  Node seq = MakeSequence123();

  auto it = seq.begin();
  auto begin = it;

  auto a = it++;
  auto b = it++;

  EXPECT_EQ(a, begin);
  EXPECT_EQ(b, std::next(begin));
  EXPECT_EQ(it, std::next(begin, 2));
}

TEST_F(NodeIteratorPostfixIncrementTest_186, PostIncrementFromLastElementReachesEnd_186) {
  Node seq = MakeSequence123();

  auto it_last = std::next(seq.begin(), 2);
  ASSERT_NE(it_last, seq.end());
  EXPECT_EQ(it_last->as<int>(), 3);

  auto ret = it_last++;  // increment last -> end

  // Returned iterator was last element.
  ASSERT_NE(ret, seq.end());
  EXPECT_EQ(ret->as<int>(), 3);

  // Now at end.
  EXPECT_EQ(it_last, seq.end());
}

TEST_F(NodeIteratorPostfixIncrementTest_186, PostIncrementDoesNotThrowForValidIterator_186) {
  Node seq = MakeSequence123();

  auto it = seq.begin();
  EXPECT_NO_THROW({
    auto unused = it++;
    (void)unused;
  });
}

}  // namespace