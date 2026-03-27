#include <gtest/gtest.h>

#include "catch2/internal/catch_tag_alias_registry.hpp"

#include "catch2/internal/catch_source_line_info.hpp"



using namespace Catch;



class TagAliasRegistryTest : public ::testing::Test {

protected:

    TagAliasRegistry registry;

    SourceLineInfo lineInfo{"test_file.cpp", 42};

};



TEST_F(TagAliasRegistryTest_NormalOperation_677, AddValidAlias_677) {

    EXPECT_NO_THROW(registry.add("[@valid]", "tag1", lineInfo));

}



TEST_F(TagAliasRegistryTest_BoundaryConditions_677, EmptyAlias_677) {

    EXPECT_THROW(registry.add("", "tag1", lineInfo), std::runtime_error);

}



TEST_F(TagAliasRegistryTest_BoundaryConditions_677, InvalidFormatAlias_677) {

    EXPECT_THROW(registry.add("@invalid]", "tag1", lineInfo), std::runtime_error);

    EXPECT_THROW(registry.add("[@invalid", "tag1", lineInfo), std::runtime_error);

}



TEST_F(TagAliasRegistryTest_ExceptionalCases_677, DuplicateAlias_677) {

    registry.add("[@duplicate]", "tag1", lineInfo);

    EXPECT_THROW(registry.add("[@duplicate]", "tag2", lineInfo), std::runtime_error);

}
