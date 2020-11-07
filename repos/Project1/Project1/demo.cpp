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
        this->title = new char[10];
        strcpy(this->title, " ");
        this->authors = new char[10];
        strcpy(this->authors, " ");
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

    friend bool checkAuthor(Book book, const char* author)
    {
        int i = 0, j = 0;
        int flag = 0;
        while (book.authors[i] != 0)
        {
            if (book.authors[i] == author[j])
            {
                j++;
                if (author[j] == 0)
                {
                    flag = 1;
                    break;
                }
            }
            else
                j = 0;
            i++;
        }
        if (flag && (book.authors[i + 1] == 0 || book.authors[i + 1] == ','))
            return true;
        else
            return false;
    }
};
int main()
{
    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    cout << checkAuthor(book1, "Nguyen Thi Xuan Anh");
    return 0;
}