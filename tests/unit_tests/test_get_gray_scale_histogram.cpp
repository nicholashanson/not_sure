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

TEST_CASE( "Get Gray Scale Historgram Double Peaks" ) {
    std::vector<std::vector<uint8_t>> image;
    for ( int i = 0; i <= 127; ++i ) {
        int count = ( i <= 63 ) ? i + 1    
                  : ( i <= 64 ) ? 64         
                  : 64 - ( i - 64 );      
        for ( int j = 0; j < count; ++j ) {
            image.push_back( { static_cast<uint8_t>( i ) } );
        }
    }
    for ( int i = 128; i <= 255; ++i ) {
        int count = ( i <= 191 ) ? i - 127   
                  : ( i <= 192 ) ? 64         
                  : 256 - i;                
        for ( int j = 0; j < count; ++j ) {
            image.push_back( { static_cast<uint8_t>( i ) } );
        }
    }
    not_sure::gray_scale_histogram expected_histogram{};
    for (int i = 0; i <= 127; ++i) {
        int count = (i <= 63) ? i + 1
                  : (i == 64) ? 64
                  : 64 - (i - 64);
        expected_histogram[i] = count;
    }
    for (int i = 128; i <= 255; ++i) {
        int count = (i <= 191) ? i - 127
                  : (i == 192) ? 64
                  : 256 - i;
        expected_histogram[i] = count;
    }
    not_sure::gray_scale_histogram actual_histogram = not_sure::get_gray_scale_histogram( image );
    REQUIRE( actual_histogram == expected_histogram );
}