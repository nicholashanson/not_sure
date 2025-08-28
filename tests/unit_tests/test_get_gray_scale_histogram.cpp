#define CATCH_CONFIG_MAIN  
#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Get Gray Scale Historgram" ) {
    std::vector<std::vector<uint8_t>> gray_scale_image = {
        { 0, 0, 255 },
        { 128, 128, 128 },
        { 255, 255, 0 }
    };
    not_sure::gray_scale_histogram expected{};
    expected[ 0 ] = 3;   
    expected[ 128 ] = 3;   
    expected[ 255 ] = 3;   
    not_sure::gray_scale_histogram actual = not_sure::get_gray_scale_histogram( gray_scale_image );
    REQUIRE( actual == expected );
}