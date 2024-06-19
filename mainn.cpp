#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Định nghĩa lớp Student để lưu trữ thông tin của mỗi học sinh
class Student {
public:
    string name;        // Tên học sinh
    string student_id;  // Mã số học sinh
    string class_name;  // Tên lớp
    int rank;           // Thứ hạng
    string pass;        // Mật khẩu

    // Constructor để khởi tạo đối tượng Student từ các thông tin đầu vào
    Student(string n, string sid, string cn, int r, string p)
        : name(n), student_id(sid), class_name(cn), rank(r), pass(p) {}
};

vector<Student> students; // Vector chứa danh sách các đối tượng Student

// Khai báo các hàm
void searchByClass(const string& filename); // Hàm tìm kiếm học sinh theo lớp
void deleteByRank();                        // Hàm xóa học sinh theo thứ hạng
void clrscr();                              // Hàm xóa màn hình console
void waitForKey();                          // Hàm chờ nhấn phím tiếp tục

int main() {
    string csv_filename;

    // Nhập đường dẫn đến file CSV
    cout << "Enter path to the CSV file: ";
    cin >> csv_filename;

    int choice = 0;
    // Vòng lặp chính của chương trình
    while (choice != 3) {
        clrscr(); // Xóa màn hình
        // Menu chính của chương trình
        cout << "\t\t\t===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "\n\n\n\t\t\t\t 1. Search student by class (6A1, 6A2, 6A3)\n";
        cout << "\t\t\t\t 2. Delete student by rank\n";
        cout << "\t\t\t\t 3. Exit\n";
        cout << "\t\t\t\t ___________________________\n";
        cout << "\t\t\t\t ";
        cin >> choice;

        // Xử lý lựa chọn từ menu
        switch (choice) {
            case 1:
                clrscr(); // Xóa màn hình
                searchByClass(csv_filename); // Gọi hàm tìm kiếm học sinh theo lớp
                waitForKey(); // Chờ người dùng nhấn phím tiếp tục
                clrscr(); // Xóa màn hình
                break;
            case 2:
                clrscr(); // Xóa màn hình
                deleteByRank(); // Gọi hàm xóa học sinh theo thứ hạng
                waitForKey(); // Chờ người dùng nhấn phím tiếp tục
                clrscr(); // Xóa màn hình
                break;
            case 3:
                clrscr(); // Xóa màn hình
                cout << "\n\t\t\tThank you for using the software\n";
                return 0; // Kết thúc chương trình
            default:
                clrscr(); // Xóa màn hình
                cout << "\n\t\t\tEnter a valid number.\n";
                waitForKey(); // Chờ người dùng nhấn phím tiếp tục
                clrscr(); // Xóa màn hình
                break;
        }
    }
    return 0;
}

// Hàm xóa màn hình console
void clrscr() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Hàm chờ người dùng nhấn phím tiếp tục
void waitForKey() {
    cout << "Press any key to continue...\n";
    cin.ignore();
    cin.get();
}

// Hàm tìm kiếm học sinh theo lớp
void searchByClass(const string& filename) {
    students.clear(); // Xóa dữ liệu học sinh hiện có

    // Đọc file CSV và gán các lớp cho học sinh
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1); // Thoát chương trình nếu không thể mở file
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, student_id, class_name, rank_str, pass;

        // Đọc thông tin từng dòng trong file CSV
        if (getline(ss, name, ',') && getline(ss, student_id, ',') && getline(ss, class_name, ',') &&
            getline(ss, rank_str, ',') && getline(ss, pass, ',')) {
            try {
                int rank = stoi(rank_str); // Chuyển đổi rank từ string sang int
                students.push_back(Student(name, student_id, class_name, rank, pass)); // Thêm học sinh vào vector students
            } catch (const invalid_argument& e) {
                cerr << "Invalid rank value: " << rank_str << " for student: " << name << endl;
                continue; // Bỏ qua nếu giá trị rank không hợp lệ
            }
        }
    }

    file.close(); // Đóng file sau khi đọc xong

    // Sắp xếp các học sinh theo rank
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.rank < b.rank;
    });

    // Xóa các phân lớp trước đó của các học sinh
    for (auto& student : students) {
        student.class_name = "";
    }

    // Phân lớp học sinh vào 3 lớp 6A1, 6A2, 6A3 với số lượng gần bằng nhau
    int student_count = students.size();
    int class_size = student_count / 3; // Chia đều học sinh vào 3 lớp

    for (int i = 0; i < student_count; ++i) {
        if (i < class_size) {
            students[i].class_name = "6A1";
        } else if (i < 2 * class_size) {
            students[i].class_name = "6A2";
        } else {
            students[i].class_name = "6A3";
        }
    }

    // Nhập tên lớp để tìm kiếm
    string search_class_name;
    cout << "\n\t\t\t\t====== Search Student by Class ======\n\n\n";
    cout << "\n\t\t\tEnter class name to search (6A1, 6A2, 6A3): ";
    cin >> search_class_name;

    // In thông tin học sinh thuộc lớp tìm kiếm
    bool found = false;
    for (const auto& student : students) {
        if (student.class_name == search_class_name) {
            found = true;
            cout << "\n\t\t\tName: " << student.name;
            cout << "\n\t\t\tStudent ID: " << student.student_id;
            cout << "\n\t\t\tClass: " << student.class_name;
            cout << "\n\t\t\tRank: " << student.rank;
            cout << "\n\t\t\tPass: " << student.pass;
            cout << "\n";
        }
    }

    if (!found) {
        cout << "\n\t\t\tNo students found in class " << search_class_name << "\n";
    }
}

// Hàm xóa học sinh theo thứ hạng
void deleteByRank() {
    int rank;
    bool found = false;

    cout << "\t\t\t\t====== Delete Student by Rank ======\n\n\n";
    cout << "\n\t\t\tEnter rank of student to delete: ";
    cin >> rank;

    // Tìm và xóa học sinh có rank nhập vào
    auto it = remove_if(students.begin(), students.end(), [rank, &found](const Student& student) {
        if (student.rank == rank) {
            found = true;
            return true;
        }
        return false;
    });

    if (found) {
        students.erase(it, students.end()); // Xóa học sinh từ vị trí it đến cuối

        // Xuất thông tin học sinh còn lại ra file CSV
        ofstream csv("student_info.csv");
        if (!csv.is_open()) {
            cerr << "\n\t\t\tCan't open file\n";
            return;
        }

        csv << "Name,Student ID,Class,Rank,Pass\n";

        for (const auto& student : students) {
            csv << student.name << "," << student.student_id << "," << student.class_name << ","
                << student.rank << "," << student.pass << "\n";
        }

        csv.close(); // Đóng file sau khi ghi dữ liệu xong
        cout << "\n\t\t\tStudent with rank " << rank << " deleted and data exported to student_info.csv successfully\n";
    } else {
        cout << "\n\t\t\tNo student found with rank " << rank << "\n";
    }
}
