#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <map>
#include <string>

// Test encoding an empty map
TEST(MapEncodeTest_607, EmptyMap_607) {
    std::map<std::string, std::string> emptyMap;
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(emptyMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

// Test encoding a map with a single element
TEST(MapEncodeTest_607, SingleElementMap_607) {
    std::map<std::string, std::string> singleMap;
    singleMap["key1"] = "value1";
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(singleMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node["key1"].as<std::string>(), "value1");
}

// Test encoding a map with multiple elements
TEST(MapEncodeTest_607, MultipleElementsMap_607) {
    std::map<std::string, std::string> multiMap;
    multiMap["alpha"] = "a";
    multiMap["beta"] = "b";
    multiMap["gamma"] = "c";
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(multiMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["alpha"].as<std::string>(), "a");
    EXPECT_EQ(node["beta"].as<std::string>(), "b");
    EXPECT_EQ(node["gamma"].as<std::string>(), "c");
}

// Test encoding a map with integer keys and values
TEST(MapEncodeTest_607, IntKeyIntValueMap_607) {
    std::map<int, int> intMap;
    intMap[1] = 100;
    intMap[2] = 200;
    intMap[3] = 300;
    YAML::Node node = YAML::convert<std::map<int, int>>::encode(intMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["1"].as<int>(), 100);
    EXPECT_EQ(node["2"].as<int>(), 200);
    EXPECT_EQ(node["3"].as<int>(), 300);
}

// Test encoding a map with string keys and integer values
TEST(MapEncodeTest_607, StringKeyIntValueMap_607) {
    std::map<std::string, int> mixedMap;
    mixedMap["one"] = 1;
    mixedMap["two"] = 2;
    YAML::Node node = YAML::convert<std::map<std::string, int>>::encode(mixedMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["one"].as<int>(), 1);
    EXPECT_EQ(node["two"].as<int>(), 2);
}

// Test that the resulting node type is Map
TEST(MapEncodeTest_607, NodeTypeIsMap_607) {
    std::map<std::string, std::string> m;
    m["x"] = "y";
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(m);
    EXPECT_EQ(node.Type(), YAML::NodeType::Map);
}

// Test encoding a map with empty string keys and values
TEST(MapEncodeTest_607, EmptyStringKeysAndValues_607) {
    std::map<std::string, std::string> m;
    m[""] = "";
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 1u);
    EXPECT_EQ(node[""].as<std::string>(), "");
}

// Test encoding a map with large number of elements
TEST(MapEncodeTest_607, LargeMap_607) {
    std::map<int, int> largeMap;
    const int N = 1000;
    for (int i = 0; i < N; ++i) {
        largeMap[i] = i * 2;
    }
    YAML::Node node = YAML::convert<std::map<int, int>>::encode(largeMap);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), static_cast<std::size_t>(N));
}

// Test encoding preserves all key-value pairs (iteration check)
TEST(MapEncodeTest_607, AllKeysPreserved_607) {
    std::map<std::string, std::string> m;
    m["a"] = "1";
    m["b"] = "2";
    m["c"] = "3";
    m["d"] = "4";
    m["e"] = "5";
    YAML::Node node = YAML::convert<std::map<std::string, std::string>>::encode(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 5u);
    for (const auto& kv : m) {
        EXPECT_TRUE(node[kv.first].IsDefined());
        EXPECT_EQ(node[kv.first].as<std::string>(), kv.second);
    }
}

// Test encoding a map with double values
TEST(MapEncodeTest_607, StringKeyDoubleValueMap_607) {
    std::map<std::string, double> m;
    m["pi"] = 3.14159;
    m["e"] = 2.71828;
    YAML::Node node = YAML::convert<std::map<std::string, double>>::encode(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_NEAR(node["pi"].as<double>(), 3.14159, 1e-4);
    EXPECT_NEAR(node["e"].as<double>(), 2.71828, 1e-4);
}

// Test encoding a map with boolean values
TEST(MapEncodeTest_607, StringKeyBoolValueMap_607) {
    std::map<std::string, bool> m;
    m["flag_true"] = true;
    m["flag_false"] = false;
    YAML::Node node = YAML::convert<std::map<std::string, bool>>::encode(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node["flag_true"].as<bool>(), true);
    EXPECT_EQ(node["flag_false"].as<bool>(), false);
}

// Test that encode returns a new independent Node
TEST(MapEncodeTest_607, EncodeReturnsIndependentNode_607) {
    std::map<std::string, std::string> m;
    m["key"] = "value";
    YAML::Node node1 = YAML::convert<std::map<std::string, std::string>>::encode(m);
    YAML::Node node2 = YAML::convert<std::map<std::string, std::string>>::encode(m);
    // Both should have the same content
    EXPECT_EQ(node1.size(), node2.size());
    EXPECT_EQ(node1["key"].as<std::string>(), node2["key"].as<std::string>());
}

// Test encoding a map with custom comparator (std::greater)
TEST(MapEncodeTest_607, CustomComparatorMap_607) {
    std::map<std::string, std::string, std::greater<std::string>> m;
    m["z"] = "last";
    m["a"] = "first";
    m["m"] = "middle";
    YAML::Node node = YAML::convert<std::map<std::string, std::string, std::greater<std::string>>>::encode(m);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node["z"].as<std::string>(), "last");
    EXPECT_EQ(node["a"].as<std::string>(), "first");
    EXPECT_EQ(node["m"].as<std::string>(), "middle");
}

// Test that node can be iterated and all pairs match
TEST(MapEncodeTest_607, IterateEncodedMap_607) {
    std::map<std::string, int> m;
    m["x"] = 10;
    m["y"] = 20;
    YAML::Node node = YAML::convert<std::map<std::string, int>>::encode(m);
    
    int count = 0;
    for (auto it = node.begin(); it != node.end(); ++it) {
        std::string key = it->first.as<std::string>();
        int value = it->second.as<int>();
        EXPECT_TRUE(m.find(key) != m.end());
        EXPECT_EQ(m[key], value);
        ++count;
    }
    EXPECT_EQ(count, 2);
}
