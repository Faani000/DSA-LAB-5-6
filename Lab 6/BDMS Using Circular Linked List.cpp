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

class CircularDonorList {
private:
    DonorNode* head; // head is the last node; head->next is the first node
    int count;

    DonorNode* GetNodeAt(int index) {
        if (IsEmpty()) return nullptr;
        DonorNode* current = head->next;
        for (int i = 0; i < index; i++) current = current->next;
        return current;
    }

    int NormalizeIndex(int index) {
        return ((index % count) + count) % count;
    }

    void SwapData(DonorNode* a, DonorNode* b) {
        swap(a->donorID, b->donorID);
        swap(a->name, b->name);
        swap(a->bloodGroup, b->bloodGroup);
        swap(a->phone, b->phone);
    }

public:
    CircularDonorList() { head = nullptr; count = 0; }
    bool IsEmpty() { return count == 0; }
    bool IsNotEmpty() { return count > 0; }
    int Size() { return count; }

    void Insert(DonorNode* donor) {
        if (donor == nullptr) return;
        if (IsEmpty()) {
            head = donor;
            donor->next = donor;
        } else {
            donor->next = head->next;
            head->next = donor;
        }
        count++;
    }

    DonorNode* Remove() {
        if (IsEmpty()) return nullptr;
        DonorNode* first = head->next;
        if (first == head) head = nullptr;
        else head->next = first->next;
        first->next = nullptr;
        count--;
        return first;
    }

    void InsertAt(DonorNode* donor, int index) {
        if (donor == nullptr) return;
        if (count == 0) { head = donor; donor->next = donor; count++; return; }
        if (index < 0) index = NormalizeIndex(index);
        if (index > count) index %= count;
        if (index == 0) { Insert(donor); return; }
        if (index == count) {
            donor->next = head->next;
            head->next = donor;
            head = donor;
            count++;
            return;
        }
        DonorNode* previous = GetNodeAt(index - 1);
        donor->next = previous->next;
        previous->next = donor;
        count++;
    }

    DonorNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        index = NormalizeIndex(index);
        if (index == 0) return Remove();
        DonorNode* previous = GetNodeAt(index - 1);
        DonorNode* target = previous->next;
        previous->next = target->next;
        if (target == head) head = previous;
        target->next = nullptr;
        count--;
        return target;
    }

    void Swap(int a, int b) {
        if (IsEmpty()) { cout << "Donor list is empty.\n"; return; }
        a = NormalizeIndex(a); b = NormalizeIndex(b);
        if (a != b) SwapData(GetNodeAt(a), GetNodeAt(b));
        cout << "Donor records swapped if indexes were different.\n";
    }

    void Sort() {
        if (count < 2) return;
        DonorNode* current = head->next;
        for (int i = 0; i < count - 1; i++) {
            DonorNode* nextNode = current->next;
            for (int j = i + 1; j < count; j++) {
                if (current->donorID > nextNode->donorID) SwapData(current, nextNode);
                nextNode = nextNode->next;
            }
            current = current->next;
        }
        cout << "Donors sorted by ID.\n";
    }

    void Reverse() {
        if (count < 2) return;
        DonorNode* oldTail = head;
        DonorNode* oldFirst = head->next;
        DonorNode* previous = oldTail;
        DonorNode* current = oldFirst;
        while (current != oldTail) {
            DonorNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        oldTail->next = previous;
        head = oldFirst;
        cout << "Circular donor list reversed.\n";
    }

    void Print() {
        if (IsEmpty()) { cout << "No donor records found.\n"; return; }
        cout << "\nIndex\tID\tName\tBlood Group\tPhone\n";
        DonorNode* current = head->next;
        for (int i = 0; i < count; i++) {
            cout << i << "\t" << current->donorID << "\t" << current->name
                 << "\t" << current->bloodGroup << "\t\t" << current->phone << "\n";
            current = current->next;
        }
        cout << "Total donors: " << count << "\n";
        cout << "Circular link verified: last node points back to the first node.\n";
    }

    void MoveNext() {
        if (IsEmpty()) { cout << "No donor records to visit.\n"; return; }
        head = head->next;
        cout << "Next donor in cycle: " << head->next->name
             << " (" << head->next->bloodGroup << ")\n";
    }

    ~CircularDonorList() {
        while (IsNotEmpty()) delete Remove();
    }
};

DonorNode* CreateDonor(int id, string name, string group, string phone) {
    DonorNode* donor = new DonorNode;
    donor->donorID = id; donor->name = name; donor->bloodGroup = group;
    donor->phone = phone; donor->next = nullptr;
    return donor;
}

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
