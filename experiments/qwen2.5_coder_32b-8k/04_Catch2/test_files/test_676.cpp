#include <gtest/gtest.h>

#include "catch2/internal/catch_tag_alias_registry.hpp"



namespace Catch {



class TagAliasRegistryTest_676 : public ::testing::Test {

protected:

    TagAliasRegistry registry;

};



TEST_F(TagAliasRegistryTest_676, ExpandAliases_NoAlias_676) {

    std::string unexpanded = "testcase";

    EXPECT_EQ(registry.expandAliases(unexpanded), unexpanded);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_SingleAlias_676) {

    registry.add("@alias", "[tag]", SourceLineInfo());

    std::string unexpanded = "@aliastest";

    std::string expected = "[tag]test";

    EXPECT_EQ(registry.expandAliases(unexpanded), expected);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_MultipleAliases_676) {

    registry.add("@alias1", "[tag1]", SourceLineInfo());

    registry.add("@alias2", "[tag2]", SourceLineInfo());

    std::string unexpanded = "@alias1test@alias2";

    std::string expected = "[tag1]test[tag2]";

    EXPECT_EQ(registry.expandAliases(unexpanded), expected);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_OverlappingAliases_676) {

    registry.add("@alias", "[tag]", SourceLineInfo());

    registry.add("@aliase", "[longtag]", SourceLineInfo());

    std::string unexpanded = "@aliase";

    std::string expected = "[longtag]";

    EXPECT_EQ(registry.expandAliases(unexpanded), expected);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_NoMatchInMiddle_676) {

    registry.add("@alias", "[tag]", SourceLineInfo());

    std::string unexpanded = "pre@aliastestpost";

    std::string expected = "pre[tag]testpost";

    EXPECT_EQ(registry.expandAliases(unexpanded), expected);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_MultipleOccurrences_676) {

    registry.add("@alias", "[tag]", SourceLineInfo());

    std::string unexpanded = "@aliastest@alias";

    std::string expected = "[tag]test[tag]";

    EXPECT_EQ(registry.expandAliases(unexpanded), expected);

}



TEST_F(TagAliasRegistryTest_676, ExpandAliases_EmptyInput_676) {

    std::string unexpanded = "";

    EXPECT_EQ(registry.expandAliases(unexpanded), "");

}



}  // namespace Catch
