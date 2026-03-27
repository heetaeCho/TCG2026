#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"

#include "yaml-cpp/mark.h"



using namespace YAML;



namespace {



class TypedKeyNotFoundTest_90 : public ::testing::Test {

protected:

    Mark mark;

    std::string key;



    void SetUp() override {

        mark = Mark(1, 2, 3);

        key = "test_key";

    }

};



TEST_F(TypedKeyNotFoundTest_90, ConstructorInitializesMembers_90) {

    TypedKeyNotFound<std::string> exception = MakeTypedKeyNotFound(mark, key);



    EXPECT_EQ(exception.mark.pos, mark.pos);

    EXPECT_EQ(exception.mark.line, mark.line);

    EXPECT_EQ(exception.mark.column, mark.column);

    EXPECT_EQ(exception.key, key);

}



TEST_F(TypedKeyNotFoundTest_90, NullMarkConstructorInitializesMembers_90) {

    Mark null_mark = Mark::null_mark();

    std::string null_key = "null_key";

    TypedKeyNotFound<std::string> exception = MakeTypedKeyNotFound(null_mark, null_key);



    EXPECT_TRUE(exception.mark.is_null());

    EXPECT_EQ(exception.key, null_key);

}



TEST_F(TypedKeyNotFoundTest_90, ExceptionWhatMessage_90) {

    TypedKeyNotFound<std::string> exception = MakeTypedKeyNotFound(mark, key);



    std::string expected_message = "YAML: key not found: test_key";

    EXPECT_EQ(exception.what(), expected_message);

}



TEST_F(TypedKeyNotFoundTest_90, ExceptionWithNullMarkWhatMessage_90) {

    Mark null_mark = Mark::null_mark();

    std::string null_key = "null_key";

    TypedKeyNotFound<std::string> exception = MakeTypedKeyNotFound(null_mark, null_key);



    std::string expected_message = "YAML: key not found: null_key";

    EXPECT_EQ(exception.what(), expected_message);

}



} // namespace
