#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Ref;



class LangAltValueTest_855 : public ::testing::Test {

protected:

    LangAltValue value;

};



TEST_F(LangAltValueTest_855, WriteWithDefaultLanguage_855) {

    std::ostringstream os;

    value.read("lang=\"x-default\" English");

    value.write(os);

    EXPECT_EQ(os.str(), "lang=\"x-default\" English");

}



TEST_F(LangAltValueTest_855, WriteMultipleLanguages_855) {

    std::ostringstream os;

    value.read("lang=\"en\" English, lang=\"fr\" Francais, lang=\"x-default\" Default");

    value.write(os);

    EXPECT_EQ(os.str(), "lang=\"x-default\" Default, lang=\"en\" English, lang=\"fr\" Francais");

}



TEST_F(LangAltValueTest_855, WriteNoLanguages_855) {

    std::ostringstream os;

    value.read("");

    value.write(os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(LangAltValueTest_855, WriteOnlyDefaultLanguage_855) {

    std::ostringstream os;

    value.read("lang=\"x-default\" Default");

    value.write(os);

    EXPECT_EQ(os.str(), "lang=\"x-default\" Default");

}



TEST_F(LangAltValueTest_855, WriteSingleNonDefaultLanguage_855) {

    std::ostringstream os;

    value.read("lang=\"en\" English");

    value.write(os);

    EXPECT_EQ(os.str(), "lang=\"en\" English");

}
