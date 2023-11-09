#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>

// Utility wrappers around standard functional operations on containers
namespace func_utils {
    template<template<typename...> typename Container, typename Content, typename Predicate, typename = std::enable_if_t<std::is_same<std::invoke_result_t<Predicate, Content&>, bool>::value>>
    Container<Content> filter(Container<Content> container, Predicate &p) {
        Container<Content> results;
        std::copy_if(container.begin(), container.end(), std::back_inserter(results), p);
        return results;
    };

    template<template<typename...> typename Container, typename Content, typename Operator>
    Content accumulate(Container<Content> container, Content init, Operator op) {
        return std::accumulate(container.begin(), container.end(), init, op);
    };

    template<template<typename...> typename Container, typename Content, typename UniFunc, typename Result = std::invoke_result_t<UniFunc, Content&>>
    Container<Result> transform(Container<Content> &container, UniFunc &f) {
        Container<Result> result(container.size());
        std::transform(container.begin(), container.end(), result.begin(), f);
        return result;
    };

    template<template<typename...> typename Container1, typename Content1, template<typename...> typename Container2, typename Content2, typename BiFunc, typename Result = typename std::invoke_result_t<BiFunc, Content1&, Content2&>>
    Container1<Result> transform(Container1<Content1> container1, Container2<Content2> container2, BiFunc &f) {
        Container1<Result> result(container1.size());
        std::transform(container1.begin(), container1.end(), container2.begin(), result.begin(), f);
        return result;
    };

    template<template<typename...> typename Container, typename Content, typename UniFunc>
    void for_each(Container<Content> &container, UniFunc &f) {
        std::for_each(container.begin(), container.end(), f);
    };
};

int main() {
    std::vector<double> vec{1, 2, 3, 4};

    auto add_one = [] (double val) -> double { return val + 1; };
    auto vec2 = func_utils::transform(vec, add_one);

    auto print_contents = [] (double val) -> void { std::cout << val << std::endl;};
    func_utils::for_each(vec2, print_contents);

    auto sum = [] (double acc, double val) -> double { return acc + val; };
    auto vec_sum = func_utils::accumulate(vec, 0.0, sum);
    std::cout << vec_sum << std::endl;
    return 0;
};