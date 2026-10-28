

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

class LinkedList {
private:
    BookNode* head;
    int count;

    BookNode* GetNodeAt(int index) {
        BookNode* current = head;
        for (int i = 0; i < index && current != nullptr; i++)
            current = current->next;
        return current;
    }

    void SwapData(BookNode* a, BookNode* b) {
        swap(a->bookID, b->bookID);
        swap(a->title, b->title);
    }

public:
    LinkedList() {
        head = nullptr;
        count = 0;
    }

    bool IsEmpty() { return head == nullptr; }
    bool IsNotEmpty() { return head != nullptr; }
    int Size() { return count; }

    void Insert(BookNode* book) {
        if (book == nullptr) return;
        book->next = head;
        head = book;
        count++;
    }

    BookNode* Remove() {
        if (IsEmpty()) return nullptr;
        BookNode* book = head;
        head = head->next;
        book->next = nullptr;
        count--;
        return book;
    }

    void InsertAt(BookNode* book, int index) {
        if (book == nullptr) return;
        if (index < 0) index = 0;
        if (index > count) index = count;
        if (index == 0) {
            Insert(book);
            return;
        }
        BookNode* previous = GetNodeAt(index - 1);
        book->next = previous->next;
        previous->next = book;
        count++;
    }

    BookNode* RemoveAt(int index) {
        if (IsEmpty()) return nullptr;
        if (index < 0) index = 0;
        if (index >= count) index = count - 1;
        if (index == 0) return Remove();

        BookNode* previous = GetNodeAt(index - 1);
        BookNode* book = previous->next;
        previous->next = book->next;
        book->next = nullptr;
        count--;
        return book;
    }

    void Swap(int firstIndex, int secondIndex) {
        if (firstIndex < 0 || firstIndex >= count ||
            secondIndex < 0 || secondIndex >= count) {
            cout << "Invalid index.\n";
            return;
        }
        if (firstIndex == secondIndex) return;
        SwapData(GetNodeAt(firstIndex), GetNodeAt(secondIndex));
    }

    void Sort() {
        for (BookNode* i = head; i != nullptr; i = i->next)
            for (BookNode* j = i->next; j != nullptr; j = j->next)
                if (i->bookID > j->bookID) SwapData(i, j);
        cout << "Books sorted by ID.\n";
    }

    void Reverse() {
        BookNode* previous = nullptr;
        BookNode* current = head;
        while (current != nullptr) {
            BookNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        head = previous;
        cout << "Book collection reversed.\n";
    }

    void Print() {
        if (IsEmpty()) {
            cout << "No books in the collection.\n";
            return;
        }
        cout << "\nIndex\tBook ID\tTitle\n";
        BookNode* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << index++ << "\t" << current->bookID << "\t"
                 << current->title << "\n";
            current = current->next;
        }
        cout << "Total books: " << count << "\n";
    }

    ~LinkedList() {
        while (IsNotEmpty()) delete Remove();
    }
};

BookNode* CreateBook(int id, string title);

#endif
