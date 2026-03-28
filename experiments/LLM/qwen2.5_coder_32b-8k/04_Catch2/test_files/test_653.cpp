#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



namespace Catch { namespace Clara { namespace Detail {



using ::testing::Eq;

using ::testing::_;



class ConvertIntoTest : public ::testing::Test {

protected:

    std::string source;

    std::string target;



    void SetUp() override {

        source = "test_source";

        target.clear();

    }

};



TEST_F(ConvertIntoTest_NormalOperation_653, SourceCopiedToTarget_653) {

    auto result = convertInto(source, target);

    EXPECT_EQ(target, source);

}



TEST_F(ConvertIntoTest_NormalOperation_653, ReturnsOkResult_653) {

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(ConvertIntoTest_BoundaryConditions_653, EmptySourceString_653) {

    source.clear();

    auto result = convertInto(source, target);

    EXPECT_EQ(target, "");

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



TEST_F(ConvertIntoTest_BoundaryConditions_653, LargeSourceString_653) {

    source.append(1024 * 1024, 'a'); // 1MB large string

    auto result = convertInto(source, target);

    EXPECT_EQ(target, source);

    EXPECT_TRUE(static_cast<bool>(result));

    EXPECT_EQ(result.type(), ParseResultType::Matched);

}



}}}
