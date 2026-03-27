#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



namespace YAML {

    struct _Tag {

        enum class Type { NamedHandle };

        std::string prefix;

        std::string content;

        Type type;



        _Tag(std::string p, std::string c, Type t) : prefix(p), content(c), type(t) {}

    };



    inline _Tag LocalTag(const std::string& prefix, const std::string content) { 

        return _Tag(prefix, content, _Tag::Type::NamedHandle); 

    }

}



TEST(LocalTagTest_17, NormalOperationWithNonEmptyStrings_17) {

    auto tag = YAML::LocalTag("example", "content");

    EXPECT_EQ(tag.prefix, "example");

    EXPECT_EQ(tag.content, "content");

    EXPECT_EQ(tag.type, YAML::_Tag::Type::NamedHandle);

}



TEST(LocalTagTest_17, NormalOperationWithEmptyPrefix_17) {

    auto tag = YAML::LocalTag("", "content");

    EXPECT_EQ(tag.prefix, "");

    EXPECT_EQ(tag.content, "content");

    EXPECT_EQ(tag.type, YAML::_Tag::Type::NamedHandle);

}



TEST(LocalTagTest_17, NormalOperationWithEmptyContent_17) {

    auto tag = YAML::LocalTag("example", "");

    EXPECT_EQ(tag.prefix, "example");

    EXPECT_EQ(tag.content, "");

    EXPECT_EQ(tag.type, YAML::_Tag::Type::NamedHandle);

}



TEST(LocalTagTest_17, NormalOperationWithBothEmptyStrings_17) {

    auto tag = YAML::LocalTag("", "");

    EXPECT_EQ(tag.prefix, "");

    EXPECT_EQ(tag.content, "");

    EXPECT_EQ(tag.type, YAML::_Tag::Type::NamedHandle);

}
