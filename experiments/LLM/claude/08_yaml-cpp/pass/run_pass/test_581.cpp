#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include <cstdio>
#include "yaml-cpp/yaml.h"

class LoadFileTest_581 : public ::testing::Test {
protected:
    std::string temp_filename_;

    void SetUp() override {
        temp_filename_ = "test_temp_581.yaml";
    }

    void TearDown() override {
        std::remove(temp_filename_.c_str());
    }

    void CreateTempFile(const std::string& content) {
        std::ofstream fout(temp_filename_);
        ASSERT_TRUE(fout.is_open());
        fout << content;
        fout.close();
    }
};

TEST_F(LoadFileTest_581, ThrowsBadFileForNonExistentFile_581) {
    EXPECT_THROW(YAML::LoadFile("nonexistent_file_581.yaml"), YAML::BadFile);
}

TEST_F(LoadFileTest_581, ThrowsBadFileForEmptyFilename_581) {
    EXPECT_THROW(YAML::LoadFile(""), YAML::BadFile);
}

TEST_F(LoadFileTest_581, LoadsSimpleScalar_581) {
    CreateTempFile("hello");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(LoadFileTest_581, LoadsSimpleMap_581) {
    CreateTempFile("key: value\nname: test");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
    EXPECT_EQ(node["name"].as<std::string>(), "test");
}

TEST_F(LoadFileTest_581, LoadsSimpleSequence_581) {
    CreateTempFile("- item1\n- item2\n- item3");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "item1");
    EXPECT_EQ(node[1].as<std::string>(), "item2");
    EXPECT_EQ(node[2].as<std::string>(), "item3");
}

TEST_F(LoadFileTest_581, LoadsEmptyFile_581) {
    CreateTempFile("");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsNull());
}

TEST_F(LoadFileTest_581, LoadsNestedMap_581) {
    CreateTempFile("outer:\n  inner: value");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsMap());
    EXPECT_TRUE(node["outer"].IsMap());
    EXPECT_EQ(node["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(LoadFileTest_581, LoadsIntegerValues_581) {
    CreateTempFile("count: 42");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_EQ(node["count"].as<int>(), 42);
}

TEST_F(LoadFileTest_581, LoadsBooleanValues_581) {
    CreateTempFile("flag: true");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_EQ(node["flag"].as<bool>(), true);
}

TEST_F(LoadFileTest_581, LoadsFloatValues_581) {
    CreateTempFile("pi: 3.14");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_NEAR(node["pi"].as<double>(), 3.14, 0.001);
}

TEST_F(LoadFileTest_581, LoadsNullValue_581) {
    CreateTempFile("key: ~");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node["key"].IsNull());
}

TEST_F(LoadFileTest_581, ThrowsBadFileForInvalidPath_581) {
    EXPECT_THROW(YAML::LoadFile("/invalid/path/to/file_581.yaml"), YAML::BadFile);
}

TEST_F(LoadFileTest_581, LoadsSequenceOfMaps_581) {
    CreateTempFile("- name: Alice\n  age: 30\n- name: Bob\n  age: 25");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0]["name"].as<std::string>(), "Alice");
    EXPECT_EQ(node[0]["age"].as<int>(), 30);
    EXPECT_EQ(node[1]["name"].as<std::string>(), "Bob");
    EXPECT_EQ(node[1]["age"].as<int>(), 25);
}

TEST_F(LoadFileTest_581, LoadsMultilineString_581) {
    CreateTempFile("text: |\n  line1\n  line2\n  line3");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    std::string text = node["text"].as<std::string>();
    EXPECT_FALSE(text.empty());
    EXPECT_NE(text.find("line1"), std::string::npos);
    EXPECT_NE(text.find("line2"), std::string::npos);
    EXPECT_NE(text.find("line3"), std::string::npos);
}

TEST_F(LoadFileTest_581, LoadsDocumentWithComments_581) {
    CreateTempFile("# This is a comment\nkey: value\n# Another comment");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key"].as<std::string>(), "value");
}

TEST_F(LoadFileTest_581, LoadsQuotedStrings_581) {
    CreateTempFile("single: 'hello'\ndouble: \"world\"");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_EQ(node["single"].as<std::string>(), "hello");
    EXPECT_EQ(node["double"].as<std::string>(), "world");
}

TEST_F(LoadFileTest_581, LoadsEmptyMap_581) {
    CreateTempFile("{}");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(LoadFileTest_581, LoadsEmptySequence_581) {
    CreateTempFile("[]");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(LoadFileTest_581, LoadsFlowStyleMap_581) {
    CreateTempFile("{key1: val1, key2: val2}");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["key1"].as<std::string>(), "val1");
    EXPECT_EQ(node["key2"].as<std::string>(), "val2");
}

TEST_F(LoadFileTest_581, LoadsFlowStyleSequence_581) {
    CreateTempFile("[a, b, c]");
    YAML::Node node = YAML::LoadFile(temp_filename_);
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<std::string>(), "a");
    EXPECT_EQ(node[1].as<std::string>(), "b");
    EXPECT_EQ(node[2].as<std::string>(), "c");
}
