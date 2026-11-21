#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
class BillingError : public runtime_error { public: using runtime_error::runtime_error; };
class InvalidCharge : public BillingError { public: using BillingError::BillingError; };
class ClaimError : public BillingError { public: using BillingError::BillingError; };
class UnknownPackage : public BillingError { public: using BillingError::BillingError; };
class MissingPatient : public BillingError { public: using BillingError::BillingError; };
double validateCharge(double amount) {
    if (amount < 0) throw InvalidCharge("negative charge");
    return amount;
}
void validateClaim(double billed, double cover) {
    if (billed > cover) throw ClaimError("claim exceeds cover");
}
void validatePackage(const string& code) {
    if (code != "BASIC" && code != "PREMIUM") throw UnknownPackage("unknown package: " + code);
}
void requirePatient(bool found) {
    if (!found) throw MissingPatient("patient record not found");
}
int main() {
    try { validateCharge(-20); }
    catch (const BillingError& e) { cout << "Billing error: " << e.what() << '\n'; }
    try { validateClaim(7000, 5000); }
    catch (const BillingError& e) { cout << "Billing error: " << e.what() << '\n'; }
    try { validatePackage("UNKNOWN"); }
    catch (const BillingError& e) { cout << "Billing error: " << e.what() << '\n'; }
    try { requirePatient(false); }
    catch (const BillingError& e) { cout << "Billing error: " << e.what() << '\n'; }
    cout << "Destructors should be noexcept; allocation failures use std::bad_alloc.\n";
}
