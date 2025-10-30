#include "hippo_random.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    cout << "Testing normal distribution generator" << endl;
    for (int i = 0; i < 10; i++) {
        normal_dist nd(0.0, 1.0);
        double val = nd.generate();
        cout << val << endl;
    }
    cout << "Testing uniform distribution generator" << endl;
    for (int i = 0; i < 10; i++) {
        uniform_dist ud(0.0, 1.0);
        double val = ud.generate();
        cout << val << endl;
    }
    cout << "Testing uniform distribution (int) generator" << endl;
    for (int i = 0; i < 10; i++) {
        uniform_dist ud(0, 10);
        double val = ud.generate();
        cout << val << endl;
    }
    cout << "Testing uniform distribution (int) generator (vector)" << endl;
    auto v = uniform_dist<int>(0, 10).generate_uniform_dist_vector(5);
    for (const auto &val : v) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Testing random permutation generator" << endl;
    auto rp = random_permutation(10).generate(5);
    for (const auto &val : rp) {
        cout << val << " ";
    }
    cout << "Testing double generation of [2,4]" << endl;
    cout << uniform_dist<double>(2, std::nextafter(4, std::numeric_limits<double>::max())).generate() << endl;
    return 0;
}