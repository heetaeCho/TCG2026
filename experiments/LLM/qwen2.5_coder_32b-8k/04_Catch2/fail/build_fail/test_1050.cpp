#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_floating_point.hpp"

#include "catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch::Matchers;



TEST(WithinUlpsMatcherTest_1050, NormalOperation_Double_1050) {

    WithinUlpsMatcher matcher(1.0, 4, Detail::FloatingPointKind::Double);

    EXPECT_TRUE(matcher.match(1.0));

    EXPECT_TRUE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 2));

    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon() * 5));

}



TEST(WithinUlpsMatcherTest_1050, BoundaryConditions_DoubleExactMatch_1050) {

    WithinUlpsMatcher matcher(1.0, 0, Detail::FloatingPointKind::Double);

    EXPECT_TRUE(matcher.match(1.0));

    EXPECT_FALSE(matcher.match(1.0 + std::numeric_limits<double>::epsilon()));

}



TEST(WithinUlpsMatcherTest_1050, BoundaryConditions_DoubleMaxULPs_1050) {

    WithinUlpsMatcher matcher(1.0, std::numeric_limits<uint64_t>::max(), Detail::FloatingPointKind::Double);

    EXPECT_TRUE(matcher.match(1.0));

    EXPECT_TRUE(matcher.match(std::numeric_limits<double>::max()));

}



TEST(WithinUlpsMatcherTest_1050, ExceptionalCase_FloatType_1050) {

#ifdef GTEST_HAS_EXCEPTIONS

    EXPECT_THROW({

        WithinUlpsMatcher matcher(1.0f, std::numeric_limits<uint32_t>::max() + 1, Detail::FloatingPointKind::Float);

    }, Catch::Detail::EnforceException);

#endif

}



TEST(WithinUlpsMatcherTest_1050, ExceptionalCase_NonIEEE754_1050) {

#ifdef GTEST_HAS_EXCEPTIONS

    EXPECT_THROW({

        WithinUlpsMatcher matcher(1.0, 4, Detail::FloatingPointKind::Double);

        std::numeric_limits<double>::is_iec559 = false; // This is a hypothetical scenario for testing purposes.

        matcher.match(1.0);

    }, Catch::Detail::EnforceException);

#endif

}



TEST(WithinUlpsMatcherTest_1050, DescribeMethod_1050) {

    WithinUlpsMatcher matcher(1.0, 4, Detail::FloatingPointKind::Double);

    EXPECT_EQ(matcher.describe(), "is within 4 ulp of 1");

}
