#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Bill {
protected:
    string patient;
public:
    explicit Bill(string p) : patient(std::move(p)) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual void print() const { cout << type() << " " << patient << ": " << total() << '\n'; }
};
class OutPatientBill : public Bill {
    double consultation, tests;
public:
    OutPatientBill(string p, double c, double t) : Bill(std::move(p)), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OP"; }
};
class InPatientBill : public Bill {
    int days; double perDay, procedure;
public:
    InPatientBill(string p, int d, double rate, double proc) : Bill(std::move(p)), days(d), perDay(rate), procedure(proc) {}
    double total() const override { return days * perDay + procedure; }
    string type() const override { return "IP"; }
};
class DayCareBill : public Bill {
    double packagePrice;
public:
    DayCareBill(string p, double price) : Bill(std::move(p)), packagePrice(price) {}
    double total() const override { return packagePrice; }
    string type() const override { return "DayCare"; }
};
class EmergencyBill : public Bill {
    double baseCharge, hourlyCharge; int hours;
public:
    EmergencyBill(string p, double base, double hourly, int h) : Bill(std::move(p)), baseCharge(base), hourlyCharge(hourly), hours(h) {}
    double total() const override { return baseCharge + hourlyCharge * hours; }
    string type() const override { return "Emergency"; }
};
int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatientBill>("Ravi", 500, 1200));
    bills.push_back(make_unique<InPatientBill>("Meena", 3, 2500, 40000));
    bills.push_back(make_unique<DayCareBill>("Arun", 18000));
    bills.push_back(make_unique<EmergencyBill>("Sara", 2000, 750, 4));
    double grandTotal = 0;
    for (const auto& bill : bills) { bill->print(); grandTotal += bill->total(); }
    cout << "Day total: " << grandTotal << '\n';
}
