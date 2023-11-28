#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <string>
#include <type_traits>
  
/*! \addtogroup <main_group> Print Ip
 *
 *  @{
 */
namespace print_ip
{

#pragma region containers

    /*!
     *  \addtogroup <Container_group> Is STL Container
     *  @{
     */

    //! `type_traits` to verify that the type is a contener
    namespace is_stl_container_impl
    {
        template <typename T>
        struct is_stl_container : std::false_type
        {
        };
        template <typename T, std::size_t N>
        struct is_stl_container<std::array<T, N>> : std::true_type
        {
        };
        template <typename... Args>
        struct is_stl_container<std::vector<Args...>> : std::true_type
        {
        };
        template <typename... Args>
        struct is_stl_container<std::list<Args...>> : std::true_type
        {
        };
    }
    /*! @} End of Doxygen Groups*/

    template <typename T>
    struct is_stl_container
    {
        static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
    };

    /*!
     * @brief Print ip addres from STL containers
     *
     * @tparam T type must be array/vector/list
     * @param ip IP address to be printed
     */
    template <typename T, std::enable_if_t<is_stl_container<T>::value, bool> = true>
    void Print_ip(T ip)
    {
        std::string str = "";
        for (const auto &item : ip)
        {
            str += std::to_string(item) + ".";
        }

        str.pop_back();
        std::cout << str << std::endl;
    }
#pragma endregion

#pragma region integer

    /*!
     * @brief Print ip addres from Integral types
     *
     * @tparam T type must be int8_t/int16_t/int32_t/int64_t
     * @param ip IP address to be printed
     */
    template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    void Print_ip(T ip)
    {
        std::string str = "";
        const auto byte_p = reinterpret_cast<const std::byte *>(&ip);

        constexpr size_t kSizeOfValue{sizeof(ip)};
        for (auto i = static_cast<int>(kSizeOfValue - 1); i >= 0; i--)
        {
            std::cout << static_cast<int>(byte_p[i]);
            std::cout << ((i == 0) ? '\n' : '.');
        }
    }

#pragma endregion

#pragma region string

    /*!
     *  \addtogroup <String_group> Is String
     *  @{
     */

    //! `type_traits` to verify that the type is a string
    namespace is_string_impl
    {
        template <typename T, typename = void>
        struct is_string
        {
            static const bool value = false;
        };

        template <class T, class Traits, class Alloc>
        struct is_string<std::basic_string<T, Traits, Alloc>, void>
        {
            static const bool value = true;
        };

        template <class T, template <typename, typename, typename> class STRING>
        struct is_string<T, STRING<T, std::char_traits<T>, std::allocator<T>>>
        {
            static const bool value = true;
        };
    }
    /*! @} End of Doxygen Groups*/

    /*!
     * @brief Print ip addres from std::string
     *
     * @tparam T type must be std::string
     * @param ip IP address to be printed
     */
    template <typename T, std::enable_if_t<is_string_impl::is_string<T>::value, bool> = true>
    void Print_ip(T ip)
    {
        std::cout << ip << std::endl;
    }

#pragma endregion

#pragma region tuple

    /*!
     *  \addtogroup <Tuple_group> Is Tuple
     *  @{
     */

    //! `type_traits` to verify that the type is a tuple
    namespace is_tuple_impl
    {
        template <typename T>
        struct is_tuple : std::false_type
        {
        };
        template <typename... Args>
        struct is_tuple<std::tuple<Args...>> : std::true_type
        {
        };
    }
    /*! @} End of Doxygen Groups*/

    template <typename T>
    struct is_tuple
    {
        static constexpr bool const value = is_tuple_impl::is_tuple<std::decay_t<T>>::value;
    };

    /*
     * @brief Convert std::tuple to std::vector
     *
     * @tparam Tuple type std::tuple
     * @tparam std::decay_t<Tuple>>>
     * @param tuple is a source std::tuple
     * @return std::vector<T>
     */
    template <class Tuple, class T = std::decay_t<std::tuple_element_t<0, std::decay_t<Tuple>>>>
    std::vector<T> to_vector(Tuple &&tuple)
    {
        return std::apply([](auto &&...elems)
                          { return std::vector<T>{std::forward<decltype(elems)>(elems)...}; },
                          std::forward<Tuple>(tuple));
    }

    /*!
     * @brief Print tuple
     *
     * @tparam T - is a type "tuple"
     * @param ip
     */
    template <typename T, std::enable_if_t<is_tuple<T>::value, bool> = true>
    void Print_ip(T ip)
    {
        auto vec = to_vector(ip);
        Print_ip(vec);
    }

#pragma endregion
}
/*! @} */