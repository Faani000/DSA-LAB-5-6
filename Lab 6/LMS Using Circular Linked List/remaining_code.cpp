#include "libraries.h"

BookNode* CreateBook(int id, string title) {
    BookNode* book = new BookNode;
    book->bookID = id; book->title = title; book->next = nullptr;
    return book;
}
