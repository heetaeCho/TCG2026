#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Mocking external collaborators if needed, but in this case, we don't need any.



TEST_F(PopplerAnnotMovieTest_2109, GetTitle_ReturnsValidString_2109) {

    // Arrange

    PopplerAnnotMovie *poppler_annot = reinterpret_cast<PopplerAnnotMovie*>(g_malloc(sizeof(PopplerAnnotMovie)));

    AnnotMovie mock_annot(nullptr, nullptr, nullptr);

    mock_annot.title = std::make_unique<GooString>("Sample Title");

    POPPLER_ANNOT(poppler_annot)->annot.reset(&mock_annot);



    // Act

    gchar *title = poppler_annot_movie_get_title(poppler_annot);



    // Assert

    EXPECT_STREQ("Sample Title", title);

    g_free(title);  // Free the allocated memory for the title

    g_free(poppler_annot);  // Free the allocated memory for PopplerAnnotMovie

}



TEST_F(PopplerAnnotMovieTest_2109, GetTitle_ReturnsNullptrWhenNoTitle_2109) {

    // Arrange

    PopplerAnnotMovie *poppler_annot = reinterpret_cast<PopplerAnnotMovie*>(g_malloc(sizeof(PopplerAnnotMovie)));

    AnnotMovie mock_annot(nullptr, nullptr, nullptr);

    mock_annot.title.reset();  // No title set

    POPPLER_ANNOT(poppler_annot)->annot.reset(&mock_annot);



    // Act

    gchar *title = poppler_annot_movie_get_title(poppler_annot);



    // Assert

    EXPECT_EQ(nullptr, title);

    g_free(poppler_annot);  // Free the allocated memory for PopplerAnnotMovie

}



TEST_F(PopplerAnnotMovieTest_2109, GetTitle_ReturnsNullptrForInvalidObject_2109) {

    // Arrange

    PopplerAnnotMovie *poppler_annot = nullptr;



    // Act

    gchar *title = poppler_annot_movie_get_title(poppler_annot);



    // Assert

    EXPECT_EQ(nullptr, title);

}



TEST_F(PopplerAnnotMovieTest_2109, GetTitle_ReturnsNullptrWhenGooStringIsNull_2109) {

    // Arrange

    PopplerAnnotMovie *poppler_annot = reinterpret_cast<PopplerAnnotMovie*>(g_malloc(sizeof(PopplerAnnotMovie)));

    AnnotMovie mock_annot(nullptr, nullptr, nullptr);

    mock_annot.title.reset(new GooString());  // Empty title

    POPPLER_ANNOT(poppler_annot)->annot.reset(&mock_annot);



    // Act

    gchar *title = poppler_annot_movie_get_title(poppler_annot);



    // Assert

    EXPECT_STREQ("", title);  // Expecting empty string, not nullptr

    g_free(title);  // Free the allocated memory for the title

    g_free(poppler_annot);  // Free the allocated memory for PopplerAnnotMovie

}

```


