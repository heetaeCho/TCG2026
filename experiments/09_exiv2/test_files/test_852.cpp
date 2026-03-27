#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {

    class LangAltValueTest_852 : public ::testing::Test {

    protected:

        LangAltValue value;

    };



    TEST_F(LangAltValueTest_852, ReadValidInput_852) {

        std::string input = "lang=en Hello";

        int result = value.read(input);

        EXPECT_EQ(result, 0);

    }



    TEST_F(LangAltValueTest_852, ReadEmptyLang_852) {

        std::string input = "lang= Hello";

        EXPECT_THROW(value.read(input), Error);

    }



    TEST_F(LangAltValueTest_852, ReadInvalidLangChars_852) {

        std::string input = "lang=en-123 Hello";

        int result = value.read(input);

        EXPECT_EQ(result, 0);

    }



    TEST_F(LangAltValueTest_852, ReadQuotedLang_852) {

        std::string input = "lang=\"en\" Hello";

        int result = value.read(input);

        EXPECT_EQ(result, 0);

    }



    TEST_F(LangAltValueTest_852, ReadMissingQuote_852) {

        std::string input = "lang=\"en Hello";

        EXPECT_THROW(value.read(input), Error);

    }



    TEST_F(LangAltValueTest_852, ReadNoLangPrefix_852) {

        std::string input = "Hello";

        int result = value.read(input);

        EXPECT_EQ(result, 0);

    }



    TEST_F(LangAltValueTest_852, ReadInvalidLangWithDash_852) {

        std::string input = "lang=en- Hello";

        EXPECT_THROW(value.read(input), Error);

    }



    TEST_F(LangAltValueTest_852, ReadEmptyBuffer_852) {

        std::string input = "";

        EXPECT_THROW(value.read(input), Error);

    }

}
