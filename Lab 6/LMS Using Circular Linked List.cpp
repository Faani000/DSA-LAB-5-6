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

BookNode* CreateBook(int id, string title) {
    BookNode* book = new BookNode;
    book->bookID = id; book->title = title; book->next = nullptr;
    return book;
}

int main() {
    CircularLinkedList library;
    int choice, id, index, a, b;
    string title;

    do {
        cout << "\n===== CIRCULAR LIBRARY BOOK DISPLAY SYSTEM =====\n";
        cout << "1. Display All Books\n2. Insert Book at Head\n3. Remove Book from Head\n";
        cout << "4. Insert Book at Index\n5. Remove Book at Index\n6. Swap Books\n";
        cout << "7. Sort Books by ID\n8. Reverse Book Collection\n9. Move to Next Book\n";
        cout << "10. Check Collection Status\n11. Exit\nEnter your choice: ";
        if (!(cin >> choice)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) library.Print();
        else if (choice == 2 || choice == 4) {
            cout << "Book ID: "; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Book title: "; getline(cin, title);
            if (choice == 2) library.Insert(CreateBook(id, title));
            else {
                cout << "Index (starting from 0): "; cin >> index;
                library.InsertAt(CreateBook(id, title), index);
            }
            cout << "Book inserted.\n";
        } else if (choice == 3 || choice == 5) {
            BookNode* removed;
            if (choice == 3) removed = library.Remove();
            else { cout << "Index: "; cin >> index; removed = library.RemoveAt(index); }
            if (removed != nullptr) {
                cout << "Removed: " << removed->title << "\n";
                delete removed;
            } else cout << "The list is empty.\n";
        } else if (choice == 6) {
            cout << "First index: "; cin >> a;
            cout << "Second index: "; cin >> b;
            library.Swap(a, b);
        } else if (choice == 7) library.Sort();
        else if (choice == 8) library.Reverse();
        else if (choice == 9) library.MoveNext();
        else if (choice == 10) {
            cout << "Total books: " << library.Size() << "\n";
            cout << (library.IsEmpty() ? "Collection is empty.\n" : "Collection is not empty.\n");
        } else if (choice != 11) cout << "Invalid choice.\n";
    } while (choice != 11);

    cout << "Program ended.\n";
    return 0;
}
