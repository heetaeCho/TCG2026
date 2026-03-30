#include <gtest/gtest.h>

#include "catch2/internal/catch_tag_alias_registry.hpp"

#include <map>



using namespace Catch;



class TagAliasRegistryTest_675 : public ::testing::Test {

protected:

    TagAliasRegistry registry;

};



TEST_F(TagAliasRegistryTest_675, FindExistingAlias_675) {

    SourceLineInfo lineInfo("file.cpp", 10);

    TagAlias tagAlias{"tag"};

    registry.add("alias", "tag", lineInfo);



    const TagAlias* result = registry.find("alias");

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->m_tag, "tag");

}



TEST_F(TagAliasRegistryTest_675, FindNonExistingAlias_675) {

    const TagAlias* result = registry.find("non_existing_alias");

    EXPECT_EQ(result, nullptr);

}



TEST_F(TagAliasRegistryTest_675, AddMultipleAliases_675) {

    SourceLineInfo lineInfo1("file.cpp", 10);

    SourceLineInfo lineInfo2("file.cpp", 20);



    registry.add("alias1", "tag1", lineInfo1);

    registry.add("alias2", "tag2", lineInfo2);



    const TagAlias* result1 = registry.find("alias1");

    ASSERT_NE(result1, nullptr);

    EXPECT_EQ(result1->m_tag, "tag1");



    const TagAlias* result2 = registry.find("alias2");

    ASSERT_NE(result2, nullptr);

    EXPECT_EQ(result2->m_tag, "tag2");

}



TEST_F(TagAliasRegistryTest_675, BoundaryConditionEmptyAlias_675) {

    SourceLineInfo lineInfo("file.cpp", 10);



    registry.add("", "tag", lineInfo);

    const TagAlias* result = registry.find("");

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->m_tag, "tag");

}



TEST_F(TagAliasRegistryTest_675, BoundaryConditionEmptyTag_675) {

    SourceLineInfo lineInfo("file.cpp", 10);



    registry.add("alias", "", lineInfo);

    const TagAlias* result = registry.find("alias");

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->m_tag, "");

}



// Assuming expandAliases can be tested independently if it's part of the public interface

TEST_F(TagAliasRegistryTest_675, ExpandAliasesWithNoAliases_675) {

    std::string result = registry.expandAliases("test_spec");

    EXPECT_EQ(result, "test_spec");

}



TEST_F(TagAliasRegistryTest_675, ExpandAliasesWithExistingAlias_675) {

    SourceLineInfo lineInfo("file.cpp", 10);



    registry.add("alias", "tag", lineInfo);

    std::string result = registry.expandAliases("[alias]");

    EXPECT_EQ(result, "[tag]");

}
