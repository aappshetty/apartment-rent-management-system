#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Apartment {
public:
    Apartment(const string& name, double rent) : name(name), rent(rent), rentPaid(false) {}

    virtual ~Apartment() = default;

    virtual const string& getType() const = 0;
    virtual const string& getName() const {
        return name;
    }

    virtual double getRent() const {
        return rent;
    }

    virtual void setRent(double newRent) {
        rent = newRent;
    }

    bool isRentPaid() const {
        return rentPaid;
    }

    void payRent() {
        rentPaid = true;
    }

    void clearRentPayment() {
        rentPaid = false;
    }

protected:
    string name;
    double rent;
    bool rentPaid;
};

class TWOBHK : public Apartment {
public:
    TWOBHK(const string& name, double rent) : Apartment(name, rent) {}

    const string& getType() const override {
        static const string type = "TWOBHK";
        return type;
    }
};

class THREEBHK : public Apartment {
public:
    THREEBHK(const string& name, double rent) : Apartment(name, rent) {}

    const string& getType() const override {
        static const string type = "THREEBHK";
        return type;
    }
};

class ApartmentRentManagementSystem {
public:
    void addApartment(const shared_ptr<Apartment>& apartment) {
        apartments.push_back(apartment);
    }

    void displayApartments() const {
        cout << "Apartments List:\n";
        for (const auto& apartment : apartments) {
            cout << "Type: " << apartment->getType() << ", Name: " << apartment->getName() << ", Rent: " << apartment->getRent();
            if (apartment->isRentPaid()) {
                cout << " (Rent Paid)\n";
            } else {
                cout << " (Rent Not Paid)\n";
            }
        }
    }

    void updateRent(const string& name, double newRent) {
        for (const auto& apartment : apartments) {
            if (apartment->getName() == name) {
                apartment->setRent(newRent);
                cout << "Rent updated for apartment " << name << ". New rent: " << newRent << "\n";
                return;
            }
        }
        cout << "Apartment not found: " << name << "\n";
    }

    bool isSelected(const string& name) const {
        return find(selectedApartments.begin(), selectedApartments.end(), name) != selectedApartments.end();
    }

    void selectApartment(const string& name) {
        for (const auto& apartment : apartments) {
            if (apartment->getName() == name) {
                if (!apartment->isRentPaid()) {
                    cout << "Rent for Apartment " << name << " is not paid. Please pay the rent first.\n";
                    return;
                }

                if (isSelected(name)) {
                    cout << "Apartment " << name << " is already selected.\n";
                    return;
                }

                selectedApartments.push_back(name);
                cout << "Apartment " << name << " selected.\n";
                return;
            }
        }

        cout << "Apartment not found: " << name << "\n";
    }

    void payRent(const string& name) {
        for (const auto& apartment : apartments) {
            if (apartment->getName() == name) {
                if (apartment->isRentPaid()) {
                    cout << "Rent for Apartment " << name << " is already paid.\n";
                } else {
                    apartment->payRent();
                    cout << "Rent for Apartment " << name << " is now paid.\n";
                }
                return;
            }
        }
        cout << "Apartment not found: " << name << "\n";
    }

    void clearRentPayment(const string& name) {
        for (const auto& apartment : apartments) {
            if (apartment->getName() == name) {
                if (apartment->isRentPaid()) {
                    apartment->clearRentPayment();
                    cout << "Rent payment for Apartment " << name << " is cleared.\n";
                } else {
                    cout << "Rent for Apartment " << name << " is not paid, nothing to clear.\n";
                }
                return;
            }
        }
        cout << "Apartment not found: " << name << "\n";
    }

private:
    vector<shared_ptr<Apartment>> apartments;
    vector<string> selectedApartments;
};

int main() {
    ApartmentRentManagementSystem managementSystem;

    while (true) {
        cout << "Select an option:\n";
        cout << "1. Add Apartment\n";
        cout << "2. Display Apartments\n";
        cout << "3. Update Rent\n";
        cout << "4. Select Apartment\n";
        cout << "5. Pay Rent\n";
        cout << "6. Clear Rent Payment\n";
        cout << "7. Exit\n";

        int option;
        cin >> option;
        cin.ignore(); // Clear input buffer

        if (option == 1) {
            cout << "Enter Apartment Name: ";
            string name;
            getline(cin, name);

            cout << "Enter Rent: ";
            double rent;
            cin >> rent;
            cin.ignore(); // Clear input buffer

            cout << "Apartment Type (1 for TWO-BHK, 2 for THREE-BHK): ";
            int typeOption;
            cin >> typeOption;
            cin.ignore(); // Clear input buffer

            if (typeOption == 1) {
                managementSystem.addApartment(make_shared<TWOBHK>(name, rent));
                cout << "Apartment " << name << " (TWOBHK) with Rent " << rent << " added.\n";
            } else if (typeOption == 2) {
                managementSystem.addApartment(make_shared<THREEBHK>(name, rent));
                cout << "Apartment " << name << " (THREEBHK) with Rent " << rent << " added.\n";
            } else {
                cout << "Invalid option. Try again.\n";
            }
        } else if (option == 2) {
            managementSystem.displayApartments();
        } else if (option == 3) {
            cout << "Enter Apartment Name to update rent: ";
            string name;
            getline(cin, name);

            cout << "Enter New Rent: ";
            double newRent;
            cin >> newRent;
            cin.ignore(); // Clear input buffer

            managementSystem.updateRent(name, newRent);
        } else if (option == 4) {
            cout << "Enter Apartment Name to select: ";
            string name;
            getline(cin, name);

            managementSystem.selectApartment(name);
        } else if (option == 5) {
            cout << "Enter Apartment Name to pay rent: ";
            string name;
            getline(cin, name);

            managementSystem.payRent(name);
        } else if (option == 6) {
            cout << "Enter Apartment Name to clear rent payment: ";
            string name;
            getline(cin, name);

            managementSystem.clearRentPayment(name);
        } else if (option == 7) {
            cout << "Exiting the Apartment Rent Management System.\n";
            break;
        } else {
            cout << "Invalid option. Try again.\n";
        }

        cout << "-----------------------------\n";
    }

    return 0;
}
