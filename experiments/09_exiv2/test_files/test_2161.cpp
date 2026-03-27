#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"

#include "exiv2/datasets.hpp"



namespace {



using namespace Exiv2;



class IptcdatumTest : public ::testing::Test {

protected:

    IptcdatumTest() 

        : key("Iptc.Application2.Caption"),

          value(Value::create(string)),

          iptcDatum(key, value.get()) {}



    void SetUp() override {

        // Setup code if needed

    }



    IptcKey key;

    std::unique_ptr<Value> value;

    Iptcdatum iptcDatum;

};



TEST_F(IptcdatumTest_2161, ConstructorWithKeyValue_2161) {

    EXPECT_EQ(iptcDatum.key(), "Iptc.Application2.Caption");

}



TEST_F(IptcdatumTest_2161, CopyConstructorDeepCopy_2161) {

    Iptcdatum copiedDatum(iptcDatum);

    EXPECT_EQ(copiedDatum.key(), iptcDatum.key());

    // Assuming key and value are distinct objects after copy

    EXPECT_NE(&copiedDatum.key(), &iptcDatum.key());

}



TEST_F(IptcdatumTest_2161, AssignmentOperatorDeepCopy_2161) {

    Iptcdatum anotherDatum;

    anotherDatum = iptcDatum;

    EXPECT_EQ(anotherDatum.key(), iptcDatum.key());

    // Assuming key and value are distinct objects after assignment

    EXPECT_NE(&anotherDatum.key(), &iptcDatum.key());

}



TEST_F(IptcdatumTest_2161, SetValueString_2161) {

    std::string newValue = "New Caption";

    int result = iptcDatum.setValue(newValue);

    EXPECT_EQ(result, 0); // Assuming successful setValue returns 0

    EXPECT_EQ(iptcDatum.toString(), newValue);

}



TEST_F(IptcdatumTest_2161, SetValueStringValue_2161) {

    std::string newValue = "Another Caption";

    iptcDatum.setValue(newValue.c_str());

    EXPECT_EQ(iptcDatum.toString(), newValue);

}



TEST_F(IptcdatumTest_2161, ToString_ReturnsValueString_2161) {

    std::string expected = "Initial Value"; // Assuming initial value is set to this

    EXPECT_EQ(iptcDatum.toString(), expected);

}



TEST_F(IptcdatumTest_2161, TypeIdCorrect_2161) {

    EXPECT_EQ(iptcDatum.typeId(), string); // Assuming string type is used for Iptc.Application2.Caption

}



TEST_F(IptcdatumTest_2161, TypeNameCorrect_2161) {

    EXPECT_STREQ(iptcDatum.typeName(), "String");

}



}  // namespace
