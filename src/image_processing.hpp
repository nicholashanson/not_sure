#include <cstdint>

#include <array>
#include <expected>
#include <numeric>
#include <string>
#include <vector>

namespace not_sure {

	struct gray_scale_image {
    	std::vector<uint8_t> m_pixels; 
    	std::size_t m_width;
    	std::size_t m_height;

    	bool operator==( const gray_scale_image& other ) const {
			return m_pixels == other.m_pixels && 
				   m_width == other.m_width && 
				   m_height == other.m_height;
		}
	};

	enum class binary_value : uint8_t {
		black = 0x00,
		white = 0xff
	};

	struct binary_image {
		std::vector<binary_value> m_pixels; 
    	std::size_t m_width;
    	std::size_t m_height;

    	bool operator==( const binary_image& other ) const {
			return m_pixels == other.m_pixels && 
				   m_width == other.m_width && 
				   m_height == other.m_height;
		}
	};

	bool operator==( const gray_scale_image& gray, const binary_image& binary );

	struct class_statistics {
		double m_foreground_probability;
		double m_background_probability;
		double m_foreground_mean;
		double m_background_mean;

		class_statistics()
        	: m_foreground_probability( 0.0 ),
          	  m_background_probability( 0.0 ),
          	  m_foreground_mean( 0.0 ),
          	  m_background_mean( 0.0 ) {}

        class_statistics( double foreground_probability, double background_probability, double foreground_mean, double background_mean ) 
        	: m_foreground_probability( foreground_probability ),
          	  m_background_probability( background_probability ),
          	  m_foreground_mean( foreground_mean ),
          	  m_background_mean( background_mean ) {}

		bool operator==( const class_statistics& other ) const {
			return m_foreground_probability == other.m_foreground_probability &&
				   m_background_probability == other.m_background_probability &&
				   m_foreground_mean == other.m_foreground_mean &&
				   m_background_mean == other.m_background_mean;
		}
	};

	using gray_scale_histogram = std::array<std::size_t,256>;

	using gray_scale_histogram_probabilities = std::array<double,256>;

	gray_scale_histogram get_gray_scale_histogram( const gray_scale_image& image );

	gray_scale_histogram_probabilities get_gray_scale_histogram_probabilities( const gray_scale_histogram& histogram );

	std::expected<class_statistics,std::string> get_class_statistics( const gray_scale_histogram_probabilities& probabilities, const uint8_t threshold );

	double get_between_class_variance( const class_statistics& statistics );

	std::expected<uint8_t,std::string> get_otsu_threshold( const gray_scale_image& image );

	std::expected<binary_image,std::string> apply_otsu_threshold( const gray_scale_image& image );

} // namespace not_sure