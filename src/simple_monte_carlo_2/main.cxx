#include <iostream>
#include <random>
#include <chrono>
#include <valarray>
#include <algorithm>
#include <numeric>

const int n_paths = 10000;
const int n_steps = 100;

const double r = 0.05;
const double vol = 0.2;

const double s0 = 100;
const double k = 110;
const double ttm = 1.0;
const double dt = ttm/(n_steps + 1);

using vecd = std::valarray<double>;

int main(int argc, char** argv) {
    std::random_device rd{};
    std::mt19937 rng{rd()};
    std::normal_distribution stdnorm{0.0, 1.0};

    auto generate_stdnorm = [&rng, &stdnorm] () -> double { return stdnorm(rng); };

    auto begin = std::chrono::steady_clock::now();

    vecd s(s0, n_paths);
    vecd z(n_paths);
    for(uint ns = 0; ns < n_steps; ++ns) {
        std::generate(std::begin(z), std::end(z), generate_stdnorm);
        s = s*(1 + r*dt + vol*sqrt(dt)*z);
    }

    auto compute_payoff = [] (double si) -> double { return std::max(si - k, 0.0); };
    double mc_avg = s.apply(compute_payoff).sum()/s.size();

    auto end = std::chrono::steady_clock::now();

    std::cout << "European Option MC price = " << mc_avg << std::endl;
    std::cout << "Computation duration = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}