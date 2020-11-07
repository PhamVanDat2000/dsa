#include <iostream>
#include<string.h>
using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book()
    {
        this->title = NULL;
        this->authors = NULL;
        this->publishingYear = 0;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->title, title);
        strcpy(this->authors, authors);
        this->publishingYear = publishingYear;
    }

    ~Book()
    {
        delete this->title;
        delete this->authors;
        this->publishingYear = 0;
    }

    friend class Printer;
};

class Printer
{
public:
    static void printBook(const Book book)
    {
        printf("%s\n", book.title);
        int i = 0;
        if (book.authors[i] == ' ')
            i++;
        for (i = 0; i < strlen(book.authors); i++) {
            while (book.authors[i] != 0 && book.authors[i] != ',')
            {
                printf("%c", book.authors[i]);
                i++;
            }
            printf("\n");
            i++;
        }

        printf("%d", book.publishingYear);
    }
};
int main() {
    Book book1("Introduction to Algorithms", "Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein", 1990);
    Printer::printBook(book1);


    return 0;
}