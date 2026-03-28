#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpDataTest_1303 : public ::testing::Test {

protected:

    XmpData xmpData;

    std::unique_ptr<Value> value;

    XmpKey key;



    void SetUp() override {

        value = Value::create(stringType);

        key = XmpKey("Xmp.dc.title");

    }

};



TEST_F(XmpDataTest_1303, AddValidXmpDatum_1303) {

    Xmpdatum xmpDatum(key, value.get());

    int result = xmpData.add(xmpDatum);

    EXPECT_EQ(result, 0); // Assuming 0 indicates success

}



TEST_F(XmpDataTest_1303, AddValidKeyAndValue_1303) {

    int result = xmpData.add(key, value.get());

    EXPECT_EQ(result, 0); // Assuming 0 indicates success

}



TEST_F(XmpDataTest_1303, AddDuplicateKey_1303) {

    xmpData.add(key, value.get());

    int result = xmpData.add(key, value.get());

    EXPECT_NE(result, 0); // Assuming non-zero indicates failure due to duplicate key

}



TEST_F(XmpDataTest_1303, CountAfterAdd_1303) {

    long initialCount = xmpData.count();

    xmpData.add(key, value.get());

    long finalCount = xmpData.count();

    EXPECT_EQ(finalCount, initialCount + 1);

}



TEST_F(XmpDataTest_1303, FindKeyAfterAdd_1303) {

    xmpData.add(key, value.get());

    XmpData::const_iterator it = xmpData.findKey(key);

    EXPECT_NE(it, xmpData.end());

    EXPECT_EQ((*it).key(), key.key());

}



TEST_F(XmpDataTest_1303, ClearEmptiesXmpData_1303) {

    xmpData.add(key, value.get());

    xmpData.clear();

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1303, EmptyInitially_1303) {

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1303, SortByKeyPreservesCount_1303) {

    long initialCount = xmpData.count();

    xmpData.add(key, value.get());

    xmpData.sortByKey();

    long finalCount = xmpData.count();

    EXPECT_EQ(finalCount, initialCount + 1);

}



TEST_F(XmpDataTest_1303, EraseKeyReducesCount_1303) {

    xmpData.add(key, value.get());

    long initialCount = xmpData.count();

    XmpData::iterator it = xmpData.findKey(key);

    if (it != xmpData.end()) {

        xmpData.erase(it);

    }

    long finalCount = xmpData.count();

    EXPECT_EQ(finalCount, initialCount - 1);

}



TEST_F(XmpDataTest_1303, InvalidKeyHandling_1303) {

    XmpKey invalidKey("");

    int result = xmpData.add(invalidKey, value.get());

    EXPECT_NE(result, 0); // Assuming non-zero indicates failure due to invalid key

}
