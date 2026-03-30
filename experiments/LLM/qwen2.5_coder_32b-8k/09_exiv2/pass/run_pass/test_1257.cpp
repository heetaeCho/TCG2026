#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/properties.hpp"



using namespace Exiv2;

using ::testing::HasSubstr;



class XmpPropertiesTest_1257 : public ::testing::Test {

protected:

    XmpProperties xmpProperties;

};



TEST_F(XmpPropertiesTest_1257, PrintProperties_NoPrefixGiven_PrintsAll_1257) {

    std::ostringstream os;

    xmpProperties.printProperties(os, "");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(XmpPropertiesTest_1257, PrintProperties_ValidPrefixGiven_PrintsFiltered_1257) {

    std::ostringstream os;

    xmpProperties.printProperties(os, "somePrefix");

    EXPECT_TRUE(os.str().empty() || os.str().find("somePrefix") != std::string::npos);

}



TEST_F(XmpPropertiesTest_1257, PrintProperties_EmptyPrefixGiven_PrintsAll_1257) {

    std::ostringstream os;

    xmpProperties.printProperties(os, "");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(XmpPropertiesTest_1257, PrintProperties_NonExistentPrefixGiven_NoOutput_1257) {

    std::ostringstream os;

    xmpProperties.printProperties(os, "nonexistent");

    EXPECT_TRUE(os.str().empty());

}
