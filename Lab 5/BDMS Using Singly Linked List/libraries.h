#ifndef DSA_LAB_PROGRAM_LIBRARIES_H
#define DSA_LAB_PROGRAM_LIBRARIES_H

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

DonorNode* CreateDonor(int id, string name, string group, string phone);

#endif
