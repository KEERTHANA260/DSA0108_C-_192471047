#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
class Bill { public: virtual ~Bill() = default; virtual double total() const = 0; };
class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
};
class OPBill : public Bill {
    double amount;
public: explicit OPBill(double a) : amount(a) {} double total() const override { return amount; }
};
class SelfPay : public Payer {
public: double amountCovered(const Bill& b) const override { return b.total(); }
    string name() const override { return "SelfPay"; }
};
class Insurance : public Payer {
    double limit, copayPercent;
public:
    Insurance(double l, double c) : limit(l), copayPercent(c) {}
    double amountCovered(const Bill& b) const override {
        return min(limit, b.total() * (1.0 - copayPercent / 100.0));
    }
    string name() const override { return "Insurance"; }
};
class GovernmentScheme : public Payer {
    double packageRate;
public:
    explicit GovernmentScheme(double r) : packageRate(r) {}
    double amountCovered(const Bill& b) const override { return min(b.total(), packageRate); }
    string name() const override { return "GovernmentScheme"; }
};
class CorporatePayer : public Payer {
public:
    double amountCovered(const Bill& b) const override { return b.total() * 0.80; }
    string name() const override { return "CorporatePayer"; }
};
int main() {
    OPBill bill(10000);
    vector<unique_ptr<Payer>> payers;
    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(8000, 20));
    payers.push_back(make_unique<GovernmentScheme>(6000));
    payers.push_back(make_unique<CorporatePayer>());
    for (const auto& p : payers)
        cout << p->name() << " covers: " << p->amountCovered(bill) << '\n';
}
