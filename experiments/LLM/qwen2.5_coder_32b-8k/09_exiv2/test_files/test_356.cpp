#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;

using ::testing::_;

using ::testing::Invoke;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeSubIfd, (TiffSubIfd* object, const Exifdatum* datum), (override));

};



class TiffSubIfdTest_356 : public ::testing::Test {

protected:

    MockTiffEncoder mockEncoder;

    Exifdatum exifDatum{ExifKey("Exif.Image.Artist"), nullptr};

    TiffSubIfd tiffSubIfd{0x013B, ifdExif, ifdGPS};



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(TiffSubIfdTest_356, DoEncodeInvokesEncoder_356) {

    EXPECT_CALL(mockEncoder, encodeSubIfd(&tiffSubIfd, &exifDatum));

    tiffSubIfd.doEncode(mockEncoder, &exifDatum);

}



// No observable return value or exception for doEncode in the provided interface,

// so no additional test cases for exceptional behavior are necessary.



// Boundary conditions and other test cases:

// Since the method does not have many observable outcomes from the outside, we limit

// tests to ensuring that interactions with collaborators (mockEncoder) behave as expected.

```


