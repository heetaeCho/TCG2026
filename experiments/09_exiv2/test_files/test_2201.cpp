

### Test Cases



#### exiv2/exif.cpp (ExifData)

```cpp

#include <exiv2/exif.hpp>

#include <gtest/gtest.h>



TEST(ExifDataTest, AddRemoveTags) {

    Exiv2::ExifData exifData;

    Exiv2::Value::AutoPtr value = Exiv2::Value::create(Exiv2::unsignedShort);

    value->read("100");



    exifData.add(Exiv2::ExifKey("Exif.Image.Orientation"), value.get());

    ASSERT_EQ(exifData.count(), 1);



    exifData.erase("Exif.Image.Orientation");

    ASSERT_EQ(exifData.count(), 0);

}



TEST(ExifDataTest, FindTag) {

    Exiv2::ExifData exifData;

    Exiv2::Value::AutoPtr value = Exiv2::Value::create(Exiv2::unsignedShort);

    value->read("100");



    exifData.add(Exiv2::ExifKey("Exif.Image.Orientation"), value.get());

    ASSERT_TRUE(exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation")) != exifData.end());



    exifData.erase("Exif.Image.Orientation");

    ASSERT_FALSE(exifData.findKey(Exiv2::ExifKey("Exif.Image.Orientation")) != exifData.end());

}

```



#### exiv2/iptc.cpp (IptcData)

```cpp

#include <exiv2/iptc.hpp>

#include <gtest/gtest.h>



TEST(IptcDataTest, AddRemoveTags) {

    Exiv2::IptcData iptcData;

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Keywords"), "test");



    ASSERT_EQ(iptcData.count(), 1);

    iptcData.erase(Exiv2::IptcKey("Iptc.Application2.Keywords"));

    ASSERT_EQ(iptcData.count(), 0);

}



TEST(IptcDataTest, FindTag) {

    Exiv2::IptcData iptcData;

    iptcData.add(Exiv2::IptcKey("Iptc.Application2.Keywords"), "test");



    ASSERT_TRUE(iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords")) != iptcData.end());



    iptcData.erase(Exiv2::IptcKey("Iptc.Application2.Keywords"));

    ASSERT_FALSE(iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Keywords")) != iptcData.end());

}

```



#### exiv2/xmp.cpp (XmpData)

```cpp

#include <exiv2/xmp.hpp>

#include <gtest/gtest.h>



TEST(XmpDataTest, AddRemoveTags) {

    Exiv2::XmpData xmpData;

    xmpData.add(Exiv2::XmpKey("Xmp.dc.subject"), "test");



    ASSERT_EQ(xmpData.count(), 1);

    xmpData.erase(Exiv2::XmpKey("Xmp.dc.subject"));

    ASSERT_EQ(xmpData.count(), 0);

}



TEST(XmpDataTest, FindTag) {

    Exiv2::XmpData xmpData;

    xmpData.add(Exiv2::XmpKey("Xmp.dc.subject"), "test");



    ASSERT_TRUE(xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject")) != xmpData.end());



    xmpData.erase(Exiv2::XmpKey("Xmp.dc.subject"));

    ASSERT_FALSE(xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject")) != xmpData.end());

}

```



#### exiv2/internal/tiffcomposite_int.hpp (TiffFinder)

```cpp

#include <exiv2/internal/tiffcomposite_int.hpp>

#include <gtest/gtest.h>



using namespace Exiv2;

using namespace Internal;



TEST(TiffFinderTest, FindTag) {

    TiffFinder finder(0x10F, IfdId::ifd0Id); // Finding Make tag in IFD0

    TiffComponent* component = new TiffEntry();

    TiffEntry* entry = static_cast<TiffEntry*>(component);

    entry->tag_ = 0x10F;

    entry->group_ = IfdId::ifd0Id;



    finder.visitEntry(entry);

    ASSERT_EQ(finder.result(), component);



    delete component;

}

```



#### exiv2/internal/tiffvisitor_int.hpp (TiffEncoder)

```cpp

#include <exiv2/internal/tiffvisitor_int.hpp>

#include <gtest/gtest.h>



using namespace Exiv2;

using namespace Internal;



TEST(TiffEncoderTest, VisitEntry) {

    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups{}, nullptr, nullptr);

    TiffComponent* component = new TiffEntry();

    TiffEntry* entry = static_cast<TiffEntry*>(component);



    encoder.visitEntry(entry); // No crash means it's handled



    delete component;

}



TEST(TiffEncoderTest, VisitDataEntry) {

    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups{}, nullptr, nullptr);

    TiffComponent* component = new TiffDataEntry();

    TiffDataEntry* entry = static_cast<TiffDataEntry*>(component);



    encoder.visitDataEntry(entry); // No crash means it's handled



    delete component;

}

```



#### exiv2/tags.hpp (IfdId)

```cpp

#include <exiv2/tags.hpp>

#include <gtest/gtest.h>



using namespace Exiv2;



TEST(IfdIdTest, EnumValues) {

    EXPECT_EQ(static_cast<int>(IfdId::ifd0Id), 1);

    EXPECT_EQ(static_cast<int>(IfdId::exifId), 5);

    EXPECT_EQ(static_cast<int>(IfdId::gpsId), 6);

    EXPECT_EQ(static_cast<int>(IfdId::iopId), 7);

    EXPECT_EQ(static_cast<int>(IfdId::mnId), 20);

}

```



These test cases cover some basic operations like adding, removing, and finding tags in the EXIF, IPTC, and XMP data containers. Additionally, they include tests for the `TiffFinder` and `TiffEncoder` classes to ensure they handle visiting different types of TIFF components correctly. The `IfdIdTest` verifies that the enum values are set as expected.


