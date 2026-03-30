// TEST_ID: 190
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <map>
#include <memory>

namespace YAML {
namespace detail {

// Provide MapIter for the partial class under test (as given in the prompt).
class MockNode {
 public:
  MOCK_METHOD(bool, is_defined, (), (const));
};

// MapIter must support: it->first->is_defined() && it->second->is_defined()
using MapIter =
    std::map<std::shared_ptr<MockNode>, std::shared_ptr<MockNode>>::iterator;

// Partial implementation under test (from prompt).
class node_iterator_base {
 public:
  bool is_defined(MapIter it) const {
    return it->first->is_defined() && it->second->is_defined();
  }
};

}  // namespace detail
}  // namespace YAML

namespace {

using ::testing::Return;
using ::testing::StrictMock;

class NodeIteratorBaseIsDefinedTest_190 : public ::testing::Test {
 protected:
  using Node = YAML::detail::MockNode;
  using Iter = YAML::detail::MapIter;

  Iter AddPair(std::shared_ptr<Node> key, std::shared_ptr<Node> value) {
    auto ins = m_map.emplace(std::move(key), std::move(value));
    return ins.first;
  }

  YAML::detail::node_iterator_base sut_;
  std::map<std::shared_ptr<Node>, std::shared_ptr<Node>> m_map;
};

TEST_F(NodeIteratorBaseIsDefinedTest_190, ReturnsTrueWhenKeyAndValueAreDefined_190) {
  auto key = std::make_shared<StrictMock<Node>>();
  auto val = std::make_shared<StrictMock<Node>>();
  auto it = AddPair(key, val);

  EXPECT_CALL(*key, is_defined()).WillOnce(Return(true));
  EXPECT_CALL(*val, is_defined()).WillOnce(Return(true));

  EXPECT_TRUE(sut_.is_defined(it));
}

TEST_F(NodeIteratorBaseIsDefinedTest_190, ReturnsFalseWhenKeyIsNotDefined_190) {
  auto key = std::make_shared<StrictMock<Node>>();
  auto val = std::make_shared<StrictMock<Node>>();
  auto it = AddPair(key, val);

  // Short-circuit behavior is observable via external interaction:
  // if key is not defined, value::is_defined() must not be called.
  EXPECT_CALL(*key, is_defined()).WillOnce(Return(false));
  EXPECT_CALL(*val, is_defined()).Times(0);

  EXPECT_FALSE(sut_.is_defined(it));
}

TEST_F(NodeIteratorBaseIsDefinedTest_190, ReturnsFalseWhenValueIsNotDefined_190) {
  auto key = std::make_shared<StrictMock<Node>>();
  auto val = std::make_shared<StrictMock<Node>>();
  auto it = AddPair(key, val);

  EXPECT_CALL(*key, is_defined()).WillOnce(Return(true));
  EXPECT_CALL(*val, is_defined()).WillOnce(Return(false));

  EXPECT_FALSE(sut_.is_defined(it));
}

TEST_F(NodeIteratorBaseIsDefinedTest_190, ReturnsFalseWhenBothKeyAndValueAreNotDefined_190) {
  auto key = std::make_shared<StrictMock<Node>>();
  auto val = std::make_shared<StrictMock<Node>>();
  auto it = AddPair(key, val);

  // Still short-circuits after the key.
  EXPECT_CALL(*key, is_defined()).WillOnce(Return(false));
  EXPECT_CALL(*val, is_defined()).Times(0);

  EXPECT_FALSE(sut_.is_defined(it));
}

}  // namespace