#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
struct Guard {
    string name;
    explicit Guard(string s) : name(std::move(s)) {}
    ~Guard() noexcept { cout << '~' << name << ' '; }
};
void serviceLayer() {
    Guard local("service");
    throw runtime_error("claim rejected");
}
void billingLayer() {
    Guard local("billing");
    try { serviceLayer(); }
    catch (const exception& e) {
        cout << "logged: " << e.what() << ' ';
        throw; // rethrows the same exception and preserves its dynamic type
    }
}
int main() {
    Guard mainGuard("main");
    try { billingLayer(); }
    catch (const exception& e) { cout << "user message: " << e.what() << ' '; }
    cout << "recovered\n";
}
