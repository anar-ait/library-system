#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    std::string dateAdded;

public:
    // Set book details
    void setBookDetails(std::string t, std::string a, std::string i, bool avail, std::string date) {
        title = t;
        author = a;
        isbn = i;
        isAvailable = avail;
        dateAdded = date;
    }

    // Display book details
    void displayBookDetails() const {
        std::cout << "Title: " << title << "\n"
                  << "Author: " << author << "\n"
                  << "ISBN: " << isbn << "\n"
                  << "Availability: " << (isAvailable ? "Available" : "Borrowed") << "\n\n";
    }

    // Borrow book
    bool borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            std::cout << "Book borrowed successfully.\n";
            return true;
        }
        std::cout << "Book is already borrowed.\n";
        return false;
    }

    // Return book
    void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            std::cout << "Book returned successfully.\n";
        } else {
            std::cout << "Error: Book was not borrowed.\n";
        }
    }

    // Get ISBN
    std::string getISBN() const {
        return isbn;
    }

    // Check availability
    bool isBookAvailable() const {
        return isAvailable;
    }

    // Sort books by ISBN
    static void sortBookData(std::vector<Book>& books) {
        std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.isbn < b.isbn;
        });
    }
};

int main() {
    std::vector<Book> library(5);

    // Initialize books with real data
    library[0].setBookDetails("To Kill a Mockingbird", "Harper Lee", "9780060935467", true, "2020-01-01");
    library[1].setBookDetails("1984", "George Orwell", "9780451524935", true, "2020-02-01");
    library[2].setBookDetails("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565", true, "2020-03-01");
    library[3].setBookDetails("The Catcher in the Rye", "J.D. Salinger", "9780316769488", true, "2020-04-01");
    library[4].setBookDetails("Pride and Prejudice", "Jane Austen", "9780141439518", true, "2020-05-01");

    Book::sortBookData(library); // Sort books by ISBN
    std::cout << "Books have been sorted by ISBN.\n";

    while (true) {
        // Display menu
        std::cout << "Library Management System\n";
        std::cout << "1. Borrow a book by ISBN\n";
        std::cout << "2. Return a book by ISBN\n";
        std::cout << "3. Display all books\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break; // Exit program
        }

        switch (choice) {
            case 1: {
                std::cout << "Enter ISBN to borrow a book: ";
                std::string inputISBN;
                std::cin >> inputISBN;

                bool found = false;
                for (auto& book : library) {
                    if (book.getISBN() == inputISBN) {
                        found = true;
                        book.borrowBook();
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Error: Book with ISBN " << inputISBN << " not found.\n";
                }
                break;
            }
            case 2: {
                std::cout << "Enter ISBN to return a book: ";
                std::string inputISBN;
                std::cin >> inputISBN;

                bool found = false;
                for (auto& book : library) {
                    if (book.getISBN() == inputISBN) {
                        found = true;
                        book.returnBook();
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Error: Book with ISBN " << inputISBN << " not found.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Displaying all books:\n";
                for (const auto& book : library) {
                    book.displayBookDetails();
                }
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
