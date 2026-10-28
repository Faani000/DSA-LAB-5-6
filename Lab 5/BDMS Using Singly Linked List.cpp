#include <iostream>
#include <string>
#include <limits>
#include <utility>
using namespace std;

struct DonorNode {
    int donorID;
    string name;
    string bloodGroup;
    string phone;
    DonorNode* next;
};

class DonorList {
private:
    DonorNode* head;
    int count;

    DonorNode* GetNodeAt(int index) {
        DonorNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++)
            current = current->next;
        return current;
    }

    void SwapData(DonorNode* a, DonorNode* b) {
        swap(a->donorID, b->donorID);
        swap(a->name, b->name);
        swap(a->bloodGroup, b->bloodGroup);
        swap(a->phone, b->phone);
    }

public:
    DonorList() { head = nullptr; count = 0; }
    bool IsEmpty() { return head == nullptr; }
    bool IsNotEmpty() { return head != nullptr; }
    int Size() { return count; }

    void Insert(DonorNode* donor) {
        if (donor == nullptr) return;
        donor->next = head;
        head = donor;
        count++;
    }

    DonorNode* Remove() {
        if (IsEmpty()) return nullptr;
        DonorNode* donor = head;
        head = head->next;
        donor->next = nullptr;
        count--;
        return donor;
    }

    void InsertAt(DonorNode* donor, int index) {
        if (donor == nullptr) return;
        if (index < 0) index = 0;
        if (index > count) index = count;
        if (index == 0) { Insert(donor); return; }
        DonorNode* previous = GetNodeAt(index - 1);
        donor->next = previous->next;
        previous->next = donor;
        count++;
    }

    DonorNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        if (index < 0) index = 0;
        if (index >= count) index = count - 1;
        if (index == 0) return Remove();
        DonorNode* previous = GetNodeAt(index - 1);
        DonorNode* donor = previous->next;
        previous->next = donor->next;
        donor->next = nullptr;
        count--;
        return donor;
    }

    void Swap(int a, int b) {
        if (a < 0 || a >= count || b < 0 || b >= count) {
            cout << "Invalid index.\n"; return;
        }
        if (a != b) SwapData(GetNodeAt(a), GetNodeAt(b));
        cout << "Donor records swapped if indexes were different.\n";
    }

    void Sort() {
        for (DonorNode* i = head; i != nullptr; i = i->next)
            for (DonorNode* j = i->next; j != nullptr; j = j->next)
                if (i->donorID > j->donorID) SwapData(i, j);
        cout << "Donors sorted by donor ID.\n";
    }

    void Reverse() {
        DonorNode* previous = nullptr;
        DonorNode* current = head;
        while (current != nullptr) {
            DonorNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        head = previous;
        cout << "Donor list reversed.\n";
    }

    void Print() {
        if (IsEmpty()) { cout << "No donor records found.\n"; return; }
        cout << "\nIndex\tID\tName\tBlood Group\tPhone\n";
        DonorNode* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << index++ << "\t" << current->donorID << "\t"
                 << current->name << "\t" << current->bloodGroup << "\t\t"
                 << current->phone << "\n";
            current = current->next;
        }
        cout << "Total donors: " << count << "\n";
    }

    ~DonorList() { while (IsNotEmpty()) delete Remove(); }
};

DonorNode* CreateDonor(int id, string name, string group, string phone) {
    DonorNode* donor = new DonorNode;
    donor->donorID = id;
    donor->name = name;
    donor->bloodGroup = group;
    donor->phone = phone;
    donor->next = nullptr;
    return donor;
}

int main() {
    DonorList donors;
    int choice, id, index, a, b;
    string name, group, phone;

    do {
        cout << "\n===== BLOOD DONATION MANAGEMENT SYSTEM =====\n";
        cout << "1. Display Donors\n2. Insert Donor at Head\n3. Remove Donor from Head\n";
        cout << "4. Insert Donor at Index\n5. Remove Donor at Index\n6. Swap Donors\n";
        cout << "7. Sort Donors by ID\n8. Reverse Donor List\n9. Check List Status\n10. Exit\n";
        cout << "Enter your choice: ";
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
        else if (choice == 9) {
            cout << "Total donors: " << donors.Size() << "\n";
            cout << (donors.IsEmpty() ? "Donor list is empty.\n" : "Donor list is not empty.\n");
        } else if (choice != 10) cout << "Invalid choice.\n";
    } while (choice != 10);

    cout << "Program ended.\n";
    return 0;
}
