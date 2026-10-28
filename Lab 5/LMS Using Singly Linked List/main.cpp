#include "libraries.h"

int main() {
    LinkedList library;
    int choice, id, index, first, second;
    string title;

    do {
        cout << "\n===== LIBRARY BOOK COLLECTION SYSTEM =====\n";
        cout << "1. Display All Books\n2. Insert Book at Head\n3. Remove Book from Head\n";
        cout << "4. Insert Book at Index\n5. Remove Book at Index\n6. Swap Books\n";
        cout << "7. Sort Books by ID\n8. Reverse Book Collection\n";
        cout << "9. Check Collection Status\n10. Exit\nEnter your choice: ";
        if (!(cin >> choice)) return 0;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) library.Print();
        else if (choice == 2 || choice == 4) {
            cout << "Enter book ID: "; cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter book title: "; getline(cin, title);
            if (choice == 2) library.Insert(CreateBook(id, title));
            else {
                cout << "Enter index (starting from 0): "; cin >> index;
                library.InsertAt(CreateBook(id, title), index);
            }
            cout << "Book inserted.\n";
        } else if (choice == 3 || choice == 5) {
            BookNode* removed;
            if (choice == 3) removed = library.Remove();
            else {
                cout << "Enter index: "; cin >> index;
                removed = library.RemoveAt(index);
            }
            if (removed != nullptr) {
                cout << "Removed: " << removed->title << "\n";
                delete removed;
            } else cout << "The list is empty.\n";
        } else if (choice == 6) {
            cout << "Enter first index: "; cin >> first;
            cout << "Enter second index: "; cin >> second;
            library.Swap(first, second);
        } else if (choice == 7) library.Sort();
        else if (choice == 8) library.Reverse();
        else if (choice == 9) {
            cout << "Total books: " << library.Size() << "\n";
            cout << (library.IsEmpty() ? "Collection is empty.\n" : "Collection is not empty.\n");
        } else if (choice != 10) cout << "Invalid choice.\n";
    } while (choice != 10);

    cout << "Program ended.\n";
    return 0;
}
