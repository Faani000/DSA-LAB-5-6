#ifndef DSA_LAB_PROGRAM_LIBRARIES_H
#define DSA_LAB_PROGRAM_LIBRARIES_H

#include <iostream>
#include <string>
#include <limits>
#include <utility>

using namespace std;

struct BookNode {
    int bookID;
    string title;
    BookNode* next;
};

class CircularLinkedList {
private:
    BookNode* head; // head is the last node; head->next is the first node
    int count;

    BookNode* GetNodeAt(int index) {
        if (IsEmpty()) return nullptr;
        BookNode* current = head->next;
        for (int i = 0; i < index; i++) current = current->next;
        return current;
    }

    int NormalizeIndex(int index) {
        return ((index % count) + count) % count;
    }

    void SwapData(BookNode* a, BookNode* b) {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

public:
    CircularLinkedList() { head = nullptr; count = 0; }
    bool IsEmpty() { return count == 0; }
    bool IsNotEmpty() { return count > 0; }
    int Size() { return count; }

    void Insert(BookNode* book) {
        if (book == nullptr) return;
        if (IsEmpty()) {
            head = book;
            book->next = book;
        } else {
            book->next = head->next;
            head->next = book;
        }
        count++;
    }

    BookNode* Remove() {
        if (IsEmpty()) return nullptr;
        BookNode* first = head->next;
        if (first == head) head = nullptr;
        else head->next = first->next;
        first->next = nullptr;
        count--;
        return first;
    }

    void InsertAt(BookNode* book, int index) {
        if (book == nullptr) return;
        if (count == 0) {
            head = book; book->next = book; count++; return;
        }
        if (index < 0) index = NormalizeIndex(index);
        if (index > count) index %= count;
        if (index == 0) { Insert(book); return; }
        if (index == count) {
            book->next = head->next;
            head->next = book;
            head = book;
            count++;
            return;
        }
        BookNode* previous = GetNodeAt(index - 1);
        book->next = previous->next;
        previous->next = book;
        count++;
    }

    BookNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        index = NormalizeIndex(index);
        if (index == 0) return Remove();
        BookNode* previous = GetNodeAt(index - 1);
        BookNode* target = previous->next;
        previous->next = target->next;
        if (target == head) head = previous;
        target->next = nullptr;
        count--;
        return target;
    }

    void Swap(int a, int b) {
        if (IsEmpty()) { cout << "List is empty.\n"; return; }
        a = NormalizeIndex(a); b = NormalizeIndex(b);
        if (a != b) SwapData(GetNodeAt(a), GetNodeAt(b));
        cout << "Books swapped if indexes were different.\n";
    }

    void Sort() {
        if (count < 2) return;
        BookNode* current = head->next;
        for (int i = 0; i < count - 1; i++) {
            BookNode* nextNode = current->next;
            for (int j = i + 1; j < count; j++) {
                if (current->bookID > nextNode->bookID) SwapData(current, nextNode);
                nextNode = nextNode->next;
            }
            current = current->next;
        }
        cout << "Books sorted by ID.\n";
    }

    void Reverse() {
        if (count < 2) return;
        BookNode* oldTail = head;
        BookNode* oldFirst = head->next;
        BookNode* previous = oldTail;
        BookNode* current = oldFirst;
        while (current != oldTail) {
            BookNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        oldTail->next = previous;
        head = oldFirst;
        cout << "Circular collection reversed.\n";
    }

    void Print() {
        if (IsEmpty()) { cout << "No books in the collection.\n"; return; }
        cout << "\nIndex\tBook ID\tTitle\n";
        BookNode* current = head->next;
        for (int i = 0; i < count; i++) {
            cout << i << "\t" << current->bookID << "\t" << current->title << "\n";
            current = current->next;
        }
        cout << "Total books: " << count << "\n";
    }

    void MoveNext() {
        if (IsEmpty()) { cout << "No books to display.\n"; return; }
        head = head->next;
        cout << "Current featured book: " << head->next->title << "\n";
    }

    ~CircularLinkedList() {
        while (IsNotEmpty()) delete Remove();
    }
};

BookNode* CreateBook(int id, string title);

#endif
