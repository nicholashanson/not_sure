#include <image_processing.hpp>

namespace not_sure {

	gray_scale_histogram get_gray_scale_histogram( std::vector<std::vector<uint8_t>> gray_scale_image ) {
		gray_scale_histogram histogram{}; 
	    for (const auto& row : gray_scale_image) {
	        for ( auto pixel : row ) {
	            ++histogram[ pixel ]; 
	    	}
		}
		return histogram;
	}

} // namespace not_sure