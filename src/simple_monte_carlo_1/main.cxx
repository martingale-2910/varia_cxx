#include <iostream>
#include <random>
#include <chrono>

const int n_paths = 10000;
const int n_steps = 100;

const double r = 0.05;
const double vol = 0.2;

const double s0 = 100;
const double k = 110;
const double ttm = 1.0;
const double dt = ttm/(n_steps + 1);

int main(int argc, char** argv) {
    std::random_device rd{};
    std::mt19937 rng{rd()};
    std::normal_distribution stdnorm{0.0, 1.0};

    auto generate_stdnorm = [&rng, &stdnorm] () -> double { return stdnorm(rng); };

    auto begin = std::chrono::steady_clock::now(); // std::chrono::steady_clock::time_point

    double s[n_paths];
    for(uint np = 0; np < n_paths; ++np) {
        s[np] = s0;
    }

    for(uint ns = 0; ns < n_steps; ++ns) {
        for(uint np = 0; np < n_paths; ++np) {
            double z = generate_stdnorm();
            s[np] = s[np]*(1 + r*dt + vol*sqrt(dt)*z);
        }
    }

    double mc_sum = 0;
    for(uint np = 0; np < n_paths; ++np) {
        mc_sum += std::max(s[np] - k, 0.0);
    }
    double mc_avg = mc_sum/n_paths;

    auto end = std::chrono::steady_clock::now();

    std::cout << "European Option MC price = " << mc_avg << std::endl;
    std::cout << "Computation duration = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}