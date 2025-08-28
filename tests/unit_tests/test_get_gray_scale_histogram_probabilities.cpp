#include <catch2/catch_all.hpp>

#include <vector>

#include <image_processing.hpp>

TEST_CASE( "Get Gray Scale Historgram Probabilities" ) {
    not_sure::gray_scale_histogram histogram{};
    histogram[ 0 ] = 5;   
    histogram[ 128 ] = 10;   
    histogram[ 255 ] = 5;   
    not_sure::gray_scale_histogram_probabilities expected{};
    expected[ 0 ] = 0.25;   
    expected[ 128 ] = 0.5;   
    expected[ 255 ] = 0.25; 
    not_sure::gray_scale_histogram_probabilities actual = not_sure::get_gray_scale_histogram_probabilities( histogram );
    REQUIRE( actual == expected );
}