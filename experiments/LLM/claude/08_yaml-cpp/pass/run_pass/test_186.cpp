#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/node_iterator.h"

// Test ID: 186

// Test iteration over a YAML sequence (normal operation)
TEST(NodeIteratorTest_186, SequenceIterationNormal_186) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test iteration over a YAML map (normal operation)
TEST(NodeIteratorTest_186, MapIterationNormal_186) {
    YAML::Node node = YAML::Load("{a: 1, b: 2, c: 3}");
    ASSERT_TRUE(node.IsMap());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test post-increment operator returns previous position
TEST(NodeIteratorTest_186, PostIncrementReturnsPreviousPosition_186) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    ASSERT_TRUE(node.IsSequence());

    auto it = node.begin();
    auto prev = it++;

    // prev should point to the first element (10)
    EXPECT_EQ(prev->as<int>(), 10);
    // it should now point to the second element (20)
    EXPECT_EQ(it->as<int>(), 20);
}

// Test pre-increment operator
TEST(NodeIteratorTest_186, PreIncrementAdvancesIterator_186) {
    YAML::Node node = YAML::Load("[10, 20, 30]");
    ASSERT_TRUE(node.IsSequence());

    auto it = node.begin();
    auto& result = ++it;

    // After pre-increment, it should point to second element
    EXPECT_EQ(it->as<int>(), 20);
    EXPECT_EQ(result->as<int>(), 20);
}

// Test empty sequence iteration (boundary condition)
TEST(NodeIteratorTest_186, EmptySequenceIteration_186) {
    YAML::Node node = YAML::Load("[]");
    ASSERT_TRUE(node.IsSequence());

    EXPECT_TRUE(node.begin() == node.end());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test empty map iteration (boundary condition)
TEST(NodeIteratorTest_186, EmptyMapIteration_186) {
    YAML::Node node = YAML::Load("{}");
    ASSERT_TRUE(node.IsMap());

    EXPECT_TRUE(node.begin() == node.end());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);
}

// Test single element sequence (boundary condition)
TEST(NodeIteratorTest_186, SingleElementSequence_186) {
    YAML::Node node = YAML::Load("[42]");
    ASSERT_TRUE(node.IsSequence());

    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->as<int>(), 42);

    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test single element map (boundary condition)
TEST(NodeIteratorTest_186, SingleElementMap_186) {
    YAML::Node node = YAML::Load("{key: value}");
    ASSERT_TRUE(node.IsMap());

    auto it = node.begin();
    EXPECT_NE(it, node.end());
    EXPECT_EQ(it->first.as<std::string>(), "key");
    EXPECT_EQ(it->second.as<std::string>(), "value");

    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test iterator equality
TEST(NodeIteratorTest_186, IteratorEquality_186) {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    auto it1 = node.begin();
    auto it2 = node.begin();

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Test iterator inequality after increment
TEST(NodeIteratorTest_186, IteratorInequalityAfterIncrement_186) {
    YAML::Node node = YAML::Load("[1, 2, 3]");

    auto it1 = node.begin();
    auto it2 = node.begin();
    ++it2;

    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

// Test post-increment on sequence does not skip elements
TEST(NodeIteratorTest_186, PostIncrementSequenceNoSkip_186) {
    YAML::Node node = YAML::Load("[100, 200, 300]");

    std::vector<int> values;
    for (auto it = node.begin(); it != node.end();) {
        auto prev = it++;
        values.push_back(prev->as<int>());
    }

    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], 100);
    EXPECT_EQ(values[1], 200);
    EXPECT_EQ(values[2], 300);
}

// Test post-increment on map does not skip elements
TEST(NodeIteratorTest_186, PostIncrementMapNoSkip_186) {
    YAML::Node node = YAML::Load("{x: 1, y: 2}");

    int count = 0;
    for (auto it = node.begin(); it != node.end();) {
        auto prev = it++;
        // Just verify we can dereference the previous iterator
        EXPECT_FALSE(prev->first.as<std::string>().empty());
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test copy of iterator via post-increment is independent
TEST(NodeIteratorTest_186, PostIncrementCopyIndependence_186) {
    YAML::Node node = YAML::Load("[5, 10, 15]");

    auto it = node.begin();
    auto copy = it++;

    // copy should still point to first element
    EXPECT_EQ(copy->as<int>(), 5);
    // it should point to second element
    EXPECT_EQ(it->as<int>(), 10);

    // Further incrementing copy should not affect it
    ++copy;
    EXPECT_EQ(copy->as<int>(), 10);
    EXPECT_EQ(it->as<int>(), 10);
}

// Test const iteration over sequence
TEST(NodeIteratorTest_186, ConstSequenceIteration_186) {
    const YAML::Node node = YAML::Load("[1, 2, 3]");
    ASSERT_TRUE(node.IsSequence());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 3);
}

// Test const iteration over map
TEST(NodeIteratorTest_186, ConstMapIteration_186) {
    const YAML::Node node = YAML::Load("{a: 1, b: 2}");
    ASSERT_TRUE(node.IsMap());

    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test dereferencing sequence iterator values
TEST(NodeIteratorTest_186, SequenceIteratorDereferenceValues_186) {
    YAML::Node node = YAML::Load("[hello, world]");

    auto it = node.begin();
    EXPECT_EQ(it->as<std::string>(), "hello");
    ++it;
    EXPECT_EQ(it->as<std::string>(), "world");
    ++it;
    EXPECT_TRUE(it == node.end());
}

// Test dereferencing map iterator key-value pairs
TEST(NodeIteratorTest_186, MapIteratorDereferenceKeyValue_186) {
    YAML::Node node = YAML::Load("{name: test}");

    auto it = node.begin();
    EXPECT_EQ(it->first.as<std::string>(), "name");
    EXPECT_EQ(it->second.as<std::string>(), "test");
}

// Test large sequence iteration
TEST(NodeIteratorTest_186, LargeSequenceIteration_186) {
    std::string yaml = "[";
    for (int i = 0; i < 1000; i++) {
        if (i > 0) yaml += ", ";
        yaml += std::to_string(i);
    }
    yaml += "]";

    YAML::Node node = YAML::Load(yaml);
    ASSERT_TRUE(node.IsSequence());

    int count = 0;
    int sum = 0;
    for (auto it = node.begin(); it != node.end(); it++) {
        sum += it->as<int>();
        count++;
    }
    EXPECT_EQ(count, 1000);
    EXPECT_EQ(sum, 999 * 1000 / 2);
}
