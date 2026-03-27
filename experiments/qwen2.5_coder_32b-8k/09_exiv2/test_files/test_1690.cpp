

### Test Case 1: Basic Initialization



```cpp

#include <gtest/gtest.h>

#include "tiffencoder_int.hpp"

#include "types.hpp"



TEST(TiffEncoderTest, Initialization) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    EXPECT_NO_THROW(Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    ));

}

```



### Test Case 2: Encoding Basic TiffEntry



```cpp

#include "tiffentry_int.hpp"

#include "exifdatum.hpp"



TEST(TiffEncoderTest, EncodeBasicTiffEntry) {

    Exiv2::ExifData exifData;

    auto key = Exiv2::ExifKey("Exif.Image.Artist");

    exifData.add(key, "John Doe");



    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    auto entry = new Exiv2::Internal::TiffEntry();

    entry->setTag(Exiv2::ImageIFD::artist);

    encoder.visitEntry(entry);



    // Here we can add assertions to check if the entry was encoded correctly.

}

```



### Test Case 3: Encoding TiffMnEntry



```cpp

TEST(TiffEncoderTest, EncodeTiffMnEntry) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    auto mnEntry = new Exiv2::Internal::TiffMnEntry();

    encoder.visitMnEntry(mnEntry);



    // Here we can add assertions to check if the mnEntry was encoded correctly.

}

```



### Test Case 4: Encoding BinaryArray and BinaryElement



```cpp

TEST(TiffEncoderTest, EncodeBinaryElements) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    auto binaryArray = new Exiv2::Internal::TiffBinaryArray();

    encoder.visitBinaryArray(binaryArray);



    auto binaryElement = new Exiv2::Internal::TiffBinaryElement();

    encoder.visitBinaryElement(binaryElement);



    // Here we can add assertions to check if the binary elements were encoded correctly.

}

```



### Test Case 5: Setting Dirty Flag



```cpp

TEST(TiffEncoderTest, SetDirtyFlag) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    encoder.setDirty(true);

    EXPECT_TRUE(encoder.dirty());



    encoder.setDirty(false);

    EXPECT_FALSE(encoder.dirty());

}

```



### Test Case 6: Byte Order



```cpp

TEST(TiffEncoderTest, ByteOrder) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    // Assuming pHeader is properly mocked to set byte order as littleEndian for this test.

    EXPECT_EQ(encoder.byteOrder(), Exiv2::littleEndian);

}

```



### Test Case 7: Write Method



```cpp

TEST(TiffEncoderTest, WriteMethod) {

    Exiv2::ExifData exifData;

    Exiv2::IptcData iptcData;

    Exiv2::XmpData xmpData;



    std::unique_ptr<Exiv2::Internal::TiffComponent> pRoot(new Exiv2::Internal::TiffDirectory());

    bool isNewImage = false;

    Exiv2::PrimaryGroups pPrimaryGroups;

    const Exiv2::TiffHeaderBase* pHeader = nullptr; // Assuming we can provide a mock or null header for this test

    Exiv2::Internal::FindEncoderFct findEncoderFct = nullptr;



    Exiv2::Internal::TiffEncoder encoder(

        std::move(exifData),

        iptcData,

        xmpData,

        pRoot.get(),

        isNewImage,

        std::move(pPrimaryGroups),

        pHeader,

        findEncoderFct

    );



    EXPECT_EQ(encoder.writeMethod(), Exiv2::wmNonIntrusive);

}

```


