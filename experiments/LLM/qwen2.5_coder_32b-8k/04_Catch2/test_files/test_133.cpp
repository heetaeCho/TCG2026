#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/matchers/internal/catch_matchers_impl.hpp>

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::StrEq;



class MatchExprTest_133 : public ::testing::Test {

protected:

    template<typename ArgT, typename MatcherT>

    std::string getStreamedExpression(ArgT&& arg, const MatcherT& matcher) {

        std::ostringstream oss;

        MatchExpr<ArgT, MatcherT> matchExpr(std::forward<ArgT>(arg), matcher);

        matchExpr.streamReconstructedExpression(oss);

        return oss.str();

    }

};



TEST_F(MatchExprTest_133, StreamReconstructedExpression_NumericValue_133) {

    int value = 42;

    auto matcher = Matcher::Eq(42); // Assuming a simple equality matcher

    EXPECT_THAT(getStreamedExpression(value, matcher), StrEq("42 == 42"));

}



TEST_F(MatchExprTest_133, StreamReconstructedExpression_StringValue_133) {

    std::string value = "hello";

    auto matcher = Matcher::Contains("hello"); // Assuming a simple contains matcher

    EXPECT_THAT(getStreamedExpression(value, matcher), StrEq("\"hello\" contains \"hello\""));

}



TEST_F(MatchExprTest_133, StreamReconstructedExpression_CharValue_133) {

    char value = 'a';

    auto matcher = Matcher::Eq('a'); // Assuming a simple equality matcher

    EXPECT_THAT(getStreamedExpression(value, matcher), StrEq("'a' == 'a'"));

}



TEST_F(MatchExprTest_133, StreamReconstructedExpression_EmptyString_133) {

    std::string value = "";

    auto matcher = Matcher::Contains(""); // Assuming a simple contains matcher

    EXPECT_THAT(getStreamedExpression(value, matcher), StrEq("\"\" contains \"\""));

}



TEST_F(MatchExprTest_133, StreamReconstructedExpression_ZeroValue_133) {

    int value = 0;

    auto matcher = Matcher::Eq(0); // Assuming a simple equality matcher

    EXPECT_THAT(getStreamedExpression(value, matcher), StrEq("0 == 0"));

}

```


