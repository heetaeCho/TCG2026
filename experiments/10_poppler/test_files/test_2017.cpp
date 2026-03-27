#include <gtest/gtest.h>

#include "Object.h"

#include "Dict.h"

#include "Annot.h"



using namespace std;



// Mock class for Dict if needed (though not used in this case)

class MockDict : public Dict {

public:

    using Dict::Dict;

    MOCK_METHOD(const Object&, lookup, (std::string_view key, int recursion), (const, override));

};



TEST(parseAnnotExternalData_2017, SubtypeMarkup3D_2017) {

    Dict dict;

    Object subtype("Markup3D");

    dict.add("Subtype", std::move(subtype));



    AnnotExternalDataType result = parseAnnotExternalData(&dict);

    EXPECT_EQ(result, annotExternalDataMarkup3D);

}



TEST(parseAnnotExternalData_2017, SubtypeUnknown_2017) {

    Dict dict;

    Object subtype("Unknown");

    dict.add("Subtype", std::move(subtype));



    AnnotExternalDataType result = parseAnnotExternalData(&dict);

    EXPECT_EQ(result, annotExternalDataMarkupUnknown);

}



TEST(parseAnnotExternalData_2017, NoSubtype_2017) {

    Dict dict;



    AnnotExternalDataType result = parseAnnotExternalData(&dict);

    EXPECT_EQ(result, annotExternalDataMarkupUnknown);

}



TEST(parseAnnotExternalData_2017, SubtypeNotName_2017) {

    Dict dict;

    Object subtype(42); // Integer instead of name

    dict.add("Subtype", std::move(subtype));



    AnnotExternalDataType result = parseAnnotExternalData(&dict);

    EXPECT_EQ(result, annotExternalDataMarkupUnknown);

}



TEST(parseAnnotExternalData_2017, EmptyDict_2017) {

    Dict dict;



    AnnotExternalDataType result = parseAnnotExternalData(&dict);

    EXPECT_EQ(result, annotExternalDataMarkupUnknown);

}
