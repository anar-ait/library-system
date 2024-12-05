#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// Book class definition
class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    std::string dateAdded;

    // Helper function to validate ISBN (for demonstration)
    bool isValidISBN(const std::string& isbn) const {
        return isbn.length() == 10 || isbn.length() == 13;  // Simple validation for ISBN length
    }

public:
    // Set book details with validation
    void setBookDetails(const std::string& t, const std::string& a, const std::string& i, bool avail, const std::string& date) {
        if (!isValidISBN(i)) {
            throw std::invalid_argument("Invalid ISBN format.");
        }
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

// Function to test book class initialization and error handling
void testBookClass() {
    std::cout << "=== TEST: Book Initialization ===\n";

    // Correct initialization
    Book book1, book2, book3;
    try {
        book1.setBookDetails("Test Book 1", "Author A", "1234567890", true, "2024-01-01");
        book2.setBookDetails("Test Book 2", "Author B", "0987654321", false, "2024-02-01");
        book3.setBookDetails("Test Book 3", "Author C", "5678901234", true, "2024-03-01");
        std::cout << "Correct initialization completed successfully.\n";
    } catch (const std::exception& e) {
        std::cout << "Error during correct initialization: " << e.what() << "\n";
    }

    // Incorrect initialization
    try {
        book1.setBookDetails("Invalid Book", "Author X", "INVALID_ISBN", true, "2024-04-01");
        std::cout << "Incorrect initialization detected.\n";
    } catch (const std::exception& e) {
        std::cout << "Error detected during incorrect initialization: " << e.what() << "\n";
        // Output the invalid book data
        std::cout << "Invalid book data:\n";
        std::cout << "Title: Invalid Book\n"
                  << "Author: Author X\n"
                  << "ISBN: INVALID_ISBN\n"
                  << "Availability: Available\n"
                  << "Date Added: 2024-04-01\n\n";
    }

    std::cout << "\n";
}


// Function to test sorting functionality
void testSortingBooks() {
    std::cout << "=== TEST: Sorting Books ===\n";

    // Arrays of books
    std::vector<Book> ascending(3), descending(3), mixed(3);

    // Initialize arrays
    ascending[0].setBookDetails("Book A", "Author X", "1111111111", true, "2024-01-01");
    ascending[1].setBookDetails("Book B", "Author Y", "2222222222", true, "2024-02-01");
    ascending[2].setBookDetails("Book C", "Author Z", "3333333333", true, "2024-03-01");

    descending[0].setBookDetails("Book C", "Author Z", "3333333333", true, "2024-03-01");
    descending[1].setBookDetails("Book B", "Author Y", "2222222222", true, "2024-02-01");
    descending[2].setBookDetails("Book A", "Author X", "1111111111", true, "2024-01-01");

    mixed[0].setBookDetails("Book B", "Author Y", "2222222222", true, "2024-02-01");
    mixed[1].setBookDetails("Book C", "Author Z", "3333333333", true, "2024-03-01");
    mixed[2].setBookDetails("Book A", "Author X", "1111111111", true, "2024-01-01");

    // Sort arrays
    Book::sortBookData(ascending);
    Book::sortBookData(descending);
    Book::sortBookData(mixed);

    std::cout << "Books in ascending order:\n";
    for (const auto& book : ascending) {
        book.displayBookDetails();
    }

    std::cout << "Books in descending order:\n";
    for (const auto& book : descending) {
        book.displayBookDetails();
    }

    std::cout << "Books in mixed order:\n";
    for (const auto& book : mixed) {
        book.displayBookDetails();
    }

    std::cout << "\n";
}

int main() {
    std::cout << "=== Library Management System: Test Application ===\n";

    // Run tests
    testBookClass();
    testSortingBooks();

    std::cout << "All tests completed.\n";

    return 0;
}

