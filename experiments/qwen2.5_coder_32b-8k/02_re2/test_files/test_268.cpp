#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "absl/strings/string_view.h"



namespace re2 { namespace re2_internal {



template <> bool Parse(const char* str, size_t n, absl::string_view* dest);



} } // namespace re2::re2_internal



using namespace ::testing;



class ParseTest_268 : public Test {

protected:

    const char* testString = "test_string";

    size_t testLength = 11;

};



TEST_F(ParseTest_268, NormalOperation_268) {

    absl::string_view dest;

    bool result = re2::re2_internal::Parse(testString, testLength, &dest);

    EXPECT_TRUE(result);

    EXPECT_EQ(dest, absl::string_view(testString, testLength));

}



TEST_F(ParseTest_268, NullDestPointer_268) {

    bool result = re2::re2_internal::Parse(testString, testLength, nullptr);

    EXPECT_TRUE(result);

}



TEST_F(ParseTest_268, EmptyString_268) {

    const char* emptyString = "";

    size_t emptyLength = 0;

    absl::string_view dest;

    bool result = re2::re2_internal::Parse(emptyString, emptyLength, &dest);

    EXPECT_TRUE(result);

    EXPECT_EQ(dest, absl::string_view(emptyString, emptyLength));

}



TEST_F(ParseTest_268, FullLengthOfString_268) {

    absl::string_view dest;

    bool result = re2::re2_internal::Parse(testString, testLength, &dest);

    EXPECT_TRUE(result);

    EXPECT_EQ(dest.size(), testLength);

}
