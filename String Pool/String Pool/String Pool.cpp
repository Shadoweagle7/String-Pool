// String Pool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <concepts>

#define STATIC_CLASS(x)\
    x ## () = delete;\
    x ## (const x &) = delete;\
    x ## (x &&) = delete;

class string_pool {
public:
    struct allocator;
private:
    static std::set<std::string> pool;
public:

    STATIC_CLASS(string_pool)

    struct allocator {
    private:
        std::allocator<std::string> internal_allocator;
    public:
        using value_type = std::allocator<std::string>::value_type;
        using size_type = std::allocator<std::string>::size_type;
        using difference_type = std::allocator<std::string>::difference_type;
        using propagate_on_container_move_assignment =
            std::allocator<std::string>::propagate_on_container_move_assignment;

        constexpr allocator() noexcept {}
        constexpr allocator(const allocator &a) noexcept {}
        constexpr allocator(allocator &&a) noexcept {}

        // address() is deprecated in C++17, removed in C++20

        [[nodiscard]] /* constexpr C++20 */ value_type *allocate(size_t n) {
            return this->internal_allocator.allocate(n);
        }

        /* constexpr C++20 */ void deallocate(value_type *p, size_t n) {
            this->internal_allocator.deallocate(p, n);
        }

        // max_size(), construct() and destroy() are deprecated in C++17, removed in C++20

        bool operator==(const allocator &other) const noexcept {
            return true;
        }

        bool operator!=(const allocator &other) const noexcept {
            return false;
        }

        /* constexpr (waiting for complete C++20 support, MSVC) */  ~allocator() {}
    };

    static size_t size() {
        return pool.size();
    }

    template<class... argv>
    static const char *make(argv&&... args) requires std::constructible_from<std::string, argv...> {
        return pool.emplace(std::forward<argv>(args)...).first->c_str();
    }
};

std::set<std::string> string_pool::pool;

int main(int argc, const char *argv[]) {
    const char *test = string_pool::make("boing");

    std::cout << "string_pool::size(): " << string_pool::size() << "\n";

    const char *test2 = string_pool::make("boing");

    std::cout << "string_pool::size(): " << string_pool::size() << "\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
