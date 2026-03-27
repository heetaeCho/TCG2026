#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emittermanip.h"

#include <string>



using namespace YAML;

using namespace testing;



TEST(LocalTagTest_16, ValidContent_ReturnsPrimaryHandle_16) {

    std::string content = "example";

    _Tag tag = LocalTag(content);

    EXPECT_EQ(tag.first, "");

    EXPECT_EQ(tag.second, content);

    EXPECT_EQ(static_cast<int>(tag.third), static_cast<int>(_Tag::Type::PrimaryHandle));

}



TEST(LocalTagTest_16, EmptyContent_ReturnsEmptyString_16) {

    std::string content = "";

    _Tag tag = LocalTag(content);

    EXPECT_EQ(tag.first, "");

    EXPECT_EQ(tag.second, content);

    EXPECT_EQ(static_cast<int>(tag.third), static_cast<int>(_Tag::Type::PrimaryHandle));

}



TEST(LocalTagTest_16, LargeContent_ReturnsLargeString_16) {

    std::string large_content(1024, 'a');

    _Tag tag = LocalTag(large_content);

    EXPECT_EQ(tag.first, "");

    EXPECT_EQ(tag.second, large_content);

    EXPECT_EQ(static_cast<int>(tag.third), static_cast<int>(_Tag::Type::PrimaryHandle));

}
