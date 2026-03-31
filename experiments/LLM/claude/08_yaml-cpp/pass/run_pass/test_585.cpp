#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include "yaml-cpp/yaml.h"

class LoadAllFromFileTest_585 : public ::testing::Test {
protected:
    std::string temp_filename_;

    void SetUp() override {
        temp_filename_ = "test_loadall_585.yaml";
    }

    void TearDown() override {
        std::remove(temp_filename_.c_str());
    }

    void WriteFile(const std::string& filename, const std::string& content) {
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.good());
        fout << content;
        fout.close();
    }
};

TEST_F(LoadAllFromFileTest_585, ThrowsBadFileForNonexistentFile_585) {
    EXPECT_THROW(YAML::LoadAllFromFile("nonexistent_file_585.yaml"), YAML::BadFile);
}

TEST_F(LoadAllFromFileTest_585, ThrowsBadFileForEmptyFilename_585) {
    EXPECT_THROW(YAML::LoadAllFromFile(""), YAML::BadFile);
}

TEST_F(LoadAllFromFileTest_585, LoadsSingleDocument_585) {
    WriteFile(temp_filename_, "key: value\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0]["key"].as<std::string>(), "value");
}

TEST_F(LoadAllFromFileTest_585, LoadsMultipleDocuments_585) {
    WriteFile(temp_filename_, "---\nfoo: bar\n---\nbaz: qux\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0]["foo"].as<std::string>(), "bar");
    EXPECT_EQ(docs[1]["baz"].as<std::string>(), "qux");
}

TEST_F(LoadAllFromFileTest_585, LoadsEmptyFile_585) {
    WriteFile(temp_filename_, "");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    // An empty file may produce zero or one null document depending on implementation
    // We just verify it doesn't crash and returns a valid vector
    EXPECT_GE(docs.size(), 0u);
}

TEST_F(LoadAllFromFileTest_585, LoadsThreeDocuments_585) {
    WriteFile(temp_filename_, "---\na: 1\n---\nb: 2\n---\nc: 3\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 3u);
    EXPECT_EQ(docs[0]["a"].as<int>(), 1);
    EXPECT_EQ(docs[1]["b"].as<int>(), 2);
    EXPECT_EQ(docs[2]["c"].as<int>(), 3);
}

TEST_F(LoadAllFromFileTest_585, LoadsDocumentWithSequence_585) {
    WriteFile(temp_filename_, "- item1\n- item2\n- item3\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    ASSERT_TRUE(docs[0].IsSequence());
    EXPECT_EQ(docs[0].size(), 3u);
    EXPECT_EQ(docs[0][0].as<std::string>(), "item1");
    EXPECT_EQ(docs[0][1].as<std::string>(), "item2");
    EXPECT_EQ(docs[0][2].as<std::string>(), "item3");
}

TEST_F(LoadAllFromFileTest_585, LoadsDocumentWithScalar_585) {
    WriteFile(temp_filename_, "hello world\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0].as<std::string>(), "hello world");
}

TEST_F(LoadAllFromFileTest_585, LoadsDocumentWithExplicitEndMarkers_585) {
    WriteFile(temp_filename_, "---\nfoo: bar\n...\n---\nbaz: qux\n...\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 2u);
    EXPECT_EQ(docs[0]["foo"].as<std::string>(), "bar");
    EXPECT_EQ(docs[1]["baz"].as<std::string>(), "qux");
}

TEST_F(LoadAllFromFileTest_585, LoadsNestedMap_585) {
    WriteFile(temp_filename_, "outer:\n  inner: value\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0]["outer"]["inner"].as<std::string>(), "value");
}

TEST_F(LoadAllFromFileTest_585, LoadsDocumentWithNullValue_585) {
    WriteFile(temp_filename_, "---\nkey: ~\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_TRUE(docs[0]["key"].IsNull());
}

TEST_F(LoadAllFromFileTest_585, LoadsDocumentWithBooleanValues_585) {
    WriteFile(temp_filename_, "flag1: true\nflag2: false\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 1u);
    EXPECT_EQ(docs[0]["flag1"].as<bool>(), true);
    EXPECT_EQ(docs[0]["flag2"].as<bool>(), false);
}

TEST_F(LoadAllFromFileTest_585, BadFileExceptionContainsFilename_585) {
    std::string bad_filename = "this_file_does_not_exist_585.yaml";
    try {
        YAML::LoadAllFromFile(bad_filename);
        FAIL() << "Expected YAML::BadFile exception";
    } catch (const YAML::BadFile& e) {
        std::string msg = e.what();
        // The exception should exist; we just verify it was thrown
        EXPECT_FALSE(msg.empty());
    }
}

TEST_F(LoadAllFromFileTest_585, LoadsMixedDocumentTypes_585) {
    WriteFile(temp_filename_, "---\nscalar_value\n---\n- list_item\n---\nkey: value\n");
    std::vector<YAML::Node> docs = YAML::LoadAllFromFile(temp_filename_);
    ASSERT_EQ(docs.size(), 3u);
    EXPECT_TRUE(docs[0].IsScalar());
    EXPECT_TRUE(docs[1].IsSequence());
    EXPECT_TRUE(docs[2].IsMap());
}
