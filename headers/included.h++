

#if not defined(_INCLUDED_)

    #define _INCLUDED_

    #if defined(_WIN16) or defined(_WIN32) or defined(_WIN64) or defined(__WIN32__) or defined(__TOS_WIN__) or defined(__WINDOWS__)


        #if not defined(crap_os)
            #define crap_os
        #endif
        
        #if not defined(_WIN32_WINNT)
            #define _WIN32_WINNT 0x0600
        #endif

        #if not defined(_WINSOCK2API_)
            #include <WinSock2.h>
        #endif

        #if not defined(_WS2TCPIP_H_)
            #include <WS2tcpip.h>
        #endif

        #if not defined(_INC_CONIO)
            #include <conio.h>
        #endif

        #if not defined(__IPHLPAPI_H__)
            #include <iphlpapi.h>
        #endif

        #if not defined(_WINDOWS_)
            #include <Windows.h>
        #endif

        #if not defined(_BASETSD_H_)
            #include <BaseTsd.h>
            typedef SSIZE_T ssize_t;
        #endif

        #if defined(_WIN32) || defined(_WIN64)
            #include <cstddef>
            typedef ptrdiff_t ssize_t;
        #endif

        #pragma comment(lib, "ws2_32.lib")
        #pragma comment(lib, "iphlpapi.lib")


        #define get_string(crap_string)\
            [&]() -> std::string {\
                const wchar_t* crap_str = crap_string;\
                std::string the_answer;\
                while(*crap_str) {\
                    the_answer.push_back(static_cast<char>(*crap_str));\
                }\
                return the_answer;\
            }()


        // For dealing with adapters
        #define ifaddrs_adapter_type PIP_ADAPTER_ADDRESSES
        #define ifaddrs_get_adapter_name(this_adapter) wchar_to_string(this_adapter->FriendlyName)
        #define ifaddrs_get_next_adapter(this_adapter) this_adapter->Next
        #define ifaddrs_pull_adapter_address(this_adapter) this_adapter->FirstUnicastAddress
        #define ifaddrs_free_adapters(these_adapters) std::free(these_adapters)


        // For dealing with addresses
        #define ifaddrs_address_type PIP_ADAPTER_UNICAST_ADDRESS
        #define ifaddrs_get_next_address(this_address) this_address->Next
        #define ifaddrs_get_address_sockaddr(this_address) this_address->Address.lpSockaddr
        #define ifaddrs_get_address_sockaddrlen(this_address) this_address->Address.iSockaddrLength
        #define ifaddrs_get_address_family(this_address) this_address->Address.lpSockaddr->sa_family



        // For dealing with sockets
        #define socket_error WSAGetLastError()
        #define socket_type SOCKET
        #define socket_family_type int
        #define invalid_socket INVALID_SOCKET
        #define valid_socket(this_socket) (this_socket != INVALID_SOCKET)
        #define close_socket(this_socket) closesocket(this_socket)
        #define sys_slash "\\"
        #define get_socket_error() WSAGetLastError()

    #else

        #if not defined(unix_os)
            #define unix_os
        #endif

        #if defined(__APPLE__) or defined(__APPLE_CC__)
            #define mac_os
        #else
            #define linux_os
        #endif

        #if (defined(mac_os) and not defined(_UNISTD_H_)) or (defined(linux_os) and not defined(_UNISTD_H))
            #include <unistd.h>
        #endif


        #if (defined(mac_os) and not defined(_SYS_IOCTL_H_)) or (defined(linux_os) and not defined(_SYS_IOCTL_H))
            #include <sys/ioctl.h>
        #endif

        #if (defined(mac_os) and not defined(_UNISTD_H_)) or (defined(linux_os) and not defined(_UNISTD_H))
            #include <unistd.h>
        #endif

        #if (defined(mac_os) and not defined(_IFADDRS_H_)) or (defined(linux_os) and not defined(_IFADDRS_H))
            #include <ifaddrs.h>
        #endif

        #if (defined(mac_os) and not defined(_SYS_SOCKET_H_)) or (defined(linux_os) and not defined(_SYS_SOCKET_H))
            #include <sys/socket.h>
        #endif

        #if (defined(mac_os) and not defined(_NETDB_H_)) or (defined(linux_os) and not defined(_NETDB_H))
            #include <netdb.h>
        #endif

        #if (defined(mac_os) and not defined(_LIBCPP_ERRNO_H)) or (defined(linux_os) and not defined(_ERRNO_H))
            #include <errno.h>
        #endif

        
        // Check the linux header checkers

        #if (defined(mac_os) and not defined(_ARPA_INET_H_)) or (defined(linux_os) and not defined(_ARPA_INET_H))
            #include <arpa/inet.h>
        #endif

        #if (defined(mac_os) and not defined(_SYS_FCNTL_H_)) or (defined(linux_os) and not defined(_FCNTL_H_))
            #include <sys/fcntl.h>
        #endif


        // For dealing with adapters
        #define ifaddrs_adapter_type struct ifaddrs*
        #define ifaddrs_get_adapter_name(this_adapter) std::string(this_adapter->ifa_name)
        #define ifaddrs_get_next_adapter(this_adapter) this_adapter->ifa_next
        #define ifaddrs_pull_adapter_address(this_adapter) this_adapter
        #define ifaddrs_free_adapters(these_adapters) freeifaddrs(these_adapters)
        
        
        // For dealing with addresses
        #define ifaddrs_address_type struct ifaddrs*
        #define ifaddrs_get_next_address(this_address) NULL
        #define ifaddrs_get_address_sockaddr(this_address) this_address->ifa_addr
        #define ifaddrs_get_address_sockaddrlen(this_address) sizeof(*this_address->ifa_addr)
        #define ifaddrs_get_address_family(this_address) this_address->ifa_addr->sa_family
        
        
        // For dealing with sockets
        #define socket_error errno
        #define socket_type int
        #if defined(mac_os)
            #define socket_family_type unsigned char
        #else
            #define socket_family_type unsigned short
        #endif
        #define invalid_socket -1
        #define valid_socket(this_socket) (this_socket >= 0)
        #define close_socket(this_socket) close(this_socket)
        #define sys_slash "/"
        #define get_socket_error() errno

    #endif



    #if (defined(mac_os) and not defined(_LIBCPP_CTIME)) or (defined(linux_os) and not defined(_GLIBCXX_CTIME)) or (defined(crap_os) and not defined(_CTIME_))
        #include <ctime>
    #endif

    #if (defined(mac_os) and not defined(_LIBC_CSTRING)) or (defined(linux_os) and not defined(_GLIBCXX_STRING)) or (defined(crap_os) and not defined(_CSTRING_))
        #include <cstring>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_STRING)) or (defined(linux_os) and not defined(_GLIBCXX_STRING)) or (defined(crap_os) and not defined(_STRING_))
        #include <string>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_VECTOR)) or (defined(linux_os) and not defined(_GLIBCXX_VECTOR)) or (defined(crap_os) and not defined(_VECTOR_))
        #include <vector>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_MAP)) or (defined(linux_os) and not defined(_GLIBCXX_MAP)) or (defined(crap_os) and not defined(_MAP_))
        #include <map>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_SET)) or (defined(linux_os) and not defined(_GLIBCXX_SET)) or (defined(crap_os) and not defined(_SET_))
        #include <set>
    #endif

    #if (defined(mac_os) and not defined(_SYS_IOCTL_H_)) or (defined(linux_os) and not defined(_SYS_IOCTL_H))
        #include <sys/ioctl.h>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_IOSTREAM)) or (defined(linux_os) and not defined(_GLIBCXX_IOSTREAM)) or (defined(crap_os) and not defined(_IOSTREAM_))
        #include <iostream>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_SSTREAM)) or (defined(linux_os) and not defined(_GLIBCXX_SSTREAM)) or (defined(crap_os) and not defined(_SSTREAM_))
        #include <sstream>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_REGEX)) or (defined(linux_os) and not defined(_GLIBCXX_REGEX)) or (defined(crap_os) and not defined(_REGEX_))
        #include <regex>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_FILESYSTEM)) or (defined(linux_os) and not defined(_GLIBCXX_FILESYSTEM)) or (defined(crap_os) and not defined(_FILESYSTEM_))
        #include <filesystem>
    #endif

    #if (defined(mac_os) and not defined(_LIBCPP_FSTREAM)) or (defined(linux_os) and not defined(_GLIBCXX_FSTREAM)) or (defined(crap_os) and not defined(_FSTREAM_))
        #include <fstream>
    #endif

    #include <memory>




    #include <openssl/crypto.h>
    #include <openssl/x509.h>
    #include <openssl/pem.h>
    #include <openssl/ssl.h>
    #include <openssl/err.h>



    #define is ==
    #define less <
    #define greater >
    #define than
    #define IN_RANGE_INCLUDE(a, b, c) (a <= b and b <= c)
    #define CASE_DIFF 'a' - 'A'
    #define prev -1
    #define NOT !=
    #define null NULL
    #define secure_socket_type SSL*
    #define secure_socket_context_type SSL_CTX*
    #define invalid_secure_socket null
    #define invalid_context null
    
    #define valid_secure_socket(the_socket) (the_socket != invalid_secure_socket)
    #define valid_context(the_context) (the_context != invalid_context)


    #define buffer_size 100
    #define kilo_byte 1024
    #define four_kilo_bytes 4096
    #define eight_kilo_bytes 8192



    #if not defined(AI_ALL)
        #define AI_ALL 0x0100
    #endif


    #define response_size 32768
    #define byte char

    #define DEFAULT_HOST "LOCALHOST"
    #define DEFAULT_PORT "8080"
    #define TIMEOUT 5.0

        #if defined(crap_os)

        inline std::string wchar_to_string(const wchar_t* wstr) {
            if (!wstr) return std::string();
            int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
            std::string strTo(size_needed, 0);
            WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &strTo[0], size_needed, NULL, NULL);
            strTo.pop_back(); // Remove the null terminator
            return strTo;
        }

        #endif


#endif