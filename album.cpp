#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // system
#include <iomanip>  // setw
#include <algorithm>
#include <sstream>

using namespace std;

class Image {
public:
    string name;
    string date; // format: DD-MM-YYYY
    string description;
    int size;
    Image* next;

    Image() {
        next = nullptr;
    }
};

Image* head = nullptr;

void clearScreen() {
    system("cls"); // use "clear" for Linux/macOS
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

Image* createImage() {
    Image* newImage = new Image();

    cout << "Enter photo name: ";
    getline(cin >> ws, newImage->name);

    cout << "Enter date (DD-MM-YYYY): ";
    getline(cin, newImage->date);

    cout << "Enter description: ";
    getline(cin, newImage->description);

    cout << "Enter size (KB): ";
    cin >> newImage->size;

    return newImage;
}

void addPhoto() {
    Image* newImage = createImage();
    if (!newImage) return;

    if (!head) {
        head = newImage;
    } else {
        Image* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newImage;
    }
    cout << "\nPhoto added successfully!\n";
    pause();
}

void addPhoto_auto() {
    vector<string> names = {
        "Sunset.jpg", "Beach.png", "Mountain.bmp", "Forest.jpeg", "River.tiff",
        "City.jpg", "Desert.png", "Snow.bmp", "NightSky.jpeg", "Flower.tiff"
    };

    vector<string> dates = {
        "01-01-2023", "01-01-2023", "01-01-2023", "20-04-2023", "30-05-2023",
        "15-06-2023", "22-07-2023", "10-08-2023", "18-09-2023", "25-10-2023"
    };

    vector<string> descs = {
        "captured by me", "Capture by me", "Snowy mountain peak", "Green lush forest", "Captured by me",
        "Busy city skyline", "Hot desert with cactus", "Frozen lake in winter", "Starry night sky", "Colorful spring flowers"
    };

    vector<int> sizes = {1500, 1200, 1800, 1300, 1100, 1400, 1600, 1700, 1250, 1350};

    for (int i = 0; i < 10; i++) {
        Image* newImage = new Image();
        newImage->name = names[i];
        newImage->date = dates[i];
        newImage->description = descs[i];
        newImage->size = sizes[i];

        if (!head) {
            head = newImage;
        } else {
            Image* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newImage;
        }
    }

    cout << "\n10 sample photos added successfully!\n";

    Image* temp = head;
    cout << left << setw(20) << "Photo Name" << setw(12) << "Date" << setw(10) << "Size(KB)" << "Description\n";
    cout << string(60, '-') << "\n";

    while (temp) {
        cout << setw(20) << temp->name << setw(12) << temp->date << setw(10) << temp->size << temp->description << "\n";
        temp = temp->next;
    }
    pause();
}

void displayPhotos() {
    if (!head) {
        cout << "No photos in the album.\n";
        pause();
        return;
    }

    Image* temp = head;
    cout << left << setw(20) << "Photo Name" << setw(12) << "Date" << setw(10) << "Size(KB)" << "Description\n";
    cout << string(60, '-') << "\n";

    while (temp) {
        cout << setw(20) << temp->name << setw(12) << temp->date << setw(10) << temp->size << temp->description << "\n";
        temp = temp->next;
    }
    pause();
}

Image* findPhoto(const string& name) {
    Image* temp = head;
    while (temp) {
        if (temp->name == name)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}

void searchPhoto() {
    string name;
    cout << "Enter photo name to search: ";
    getline(cin >> ws, name);

    Image* photo = findPhoto(name);
    if (photo) {
        cout << "\nPhoto found:\n";
        cout << "Name: " << photo->name << "\nDate: " << photo->date
             << "\nSize: " << photo->size << " KB\nDescription: " << photo->description << "\n";
    } else {
        cout << "Photo not found.\n";
    }
    pause();
}

void deletePhoto() {
    string name;
    cout << "Enter photo name to delete: ";
    getline(cin >> ws, name);

    Image* temp = head;
    Image* prev = nullptr;

    while (temp && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Photo not found.\n";
    } else {
        if (!prev)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Photo deleted successfully.\n";
    }
    pause();
}

void editPhoto() {
    string name;
    cout << "Enter photo name to edit: ";
    getline(cin >> ws, name);

    Image* photo = findPhoto(name);
    if (!photo) {
        cout << "Photo not found.\n";
        pause();
        return;
    }

    cout << "Editing photo: " << name << "\n";

    cout << "Enter new date (DD-MM-YYYY): ";
    getline(cin, photo->date);

    cout << "Enter new description: ";
    getline(cin, photo->description);

    cout << "Enter new size (KB): ";
    cin >> photo->size;

    cout << "Photo updated successfully.\n";
    pause();
}

void detectDuplicates() {
    bool found = false;
    for (Image* ptr1 = head; ptr1 != nullptr; ptr1 = ptr1->next) {
        for (Image* ptr2 = ptr1->next; ptr2 != nullptr; ptr2 = ptr2->next) {
            if (ptr1->name == ptr2->name && ptr1->date == ptr2->date) {
                cout << "Duplicate found: " << ptr1->name << " on " << ptr1->date << "\n";
                found = true;
            }
        }
    }

    if (!found)
        cout << "No duplicates found.\n";

    pause();
}

int countNodes() {
    int count = 0;
    Image* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

vector<Image*> fillArray() {
    vector<Image*> arr;
    Image* temp = head;
    while (temp) {
        arr.push_back(temp);
        temp = temp->next;
    }
    return arr;
}

bool compareByName(Image* a, Image* b) {
    return a->name < b->name;
}

bool compareBySize(Image* a, Image* b) {
    return a->size < b->size;
}

bool compareByDate(Image* a, Image* b) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(a->date.c_str(), "%2d-%2d-%4d", &d1, &m1, &y1);
    sscanf(b->date.c_str(), "%2d-%2d-%4d", &d2, &m2, &y2);

    if (y1 != y2) return y1 < y2;
    if (m1 != m2) return m1 < m2;
    return d1 < d2;
}

void printSortedArray(const vector<Image*>& arr) {
    for (const auto& img : arr) {
        cout << "Name: " << img->name << ", Date: " << img->date << "\n";
    }
    pause();
}

void sortByName() {
    auto arr = fillArray();
    sort(arr.begin(), arr.end(), compareByName);
    printSortedArray(arr);
}

void sortBySize() {
    auto arr = fillArray();
    sort(arr.begin(), arr.end(), compareBySize);
    printSortedArray(arr);
}

void sortByDate() {
    auto arr = fillArray();
    sort(arr.begin(), arr.end(), compareByDate);
    printSortedArray(arr);
}

// You can then create a menu to test all functions here if you want.
int main() {
    int choice;
    do {
        clearScreen();
        cout << "===== Photo Manager =====\n";
        cout << "1. Add Photo\n";
        cout << "2. Add Sample Photos\n";
        cout << "3. Display Photos\n";
        cout << "4. Search Photo\n";
        cout << "5. Delete Photo\n";
        cout << "6. Edit Photo\n";
        cout << "7. Detect Duplicates\n";
        cout << "8. Sort by Name\n";
        cout << "9. Sort by Size\n";
        cout << "10. Sort by Date\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addPhoto(); break;
            case 2: addPhoto_auto(); break;
            case 3: displayPhotos(); break;
            case 4: searchPhoto(); break;
            case 5: deletePhoto(); break;
            case 6: editPhoto(); break;
            case 7: detectDuplicates(); break;
            case 8: sortByName(); break;
            case 9: sortBySize(); break;
            case 10: sortByDate(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n"; pause(); break;
        }

    } while (choice != 0);

    return 0;
}
