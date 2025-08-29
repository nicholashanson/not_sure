#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Apply Otsu Threshold Base Case" ) { 
    not_sure::gray_scale_image image = { .m_pixels = { 0, 0, 0, 255, 255, 255 }, .m_width = 3, .m_height = 2 };
    auto otsu_result = not_sure::apply_otsu_threshold( image ); 
    REQUIRE( otsu_result.has_value() == true );
    REQUIRE( otsu_result.value() == image );
}