#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

#include <algorithm>

#include <vector>

#include <string>



using namespace Exiv2;



class XmpDataTest : public ::testing::Test {

protected:

    XmpData xmpData;

};



TEST_F(XmpDataTest_1307, SortByKeyWithEmptyData_1307) {

    // Arrange

    // No elements added to xmpData



    // Act

    xmpData.sortByKey();



    // Assert

    EXPECT_TRUE(xmpData.empty());

}



TEST_F(XmpDataTest_1307, SortByKeyWithSingleElement_1307) {

    // Arrange

    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Example Title");

    xmpData.add(key, value);



    // Act

    xmpData.sortByKey();



    // Assert

    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(XmpDataTest_1307, SortByKeyWithMultipleElementsAlreadySorted_1307) {

    // Arrange

    XmpKey key1("Xmp.dc.title");

    Value* value1 = new StringValue("Title A");

    xmpData.add(key1, value1);



    XmpKey key2("Xmp.dc.description");

    Value* value2 = new StringValue("Description B");

    xmpData.add(key2, value2);



    // Act

    xmpData.sortByKey();



    // Assert

    auto it = xmpData.begin();

    EXPECT_EQ(it->key(), "Xmp.dc.description");

    ++it;

    EXPECT_EQ(it->key(), "Xmp.dc.title");

}



TEST_F(XmpDataTest_1307, SortByKeyWithMultipleElementsUnsorted_1307) {

    // Arrange

    XmpKey key1("Xmp.dc.title");

    Value* value1 = new StringValue("Title A");

    xmpData.add(key1, value1);



    XmpKey key2("Xmp.dc.description");

    Value* value2 = new StringValue("Description B");

    xmpData.add(key2, value2);



    // Unsorted order: reverse the insertion order

    std::vector<Xmpdatum> temp(xmpData.begin(), xmpData.end());

    std::reverse(temp.begin(), temp.end());

    xmpData.clear();

    for (const auto& datum : temp) {

        xmpData.add(datum);

    }



    // Act

    xmpData.sortByKey();



    // Assert

    auto it = xmpData.begin();

    EXPECT_EQ(it->key(), "Xmp.dc.description");

    ++it;

    EXPECT_EQ(it->key(), "Xmp.dc.title");

}



TEST_F(XmpDataTest_1307, SortByKeyWithDuplicateKeys_1307) {

    // Arrange

    XmpKey key("Xmp.dc.title");

    Value* value1 = new StringValue("Title A");

    xmpData.add(key, value1);



    Value* value2 = new StringValue("Title B");

    xmpData.add(key, value2);



    // Act

    xmpData.sortByKey();



    // Assert

    EXPECT_EQ(xmpData.count(), 2);

    auto it = xmpData.begin();

    EXPECT_EQ(it->key(), "Xmp.dc.title");

    ++it;

    EXPECT_EQ(it->key(), "Xmp.dc.title");

}
