/*
 * MIT License
 *
 * Copyright (c) 2025 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file Utils.inl
 * @brief Implementation file for high-performance string utilities
 * @details Inline implementations of string validation, parsing, and comparison functions
 *          with optimized algorithms for maximum runtime performance and minimal overhead.
 */

#include <algorithm>
#include <cctype>
#include <cmath>
#include <charconv>

namespace nfx::string
{
	//=====================================================================
	// String utilities
	//=====================================================================

	//----------------------------------------------
	// String validation
	//----------------------------------------------

	inline constexpr bool hasExactLength( std::string_view str, std::size_t expectedLength ) noexcept
	{
		return str.size() == expectedLength;
	}

	inline constexpr bool isEmpty( std::string_view str ) noexcept
	{
		return str.empty();
	}

	inline constexpr bool isNullOrWhiteSpace( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return true;
		}

		for ( const char c : str )
		{
			// Check for standard whitespace characters: space, tab, newline, carriage return, form feed, vertical tab
			if ( c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\f' && c != '\v' )
			{
				return false;
			}
		}
		return true;
	}

	inline constexpr bool isAllDigits( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isDigit( c ); } );
	}

	//----------------------------------------------
	// Character Classification
	//----------------------------------------------

	inline constexpr bool isWhitespace( char c ) noexcept
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
	}

	inline constexpr bool isDigit( char c ) noexcept
	{
		return static_cast<unsigned char>( c - '0' ) <= 9u;
	}

	inline constexpr bool isAlpha( char c ) noexcept
	{
		return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
	}

	inline constexpr bool isAlphaNumeric( char c ) noexcept
	{
		return isAlpha( c ) || isDigit( c );
	}

	//----------------------------------------------
	// String operations
	//----------------------------------------------

	inline constexpr bool startsWith( std::string_view str, std::string_view prefix ) noexcept
	{
		// Thin wrapper only
		return str.starts_with( prefix );
	}

	inline constexpr bool contains( std::string_view str, std::string_view substr ) noexcept
	{
		return str.find( substr ) != std::string_view::npos;
	}

	inline constexpr bool endsWith( std::string_view str, std::string_view suffix ) noexcept
	{
		// Thin wrapper only
		return str.ends_with( suffix );
	}

	inline constexpr bool equals( std::string_view lhs, std::string_view rhs ) noexcept
	{
		return lhs == rhs;
	}

	inline bool iequals( std::string_view lhs, std::string_view rhs ) noexcept
	{
		if ( lhs.size() != rhs.size() )
		{
			return false;
		}

		return std::equal( lhs.begin(), lhs.end(), rhs.begin(),
			[]( char a, char b ) noexcept { return toLower( a ) == toLower( b ); } );
	}

	//----------------------------------------------
	// String Trimming
	//----------------------------------------------

	//----------------------------
	// Non-allocating
	//----------------------------

	inline constexpr std::string_view trimStart( std::string_view str ) noexcept
	{
		std::size_t start = 0;
		while ( start < str.size() && isWhitespace( str[start] ) )
		{
			++start;
		}
		return str.substr( start );
	}

	inline constexpr std::string_view trimEnd( std::string_view str ) noexcept
	{
		std::size_t end = str.size();
		while ( end > 0 && isWhitespace( str[end - 1] ) )
		{
			--end;
		}
		return str.substr( 0, end );
	}

	inline constexpr std::string_view trim( std::string_view str ) noexcept
	{
		return trimEnd( trimStart( str ) );
	}

	//----------------------------------------------
	// String case conversion
	//----------------------------------------------

	inline std::string toLower( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			result.push_back( toLower( c ) );
		}

		return result;
	}

	inline std::string toUpper( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			result.push_back( toUpper( c ) );
		}

		return result;
	}

	//----------------------------------------------
	// Character case conversion
	//----------------------------------------------

	inline constexpr char toLower( char c ) noexcept
	{
		return ( c >= 'A' && c <= 'Z' ) ? static_cast<char>( c + ( 'a' - 'A' ) ) : c;
	}

	inline constexpr char toUpper( char c ) noexcept
	{
		return ( c >= 'a' && c <= 'z' ) ? static_cast<char>( c - ( 'a' - 'A' ) ) : c;
	}

	//----------------------------------------------
	// Parsing
	//----------------------------------------------

	inline bool tryParseBool( std::string_view str, bool& result ) noexcept
	{
		if ( str.empty() )
		{
			result = false;
			return false;
		}

		// Handle single character cases first
		if ( str.size() == 1 )
		{
			const char c{ toLower( str[0] ) };
			if ( c == '1' || c == 't' || c == 'y' )
			{
				result = true;
				return true;
			}
			else if ( c == '0' || c == 'f' || c == 'n' )
			{
				result = false;
				return true;
			}
			return false;
		}

		// Handle multi-character cases
		if ( str.size() == 2 )
		{
			if ( ( toLower( str[0] ) == 'o' && toLower( str[1] ) == 'n' ) )
			{
				result = true;
				return true;
			}
			else if ( ( toLower( str[0] ) == 'n' && toLower( str[1] ) == 'o' ) )
			{
				result = false;
				return true;
			}
		}
		else if ( str.size() == 3 )
		{
			if ( toLower( str[0] ) == 'y' && toLower( str[1] ) == 'e' && toLower( str[2] ) == 's' )
			{
				result = true;
				return true;
			}
			else if ( toLower( str[0] ) == 'o' && toLower( str[1] ) == 'f' && toLower( str[2] ) == 'f' )
			{
				result = false;
				return true;
			}
		}
		else if ( str.size() == 4 )
		{
			if ( toLower( str[0] ) == 't' && toLower( str[1] ) == 'r' &&
				 toLower( str[2] ) == 'u' && toLower( str[3] ) == 'e' )
			{
				result = true;
				return true;
			}
		}
		else if ( str.size() == 5 )
		{
			if ( toLower( str[0] ) == 'f' && toLower( str[1] ) == 'a' &&
				 toLower( str[2] ) == 'l' && toLower( str[3] ) == 's' && toLower( str[4] ) == 'e' )
			{
				result = false;
				return true;
			}
		}

		result = false;
		return false;
	}

	inline bool tryParseInt( std::string_view str, int& result ) noexcept
	{
		if ( str.empty() )
		{
			result = 0;
			return false;
		}

		const char* const begin = str.data();
		const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.length() ) );
		const auto parseResult{ std::from_chars( begin, end, result ) };
		return parseResult.ec == std::errc{} && parseResult.ptr == end;
	}

	inline bool tryParseUInt( std::string_view str, std::uint32_t& result ) noexcept
	{
		if ( str.empty() )
		{
			result = 0u;
			return false;
		}

		const char* const begin = str.data();
		const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
		const auto parseResult{ std::from_chars( begin, end, result ) };
		return parseResult.ec == std::errc{} && parseResult.ptr == end;
	}

	inline bool tryParseLong( std::string_view str, std::int64_t& result ) noexcept
	{
		if ( str.empty() )
		{
			result = 0LL;
			return false;
		}

		const char* const begin = str.data();
		const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
		const auto parseResult{ std::from_chars( begin, end, result ) };
		return parseResult.ec == std::errc{} && parseResult.ptr == end;
	}

	inline bool tryParseFloat( std::string_view str, float& result ) noexcept
	{
		if ( str.empty() )
		{
			result = 0.f;
			return false;
		}

		const char* const begin = str.data();
		const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
		const auto parseResult{ std::from_chars( begin, end, result ) };
		return parseResult.ec == std::errc{} && parseResult.ptr == end;
	}

	inline bool tryParseDouble( std::string_view str, double& result ) noexcept
	{
		if ( str.empty() )
		{
			result = 0.0;
			return false;
		}

		const char* const begin = str.data();
		const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
		const auto parseResult{ std::from_chars( begin, end, result ) };
		return parseResult.ec == std::errc{} && parseResult.ptr == end;
	}

	//----------------------------------------------
	// Network and URI validation
	//----------------------------------------------

	//-----------------------------
	// URI character classification
	//-----------------------------

	inline constexpr bool isURIReserved( char c ) noexcept
	{
		// RFC 3986 Section 2.2 - Reserved Characters
		// gen-delims: : / ? # [ ] @
		// sub-delims: ! $ & ' ( ) * + , ; =
		return c == ':' || c == '/' || c == '?' || c == '#' || c == '[' || c == ']' || c == '@' ||
			   c == '!' || c == '$' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' ||
			   c == '+' || c == ',' || c == ';' || c == '=';
	}

	inline constexpr bool isURIReserved( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isURIReserved( c ); } );
	}

	inline constexpr bool isURIUnreserved( char c ) noexcept
	{
		// RFC 3986 Section 2.3 - Unreserved Characters
		// ALPHA / DIGIT / "-" / "." / "_" / "~"
		return isAlphaNumeric( c ) || c == '-' || c == '.' || c == '_' || c == '~';
	}

	inline constexpr bool isURIUnreserved( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isURIUnreserved( c ); } );
	}

	//-----------------------------
	// IP address validation
	//-----------------------------

	inline constexpr bool isIPv4Address( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 15 ) // Max: "255.255.255.255"
		{
			return false;
		}

		int octetCount = 0;
		int currentOctet = 0;
		int digitCount = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == '.' )
			{
				if ( digitCount == 0 || currentOctet > 255 )
				{
					return false;
				}
				++octetCount;
				currentOctet = 0;
				digitCount = 0;
			}
			else if ( isDigit( c ) )
			{
				// Check for leading zero: if we have '0' and there are more digits coming in this octet
				if ( digitCount == 1 && currentOctet == 0 )
				{
					return false; // Leading zero like "01", "001", etc.
				}

				currentOctet = currentOctet * 10 + ( c - '0' );
				++digitCount;
				if ( digitCount > 3 || currentOctet > 255 )
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		// Must have exactly 3 dots (4 octets) and valid last octet
		return octetCount == 3 && digitCount > 0 && currentOctet <= 255;
	}

	inline constexpr bool isIPv6Address( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 45 ) // Max with zone: "[ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255%interface]"
		{
			return false;
		}

		int groupCount = 0;
		int digitCount = 0;
		bool hasDoubleColon = false;
		bool prevWasColon = false;
		std::size_t groupStartPos = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == ':' )
			{
				if ( prevWasColon )
				{
					if ( hasDoubleColon )
					{
						return false; // Only one :: allowed
					}
					hasDoubleColon = true;
				}
				else if ( digitCount > 0 )
				{
					++groupCount;
				}
				digitCount = 0;
				prevWasColon = true;
				groupStartPos = i + 1; // Next group starts after this colon
			}
			else if ( ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ) )
			{
				++digitCount;
				if ( digitCount > 4 )
				{
					return false; // Max 4 hex digits per group
				}
				prevWasColon = false;
			}
			else if ( c == '.' )
			{
				// IPv4-mapped address (e.g., ::ffff:192.0.2.1)
				// Extract IPv4 part starting from where current group began
				const std::string_view ipv4Part = str.substr( groupStartPos );

				// Find where IPv4 actually ends (before % if present)
				const std::size_t percentPos = ipv4Part.find( '%' );
				const std::string_view ipv4Only = ( percentPos != std::string_view::npos )
													  ? ipv4Part.substr( 0, percentPos )
													  : ipv4Part;

				if ( !isIPv4Address( ipv4Only ) )
				{
					return false;
				}
				// IPv4 part counts as 2 groups (32 bits = 2 x 16-bit groups)
				groupCount += 2;
				break; // IPv4 is at the end
			}
			else if ( c == '%' )
			{
				// Zone ID - rest is interface name, accept it
				if ( digitCount > 0 )
				{
					++groupCount;
				}
				break;
			}
			else
			{
				return false;
			}
		}

		if ( digitCount > 0 && str.find( '.' ) == std::string_view::npos )
		{
			++groupCount; // Only count if not IPv4-mapped (already counted above)
		}

		// Valid: 8 groups, or less with :: compression
		return ( groupCount == 8 && !hasDoubleColon ) || ( groupCount < 8 && hasDoubleColon );
	}

	//-----------------------------
	// Host validation
	//-----------------------------

	inline constexpr bool isValidHostname( std::string_view str ) noexcept
	{
		// RFC 1123: max 253 chars, labels max 63 chars, alphanumeric + hyphen
		if ( str.empty() || str.size() > 253 )
		{
			return false;
		}

		int labelLength = 0;
		bool prevWasDot = true;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == '.' )
			{
				if ( prevWasDot || labelLength == 0 )
				{
					return false; // Empty label or consecutive dots
				}
				if ( str[i - 1] == '-' )
				{
					return false; // Label can't end with hyphen
				}
				labelLength = 0;
				prevWasDot = true;
			}
			else if ( isAlphaNumeric( c ) || c == '-' )
			{
				if ( prevWasDot && c == '-' )
				{
					return false; // Label can't start with hyphen
				}
				++labelLength;
				if ( labelLength > 63 )
				{
					return false; // Label too long
				}
				prevWasDot = false;
			}
			else
			{
				return false; // Invalid character
			}
		}

		// Can't end with dot or hyphen
		return !prevWasDot && labelLength > 0 && str[str.size() - 1] != '-';
	}

	inline constexpr bool isDomainName( std::string_view str ) noexcept
	{
		// Must be valid hostname AND contain at least one dot
		if ( !isValidHostname( str ) )
		{
			return false;
		}

		// Check for at least one dot
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '.' )
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------
	// Port validation
	//-----------------------------

	inline constexpr bool isValidPort( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 5 ) // Max: "65535"
		{
			return false;
		}

		int portValue = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( !isDigit( str[i] ) )
			{
				return false;
			}
			portValue = portValue * 10 + ( str[i] - '0' );
			if ( portValue > 65535 )
			{
				return false;
			}
		}

		return true;
	}

	template <typename T, typename>
	[[nodiscard]] inline constexpr bool isValidPort( T port ) noexcept
	{
		static_assert( std::is_integral_v<T>, "Port must be an integral type" );
		return port >= 0 && port <= 65535;
	}

	//-----------------------------
	// Endpoint parsing
	//-----------------------------

	inline bool tryParseEndpoint( std::string_view endpoint, std::string_view& host, uint16_t& port ) noexcept
	{
		if ( endpoint.empty() )
		{
			return false;
		}

		// Check for IPv6 format: [host]:port
		if ( endpoint[0] == '[' )
		{
			const std::size_t closingBracket = endpoint.find( ']' );
			if ( closingBracket == std::string_view::npos )
			{
				return false;
			}

			host = endpoint.substr( 1, closingBracket - 1 );

			// Check for :port after ]
			if ( closingBracket + 1 < endpoint.size() )
			{
				if ( endpoint[closingBracket + 1] != ':' )
				{
					return false;
				}
				const std::string_view portStr = endpoint.substr( closingBracket + 2 );
				if ( !isValidPort( portStr ) )
				{
					return false;
				}
				// Parse port
				uint32_t portValue = 0;
				if ( !tryParseUInt( portStr, portValue ) || portValue > 65535 )
				{
					return false;
				}
				port = static_cast<uint16_t>( portValue );
			}
			else
			{
				return false; // No port specified
			}

			return isIPv6Address( host );
		}

		// IPv4 or hostname format: host:port
		const std::size_t colonPos = endpoint.rfind( ':' ); // Last colon
		if ( colonPos == std::string_view::npos )
		{
			return false; // No port separator
		}

		host = endpoint.substr( 0, colonPos );
		const std::string_view portStr = endpoint.substr( colonPos + 1 );

		if ( host.empty() || portStr.empty() )
		{
			return false;
		}

		if ( !isValidPort( portStr ) )
		{
			return false;
		}

		// Parse port
		uint32_t portValue = 0;
		if ( !tryParseUInt( portStr, portValue ) || portValue > 65535 )
		{
			return false;
		}
		port = static_cast<uint16_t>( portValue );

		// If host contains only digits and dots, it must be a valid IPv4
		// Otherwise validate as hostname
		const bool looksLikeIPv4 = std::all_of( host.begin(), host.end(),
			[]( char c ) { return isDigit( c ) || c == '.'; } );

		if ( looksLikeIPv4 )
		{
			return isIPv4Address( host );
		}

		return isValidHostname( host );
	}
} // namespace nfx::string
