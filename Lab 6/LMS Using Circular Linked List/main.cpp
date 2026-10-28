#include "libraries.h"

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
