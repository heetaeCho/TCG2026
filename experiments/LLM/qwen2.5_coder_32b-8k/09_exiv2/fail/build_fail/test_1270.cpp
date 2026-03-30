#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/properties.hpp"

#include "exiv2/types.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class XmpPropertyInfoTest : public ::testing::Test {

protected:

    std::string name_ = "testName";

    std::string title_ = "testTitle";

    const char* xmpValueType_ = "XmpText";

    TypeId typeId_ = static_cast<TypeId>(1);

    XmpCategory xmpCategory_ = xmpInternal;

    std::string desc_ = "testDescription";



    XmpPropertyInfo propertyInfo;



    void SetUp() override {

        propertyInfo.name_ = name_.c_str();

        propertyInfo.title_ = title_.c_str();

        propertyInfo.xmpValueType_ = xmpValueType_;

        propertyInfo.typeId_ = typeId_;

        propertyInfo.xmpCategory_ = xmpCategory_;

        propertyInfo.desc_ = desc_.c_str();

    }

};



TEST_F(XmpPropertyInfoTest_1270, OperatorEqual_ReturnsTrueForSameName_1270) {

    EXPECT_TRUE(propertyInfo == name_);

}



TEST_F(XmpPropertyInfoTest_1270, OperatorEqual_ReturnsFalseForDifferentName_1270) {

    EXPECT_FALSE(propertyInfo == "differentName");

}



TEST_F(XmpPropertyInfoTest_1270, StreamOperator_OutputContainsAllFields_1270) {

    std::ostringstream oss;

    oss << propertyInfo;



    std::string expectedOutput = fmt::format("{},{},{},{},{},\"{}\"\n",

                                             name_,

                                             title_,

                                             xmpValueType_,

                                             TypeInfo::typeName(typeId_),

                                             (xmpCategory_ == xmpExternal ? "External" : "Internal"),

                                             desc_);

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(XmpPropertyInfoTest_1270, StreamOperator_OutputEscapesDoubleQuotesInDescription_1270) {

    propertyInfo.desc_ = "test\"description\"";

    std::ostringstream oss;

    oss << propertyInfo;



    std::string expectedOutput = fmt::format("{},{},{},{},{},\"test\"\"description\"\"\n",

                                             name_,

                                             title_,

                                             xmpValueType_,

                                             TypeInfo::typeName(typeId_),

                                             (xmpCategory_ == xmpExternal ? "External" : "Internal"));

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(XmpPropertyInfoTest_1270, StreamOperator_OutputHandlesEmptyDescription_1270) {

    propertyInfo.desc_ = "";

    std::ostringstream oss;

    oss << propertyInfo;



    std::string expectedOutput = fmt::format("{},{},{},{},{},\"\"\n",

                                             name_,

                                             title_,

                                             xmpValueType_,

                                             TypeInfo::typeName(typeId_),

                                             (xmpCategory_ == xmpExternal ? "External" : "Internal"));

    EXPECT_EQ(oss.str(), expectedOutput);

}



TEST_F(XmpPropertyInfoTest_1270, StreamOperator_OutputHandlesLongDescription_1270) {

    propertyInfo.desc_ = "This is a very long description that should be handled correctly by the stream operator.";

    std::ostringstream oss;

    oss << propertyInfo;



    std::string expectedOutput = fmt::format("{},{},{},{},{},\"{}\"\n",

                                             name_,

                                             title_,

                                             xmpValueType_,

                                             TypeInfo::typeName(typeId_),

                                             (xmpCategory_ == xmpExternal ? "External" : "Internal"),

                                             propertyInfo.desc_);

    EXPECT_EQ(oss.str(), expectedOutput);

}
