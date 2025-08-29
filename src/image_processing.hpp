#include <cstdint>

#include <array>
#include <expected>
#include <numeric>
#include <string>
#include <vector>

namespace not_sure {

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

	gray_scale_histogram get_gray_scale_histogram( const std::vector<std::vector<uint8_t>>& gray_scale_image );

	gray_scale_histogram_probabilities get_gray_scale_histogram_probabilities( const gray_scale_histogram& histogram );

	std::expected<class_statistics,std::string> get_class_statistics( const gray_scale_histogram_probabilities& probabilities, const uint8_t threshold );

	double get_between_class_variance( const class_statistics& statistics );

	std::expected<uint8_t,std::string> get_otsu_threshold( const std::vector<std::vector<uint8_t>> image );

} // namespace not_sure