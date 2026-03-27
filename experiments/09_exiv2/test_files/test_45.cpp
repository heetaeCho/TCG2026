#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"



using namespace Exiv2;

using namespace testing;



class IptcDataTest_45 : public Test {

protected:

    IptcData iptcData;

};



TEST_F(IptcDataTest_45, SizeInitiallyZero_45) {

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_45, EmptyInitiallyTrue_45) {

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_45, AddIncreasesSize_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    iptcData.add(key, new StringValue(value));

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_45, AddTwiceIncreasesSizeByTwo_45) {

    IptcKey key1("Iptc.Application2.Caption");

    std::string value1 = "Sample caption";

    iptcData.add(key1, new StringValue(value1));



    IptcKey key2("Iptc.Application2.Byline");

    std::string value2 = "Author name";

    iptcData.add(key2, new StringValue(value2));



    EXPECT_EQ(iptcData.size(), 2);

}



TEST_F(IptcDataTest_45, ClearResetsSizeToZero_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    iptcData.add(key, new StringValue(value));

    iptcData.clear();

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_45, ClearResetsEmptyToTrue_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    iptcData.add(key, new StringValue(value));

    iptcData.clear();

    EXPECT_TRUE(iptcData.empty());

}



TEST_F(IptcDataTest_45, FindKeyFindsAddedKey_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    iptcData.add(key, new StringValue(value));



    auto it = iptcData.findKey(key);

    EXPECT_NE(it, iptcData.end());

}



TEST_F(IptcDataTest_45, FindKeyNotFoundReturnsEnd_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    iptcData.add(key, new StringValue(value));



    IptcKey nonExistentKey("Iptc.Application2.Byline");

    auto it = iptcData.findKey(nonExistentKey);

    EXPECT_EQ(it, iptcData.end());

}



TEST_F(IptcDataTest_45, EraseReducesSize_45) {

    IptcKey key("Iptc.Application2.Caption");

    std::string value = "Sample caption";

    auto pos = iptcData.add(key, new StringValue(value));



    iptcData.erase(iptcData.begin());

    EXPECT_EQ(iptcData.size(), 0);

}



TEST_F(IptcDataTest_45, SortByKeyDoesNotChangeSize_45) {

    IptcKey key1("Iptc.Application2.Caption");

    std::string value1 = "Sample caption";

    iptcData.add(key1, new StringValue(value1));



    IptcKey key2("Iptc.Application2.Byline");

    std::string value2 = "Author name";

    iptcData.add(key2, new StringValue(value2));



    size_t initialSize = iptcData.size();

    iptcData.sortByKey();

    EXPECT_EQ(iptcData.size(), initialSize);

}



TEST_F(IptcDataTest_45, SortByTagDoesNotChangeSize_45) {

    IptcKey key1("Iptc.Application2.Caption");

    std::string value1 = "Sample caption";

    iptcData.add(key1, new StringValue(value1));



    IptcKey key2("Iptc.Application2.Byline");

    std::string value2 = "Author name";

    iptcData.add(key2, new StringValue(value2));



    size_t initialSize = iptcData.size();

    iptcData.sortByTag();

    EXPECT_EQ(iptcData.size(), initialSize);

}



TEST_F(IptcDataTest_45, OperatorBracketAddsNewKey_45) {

    std::string key("Iptc.Application2.Caption");

    iptcData[key] = Iptcdatum(key, 0x10, 0x78, new StringValue("Sample caption"));

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_45, OperatorBracketOverwritesExistingKey_45) {

    std::string key("Iptc.Application2.Caption");

    iptcData[key] = Iptcdatum(key, 0x10, 0x78, new StringValue("Sample caption"));

    EXPECT_EQ(iptcData.size(), 1);



    iptcData[key] = Iptcdatum(key, 0x10, 0x78, new StringValue("Updated caption"));

    EXPECT_EQ(iptcData.size(), 1);

}



TEST_F(IptcDataTest_45, DetectCharsetReturnsNonEmptyString_45) {

    const char* charset = iptcData.detectCharset();

    EXPECT_STRNE(charset, "");

}
