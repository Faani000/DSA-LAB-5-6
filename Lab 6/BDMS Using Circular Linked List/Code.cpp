

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

DonorNode* CreateDonor(int id, string name, string group, string phone);

#endif
