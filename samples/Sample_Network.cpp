/**
 * @file Sample_Network.cpp
 * @brief Demonstrates network and URI validation utilities
 * @details This sample shows how to validate IPv4/IPv6 addresses, hostnames,
 *          domains, ports, and endpoints using RFC-compliant validation functions
 */

#include <array>
#include <iostream>
#include <string>
#include <string_view>

#include <nfx/string/Utils.h>

int main()
{
	std::cout << "=== nfx StringUtils - Network & URI Validation ===" << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// IPv4 Address Validation (RFC 791)
	//=========================================================================

	std::cout << "--- IPv4 Address Validation (RFC 791) ---" << std::endl;

	const std::string_view ipv4Examples[]{
		"192.168.1.1",	   // Valid private IP
		"10.0.0.1",		   // Valid private IP
		"172.16.0.1",	   // Valid private IP
		"8.8.8.8",		   // Valid public IP (Google DNS)
		"255.255.255.255", // Valid broadcast address
		"0.0.0.0",		   // Valid (any address)
		"127.0.0.1",	   // Valid loopback
		"256.1.1.1",	   // Invalid (octet > 255)
		"192.168.1",	   // Invalid (missing octet)
		"192.168.1.1.1",   // Invalid (too many octets)
		"192.168.-1.1",	   // Invalid (negative)
		"192.168.01.1",	   // Invalid (leading zero)
		"",				   // Invalid (empty)
		"not.an.ip.addr"   // Invalid (non-numeric)
	};

	for ( const auto& ip : ipv4Examples )
	{
		const bool isValid{ nfx::string::isIPv4Address( ip ) };
		std::cout << "  ";
		if ( ip.empty() )
		{
			std::cout << "(empty)";
			std::cout << std::string( 20 - 7, ' ' );
		}
		else
		{
			std::cout << ip;
			if ( ip.length() < 20 )
			{
				std::cout << std::string( 20 - ip.length(), ' ' );
			}
		}
		std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// IPv6 Address Validation (RFC 4291/5952)
	//=========================================================================

	std::cout << "--- IPv6 Address Validation (RFC 4291/5952) ---" << std::endl;

	const std::string_view ipv6Examples[]{
		"2001:0db8:85a3:0000:0000:8a2e:0370:7334", // Valid full form
		"2001:db8:85a3::8a2e:370:7334",			   // Valid compressed
		"::1",									   // Valid loopback
		"::",									   // Valid any address
		"fe80::1",								   // Valid link-local
		"ff02::1",								   // Valid multicast
		"2001:db8::1",							   // Valid compressed
		"::ffff:192.0.2.1",						   // Valid IPv4-mapped
		"fe80::1%eth0",							   // Valid with zone ID
		"2001:db8:85a3::8a2e:370g:7334",		   // Invalid (g is not hex)
		"02001:db8::1",							   // Invalid (5 hex digits)
		"2001:db8:::1",							   // Invalid (triple colon)
		"",										   // Invalid (empty)
		"hello::world"							   // Invalid (non-hex)
	};

	for ( const auto& ip : ipv6Examples )
	{
		const bool isValid{ nfx::string::isIPv6Address( ip ) };
		std::cout << "  ";
		if ( ip.empty() )
		{
			std::cout << "(empty)";
			std::cout << std::string( 40 - 7, ' ' );
		}
		else
		{
			std::cout << ip;
			if ( ip.length() < 40 )
			{
				std::cout << std::string( 40 - ip.length(), ' ' );
			}
		}
		std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Hostname Validation (RFC 1123)
	//=========================================================================

	std::cout << "--- Hostname Validation (RFC 1123) ---" << std::endl;

	const std::string_view hostnameExamples[]{
		"localhost",																  // Valid
		"example",																	  // Valid single label
		"my-server",																  // Valid with hyphen
		"web01",																	  // Valid alphanumeric
		"api-gateway-prod",															  // Valid multi-hyphen
		"a",																		  // Valid single char
		"example.com",																  // Valid (also a domain)
		"-invalid",																	  // Invalid (starts with hyphen)
		"invalid-",																	  // Invalid (ends with hyphen)
		"my_server",																  // Invalid (underscore not allowed in hostname)
		"",																			  // Invalid (empty)
		"this-label-is-way-too-long-because-it-exceeds-sixty-three-characters-limit", // Invalid (label > 63)
		"example..com"																  // Invalid (consecutive dots make empty label)
	};

	for ( const auto& hostname : hostnameExamples )
	{
		const bool isValid{ nfx::string::isValidHostname( hostname ) };
		std::cout << "  ";
		if ( hostname.empty() )
		{
			std::cout << "(empty)";
			std::cout << std::string( 75 - 7, ' ' );
		}
		else
		{
			std::cout << hostname;
			if ( hostname.length() < 75 )
			{
				std::cout << std::string( 75 - hostname.length(), ' ' );
			}
		}
		std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Domain Name Validation (RFC 1035)
	//=========================================================================

	std::cout << "--- Domain Name Validation (RFC 1035) ---" << std::endl;

	const std::string_view domainExamples[]{
		"example.com",			 // Valid
		"www.example.com",		 // Valid subdomain
		"api.v2.example.com",	 // Valid multiple subdomains
		"my-site.co.uk",		 // Valid with hyphen
		"example.museum",		 // Valid long TLD
		"xn--e1afmkfd.xn--p1ai", // Valid internationalized domain (punycode)
		"localhost",			 // Invalid (no dot, not FQDN)
		"example",				 // Invalid (no TLD)
		".example.com",			 // Invalid (starts with dot)
		"example.com.",			 // Valid (trailing dot is FQDN notation, but we accept it)
		"example..com",			 // Invalid (consecutive dots)
		"",						 // Invalid (empty)
		"-example.com",			 // Invalid (label starts with hyphen)
		"example-.com"			 // Invalid (label ends with hyphen)
	};

	for ( const auto& domain : domainExamples )
	{
		const bool isValid{ nfx::string::isDomainName( domain ) };
		std::cout << "  ";
		if ( domain.empty() )
		{
			std::cout << "(empty)";
			std::cout << std::string( 30 - 7, ' ' );
		}
		else
		{
			std::cout << domain;
			if ( domain.length() < 30 )
			{
				std::cout << std::string( 30 - domain.length(), ' ' );
			}
		}
		std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Port Number Validation (RFC 6335)
	//=========================================================================

	std::cout << "--- Port Number Validation (RFC 6335) ---" << std::endl;

	std::cout << "  Compile-time validation with templates:" << std::endl;

	// Valid port numbers
	constexpr uint16_t httpPort{ 80 };
	constexpr uint16_t httpsPort{ 443 };
	constexpr uint16_t sshPort{ 22 };
	constexpr uint16_t customPort{ 8080 };
	constexpr uint16_t maxPort{ 65535 };

	std::cout << "    HTTP port " << httpPort << " -> " << ( nfx::string::isValidPort( httpPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << std::endl;
	std::cout << "    HTTPS port " << httpsPort << " -> " << ( nfx::string::isValidPort( httpsPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << std::endl;
	std::cout << "    SSH port " << sshPort << " -> " << ( nfx::string::isValidPort( sshPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << std::endl;
	std::cout << "    Custom port " << customPort << " -> " << ( nfx::string::isValidPort( customPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << std::endl;
	std::cout << "    Max port " << maxPort << " -> " << ( nfx::string::isValidPort( maxPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << std::endl;

	// This would cause compile error (type safety):
	// constexpr uint64_t invalidPort{ 70000 };
	// nfx::string::isValidPort( invalidPort ); // static_assert failure

	std::cout << std::endl;

	//=========================================================================
	// Endpoint Parsing
	//=========================================================================

	std::cout << "--- Endpoint Parsing (Host:Port) ---" << std::endl;

	const std::string_view endpointExamples[]{
		"192.168.1.1:8080",		// Valid IPv4
		"example.com:443",		// Valid domain
		"localhost:3000",		// Valid hostname
		"[2001:db8::1]:80",		// Valid IPv6
		"[::1]:8080",			// Valid IPv6 loopback
		"[fe80::1%eth0]:22",	// Valid IPv6 with zone
		"api.example.com:8443", // Valid subdomain
		"192.168.1.1",			// Invalid (no port)
		"example.com:",			// Invalid (empty port)
		":8080",				// Invalid (empty host)
		"192.168.1.1:70000",	// Invalid (port > 65535)
		"[2001:db8::1:80",		// Invalid (missing bracket)
		"256.1.1.1:80",			// Invalid (invalid IPv4)
		"",						// Invalid (empty)
		"example.com:abc"		// Invalid (non-numeric port)
	};

	for ( const auto& endpoint : endpointExamples )
	{
		std::string_view host{};
		uint16_t port{};
		const bool parsed{ nfx::string::tryParseEndpoint( endpoint, host, port ) };

		std::cout << "  ";
		if ( endpoint.empty() )
		{
			std::cout << "(empty)";
			std::cout << std::string( 30 - 7, ' ' );
		}
		else
		{
			std::cout << endpoint;
			if ( endpoint.length() < 30 )
			{
				std::cout << std::string( 30 - endpoint.length(), ' ' );
			}
		}
		std::cout << " -> ";

		if ( parsed )
		{
			std::cout << "[OK] Host: \"" << host << "\", Port: " << port;
		}
		else
		{
			std::cout << "[FAIL] Invalid";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// URI Character Validation (RFC 3986)
	//=========================================================================

	std::cout << "--- URI Character Validation (RFC 3986) ---" << std::endl;

	std::cout << "  Reserved characters (must be percent-encoded in certain contexts):" << std::endl;
	const std::string_view reservedChars{ ":/?#[]@!$&'()*+,;=" };
	for ( const char ch : reservedChars )
	{
		std::cout << "    '" << ch << "' -> " << ( nfx::string::isURIReserved( ch ) ? "[OK] Reserved" : "[FAIL] Not reserved" ) << std::endl;
	}

	std::cout << std::endl;
	std::cout << "  Unreserved characters (safe to use without encoding):" << std::endl;
	const std::string_view unreservedChars{ "ABCabc123-._~" };
	for ( const char ch : unreservedChars )
	{
		std::cout << "    '" << ch << "' -> " << ( nfx::string::isURIUnreserved( ch ) ? "[OK] Unreserved" : "[FAIL] Not unreserved" ) << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Real-world use cases
	//=========================================================================

	std::cout << "--- Real-world Use Cases ---" << std::endl;

	// Use case 1: Validate server configuration
	std::cout << "  Use case 1: Server configuration validation" << std::endl;
	const std::string_view serverEndpoint{ "api.example.com:8443" };
	std::string_view serverHost{};
	uint16_t serverPort{};

	if ( nfx::string::tryParseEndpoint( serverEndpoint, serverHost, serverPort ) )
	{
		if ( nfx::string::isDomainName( serverHost ) || nfx::string::isValidHostname( serverHost ) )
		{
			std::cout << "    [OK] Server configuration is valid" << std::endl;
			std::cout << "      Host: " << serverHost << std::endl;
			std::cout << "      Port: " << serverPort << std::endl;
		}
	}

	std::cout << std::endl;

	// Use case 2: Network address classification
	std::cout << "  Use case 2: Network address classification" << std::endl;
	const std::string_view addresses[]{ "192.168.1.1", "2001:db8::1", "example.com" };

	for ( const auto& addr : addresses )
	{
		std::cout << "    Address: " << addr << " -> ";
		if ( nfx::string::isIPv4Address( addr ) )
		{
			std::cout << "IPv4";
		}
		else if ( nfx::string::isIPv6Address( addr ) )
		{
			std::cout << "IPv6";
		}
		else if ( nfx::string::isDomainName( addr ) )
		{
			std::cout << "Domain name";
		}
		else if ( nfx::string::isValidHostname( addr ) )
		{
			std::cout << "Hostname";
		}
		else
		{
			std::cout << "Unknown/Invalid";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// Use case 3: Connection string parsing
	std::cout << "  Use case 3: Connection string parsing" << std::endl;
	const std::string_view connections[]{ "localhost:5432", "[::1]:3306", "db.prod.internal:27017" };

	for ( const auto& conn : connections )
	{
		std::string_view dbHost{};
		uint16_t dbPort{};

		if ( nfx::string::tryParseEndpoint( conn, dbHost, dbPort ) )
		{
			std::cout << "    [OK] Connection: " << conn << std::endl;
			std::cout << "      Database host: " << dbHost << std::endl;
			std::cout << "      Database port: " << dbPort << std::endl;
		}
	}

	return 0;
}
