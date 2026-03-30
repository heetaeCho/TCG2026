

```cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include "nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



// Test case for a known lens ID with all metadata available

TEST(Nikon3MakerNoteTest, KnownLensId) {

    const std::string group = "Nikon3";

    Nikon3MakerNote makerNote;

    Value::AutoPtr pValue = Value::create(unsignedByte);

    byte data[] = {0x1A, 0x00, 0x07, 0x00, 0x40, 0x2C, 0x03, 0x00, 0x1B, 0x00};

    pValue->read(data, sizeof(data));



    ExifData exifData;

    ExifKey key("Exif.Nikon3.LensId");

    exifData.add(key, pValue.get());



    std::ostringstream os;

    makerNote.printLensId(os, *pValue, &exifData, group);



    EXPECT_EQ(os.str(), "AF-S NIKKOR 24-70mm f/2.8G ED\n");

}



// Test case for an unknown lens ID with all metadata available

TEST(Nikon3MakerNoteTest, UnknownLensId) {

    const std::string group = "Nikon3";

    Nikon3MakerNote makerNote;

    Value::AutoPtr pValue = Value::create(unsignedByte);

    byte data[] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00};

    pValue->read(data, sizeof(data));



    ExifData exifData;

    ExifKey key("Exif.Nikon3.LensId");

    exifData.add(key, pValue.get());



    std::ostringstream os;

    makerNote.printLensId(os, *pValue, &exifData, group);



    EXPECT_EQ(os.str(), "Unknown lens\n");

}



// Test case with incomplete metadata

TEST(Nikon3MakerNoteTest, IncompleteMetadata) {

    const std::string group = "Nikon3";

    Nikon3MakerNote makerNote;

    Value::AutoPtr pValue = Value::create(unsignedByte);

    byte data[] = {0x1A, 0x00}; // Only first two bytes are provided

    pValue->read(data, sizeof(data));



    ExifData exifData;

    ExifKey key("Exif.Nikon3.LensId");

    exifData.add(key, pValue.get());



    std::ostringstream os;

    makerNote.printLensId(os, *pValue, &exifData, group);



    EXPECT_EQ(os.str(), "Unknown lens\n");

}



// Test case with no metadata

TEST(Nikon3MakerNoteTest, NoMetadata) {

    const std::string group = "Nikon3";

    Nikon3MakerNote makerNote;

    Value::AutoPtr pValue = Value::create(unsignedByte);

    byte data[] = {};

    pValue->read(data, sizeof(data));



    ExifData exifData;



    std::ostringstream os;

    makerNote.printLensId(os, *pValue, &exifData, group);



    EXPECT_EQ(os.str(), "Unknown lens\n");

}



// Test case with a different type of value (incorrect type)

TEST(Nikon3MakerNoteTest, IncorrectValueType) {

    const std::string group = "Nikon3";

    Nikon3MakerNote makerNote;

    Value::AutoPtr pValue = Value::create(asciiString);

    byte data[] = {'H', 'e', 'l', 'l', 'o'};

    pValue->read(data, sizeof(data));



    ExifData exifData;

    ExifKey key("Exif.Nikon3.LensId");

    exifData.add(key, pValue.get());



    std::ostringstream os;

    makerNote.printLensId(os, *pValue, &exifData, group);



    EXPECT_EQ(os.str(), "Unknown lens\n");

}

```


