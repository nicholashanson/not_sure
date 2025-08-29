#include <catch2/catch_all.hpp>

#include <image_processing.hpp>

TEST_CASE( "Get Otsu Threshold" ) {
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
    auto result = not_sure::get_otsu_threshold( image );
    REQUIRE( result.has_value() );
    REQUIRE( static_cast<int>( result.value() ) == 127 ); 
}
