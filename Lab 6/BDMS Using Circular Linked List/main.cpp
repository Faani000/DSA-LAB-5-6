#include "libraries.h"

int main() {
    CircularDonorList donors;
    int choice, id, index, a, b;
    string name, group, phone;

    do {
        cout << "\n===== BLOOD DONATION MANAGEMENT SYSTEM =====\n";
        cout << "1. Display Donors\n2. Insert Donor at Head\n3. Remove Donor from Head\n";
        cout << "4. Insert Donor at Index\n5. Remove Donor at Index\n6. Swap Donors\n";
        cout << "7. Sort Donors by ID\n8. Reverse Donor Cycle\n9. Move to Next Donor\n";
        cout << "10. Check List Status\n11. Exit\nEnter your choice: ";
        if (!(cin >> choice)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) donors.Print();
        else if (choice == 2 || choice == 4) {
            cout << "Donor ID: "; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Donor name: "; getline(cin, name);
            cout << "Blood group (e.g. A+, O-): "; getline(cin, group);
            cout << "Phone: "; getline(cin, phone);
            if (choice == 2) donors.Insert(CreateDonor(id, name, group, phone));
            else {
                cout << "Index (starting from 0): "; cin >> index;
                donors.InsertAt(CreateDonor(id, name, group, phone), index);
            }
            cout << "Donor record inserted.\n";
        } else if (choice == 3 || choice == 5) {
            DonorNode* removed;
            if (choice == 3) removed = donors.Remove();
            else { cout << "Index: "; cin >> index; removed = donors.RemoveAt(index); }
            if (removed != nullptr) {
                cout << "Removed donor: " << removed->name << "\n";
                delete removed;
            } else cout << "The donor list is empty.\n";
        } else if (choice == 6) {
            cout << "First index: "; cin >> a;
            cout << "Second index: "; cin >> b;
            donors.Swap(a, b);
        } else if (choice == 7) donors.Sort();
        else if (choice == 8) donors.Reverse();
        else if (choice == 9) donors.MoveNext();
        else if (choice == 10) {
            cout << "Total donors: " << donors.Size() << "\n";
            cout << (donors.IsEmpty() ? "Donor list is empty.\n" : "Donor list is not empty.\n");
        } else if (choice != 11) cout << "Invalid choice.\n";
    } while (choice != 11);

    cout << "Program ended.\n";
    return 0;
}
