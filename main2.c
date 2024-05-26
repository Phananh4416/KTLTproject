#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef __unix__                         // If Compilation Environment is UNIX
#include <unistd.h>                     // For usleep() function
#define delay(x) usleep((x) * 1000)     // For Windows delay function
#define CLS() printf("\033[2J\033[1;1H")// ANSI Escape sequence for clearing screen

void gotoxy(int x, int y) {             // gotoxy function for UNIX
    printf("\033[%d;%dH", y, x);        // ANSI Escape Sequence for gotoxy
}

#else                                   // If Compilation Environment is not UNIX
#define CLS() system("cls")             // Windows clearscreen function
#include <windows.h>
// Định nghĩa FILE path
#define FLBCLAS "class.txt"
#define FLBSTUD "student.txt"

// Định nghĩa RULE macro
#define RULE(x) { printf("\n"); for (int _ = 0; _ < 80; _++) printf("%c", x); printf("\n"); }
void gotoxy(int x, int y) {             // gotoxy for Windows
    y--;
    static HANDLE h = NULL;
    if (!h) {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

void delay(unsigned int secs) {         // Defining delay function for Windows
    clock_t goal = secs + clock();      // Using clock to set time to delay till
    while (goal > clock());             // Waiting till that time
}
#endif

#define FLBSTUD "student.txt"           // Macros for storing filenames for ease
#define FLBCLAS "class.txt"             // The files are binary files
#define RULE(x) printf("\n"); for (int _ = 0; _ < 80; _++) printf("%c", x); printf("\n") // Outputs Horizontal Consisting of 'x's
#define CL(cl, x) ((cl) == 0 ? 1 : (cl) == (x)) // Macro for disabling search through class

int login() {
    // Implement login function here
    return 0;
}

int strcmpi(const char *s1, const char *s2) {   // String compare without case
    return strcasecmp(s1, s2);
}

typedef struct {
    char* first;
    int second;
} Pair;

int strcmpis(const void *a, const void *b) {    // Compare function for sort()
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    return strcasecmp(p1->first, p2->first);
}

void load() {                                  // Loader function
    CLS();
    printf("\n\n\n\n\t\t\t\t  Loading\n\n");
    for (int i = 0; i < 80; i++) {
        printf("!");
        gotoxy(i, 3);                         // Top Loading line
        printf("!");
        fflush(stdout);                       // Flush output buffer for delay()
        gotoxy(i + 1, 7);                     // Bottom Loading line
        delay((rand() % 80) + 20);
    }
    fflush(stdout);
    delay(200);
}

int scan() {                                  // Scan function for input of only non-negative integers
    char ch[100];                             // Taking initial input through string
    int i, v;
    do {
        v = 1;
        scanf("%s", ch);
        for (i = 0; i < strlen(ch); i++) {    // Checking each character is digit
            if (!isdigit(ch[i])) {
                v = 0;
                break;
            }
        }
    } while (!v);
    return atoi(ch);                          // Converting string back to integer
}

char* strTitle(int x) {                       // Converting Title from Integer to readable text
    static char title[8];
    if (x == 1)
        strcpy(title, "Master");
    else if (x == 2)
        strcpy(title, "Mr");
    else
        strcpy(title, "Miss");
    return title;
}

char bGs[8][4] = {"A+", "B+", "AB+", "O+", "A-", "B-", "AB-", "O-"}; // Allowed Blood Groups
int fee[12] = {                               // Fee for each standard
    1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000
};

typedef struct {
    int rollNo;         // Thay thế cho retRollNo
    char title[30];
    char studentName[30];
    char fatherName[30];
    char motherName[30];
    char address[50];
    char bloodGroup[5];
} Student;

void getDetails(Student* student) {    // Get Student Details from user
    CLS();
    printf("Enter Title \n(Master = 1, Mr = 2, Miss = 3)  : ");
    do {
        scanf("%d", &student->title);
    } while (student->title != 1 && student->title != 2 && student->title != 3);
    
    printf("Enter Student Name    : ");
    do {
        fgets(student->studentName, sizeof(student->studentName), stdin);
        student->studentName[strcspn(student->studentName, "\n")] = '\0'; // Remove newline character
    } while (strlen(student->studentName) == 0);

    printf("Enter Roll No.        : ");
    do {
        student->rollNo = scan();
    } while (student->rollNo < 1);

    printf("Enter Father Name     : ");
    do {
        fgets(student->fatherName, sizeof(student->fatherName), stdin);
        student->fatherName[strcspn(student->fatherName, "\n")] = '\0'; // Remove newline character
    } while (strlen(student->fatherName) == 0);

    printf("Enter Mother Name     : ");
    do {
        fgets(student->motherName, sizeof(student->motherName), stdin);
        student->motherName[strcspn(student->motherName, "\n")] = '\0'; // Remove newline character
    } while (strlen(student->motherName) == 0);

    printf("Enter Address         : ");
    do {
        fgets(student->address, sizeof(student->address), stdin);
        student->address[strcspn(student->address, "\n")] = '\0'; // Remove newline character
    } while (strlen(student->address) == 0);

    printf("Enter Blood Group     : ");
    int v = 0, i;
    do {
        fgets(student->bloodGroup, sizeof(student->bloodGroup), stdin);
        student->bloodGroup[strcspn(student->bloodGroup, "\n")] = '\0'; // Remove newline character
        for (i = 0; i < strlen(student->bloodGroup); i++) {
            student->bloodGroup[i] = toupper(student->bloodGroup[i]);
        }
        for (i = 0; i < 8; i++) {
            if (!strcmp(student->bloodGroup, bGs[i])) {
                v = 1;
                break;
            }
        }
    } while (!v);
}

void Student_printDetails(Student* obj, char attr) {
    printf("Roll No.       : %d\n", obj->rollNo);
    printf("Title          : %s\n", obj->title);
    printf("Student Name   : %s\n", obj->studentName);
    printf("Father's Name  : %s\n", obj->fatherName);
    printf("Mother's Name  : %s\n", obj->motherName);
    printf("Address        : %s\n", obj->address);
    printf("Blood Group    : %s\n", obj->bloodGroup);
}
void Student_printDetails_no_attr(Student* obj) {
    printf("Roll No.       : %d\n", obj->rollNo);
    printf("Title          : %s\n", obj->title);
    printf("Student Name   : %s\n", obj->studentName);
    printf("Father's Name  : %s\n", obj->fatherName);
    printf("Mother's Name  : %s\n", obj->motherName);
    printf("Address        : %s\n", obj->address);
    printf("Blood Group    : %s\n", obj->bloodGroup);
}
int retRollNo(Student* student) {      // Return Roll No
    return student->rollNo;
}

char* retString(Student* student, char x) {  // Return all strings available from the Student struct
    if (x == 'T')
        return strTitle(student->title[0]);
    if (x == 'N')
        return student->studentName;
    if (x == 'F')
        return student->fatherName;
    if (x == 'M')
        return student->motherName;
    if (x == 'A')
        return student->address;
    if (x == 'B')
        return student->bloodGroup;
    return NULL;
}

char* retStudentName(Student* student) {     // Returns Student Name
    return retString(student, 'N');
}

void modDetail(Student* student, char ch) {  // Modify Details for Student
    if (ch == 'T') {
        printf("Enter new title (1 for Master, 2 for Mr, 3 for Miss): ");
        scanf("%d", &student->title);
    } else if (ch == 'N') {
        printf("Enter new student name: ");
        fgets(student->studentName, sizeof(student->studentName), stdin);
        student->studentName[strcspn(student->studentName, "\n")] = '\0'; // Remove newline character
    } else if (ch == 'F') {
        printf("Enter new father's name: ");
        fgets(student->fatherName, sizeof(student->fatherName), stdin);
        student->fatherName[strcspn(student->fatherName, "\n")] = '\0'; // Remove newline character
    } else if (ch == 'M') {
        printf("Enter new mother's name: ");
        fgets(student->motherName, sizeof(student->motherName), stdin);
        student->motherName[strcspn(student->motherName, "\n")] = '\0'; // Remove newline character
    } else if (ch == 'A') {
        printf("Enter new address: ");
        fgets(student->address, sizeof(student->address), stdin);
        student->address[strcspn(student->address, "\n")] = '\0'; // Remove newline character
    } else if (ch == 'B') {
        printf("Enter new blood group: ");
        fgets(student->bloodGroup, sizeof(student->bloodGroup), stdin);
        student->bloodGroup[strcspn(student->bloodGroup, "\n")] = '\0'; // Remove newline character
    }
}
typedef struct {
    int classID;        // Thay thế cho retClass
    int rollNo;         // Thay thế cho retRollNo
    char subject[30];
    char studentName[30];
} Class;


void getDetailsClass(Class* class_rec) {    // Get Class Record Detail from user
    CLS();
    printf("Enter Class Standard : ");
    class_rec->classID = scan();

    printf("Enter Student Name   : ");
    do {
        fgets(class_rec->studentName, sizeof(class_rec->studentName), stdin);
        class_rec->studentName[strcspn(class_rec->studentName, "\n")] = '\0'; // Remove newline character
    } while (strlen(class_rec->studentName) == 0);

    printf("Enter Roll No.       : ");
    do {
        class_rec->rollNo = scan();
    } while (class_rec->rollNo < 1);

    printf("Enter Subject        : ");
    do {
        fgets(class_rec->subject, sizeof(class_rec->subject), stdin);
        class_rec->subject[strcspn(class_rec->subject, "\n")] = '\0'; // Remove newline character
    } while (strlen(class_rec->subject) == 0);
}

void Class_printDetails(Class* obj, char attr) {
    printf("Class ID       : %d\n", obj->classID);
    printf("Roll No.       : %d\n", obj->rollNo);
    printf("Subject        : %s\n", obj->subject);
    printf("Student Name   : %s\n", obj->studentName);
}
void Class_printDetails_no_attr(Class* obj) {
    printf("Class ID       : %d\n", obj->classID);
    printf("Roll No.       : %d\n", obj->rollNo);
    printf("Subject        : %s\n", obj->subject);
    printf("Student Name   : %s\n", obj->studentName);
}

int retClass(Class* class_rec) {           // Return Class Standard
    return class_rec->classID;
}

int retRollNoClass(Class* class_rec) {     // Return Roll No
    return class_rec->rollNo;
}

char* retStringClass(Class* class_rec, char x) {  // Return all strings available from the Class struct
    if (x == 'N')
        return class_rec->studentName;
    if (x == 'S')
        return class_rec->subject;
    return NULL;
}

char* retStudentNameClass(Class* class_rec) {     // Return Student Name
    return retStringClass(class_rec, 'N');
}

void modDetailClass(Class* class_rec, char ch) {  // Modify Details for Class
    if (ch == 'C') {
        printf("Enter new class standard: ");
        class_rec->classID = scan();
    } else if (ch == 'N') {
        printf("Enter new student name: ");
        fgets(class_rec->studentName, sizeof(class_rec->studentName), stdin);
        class_rec->studentName[strcspn(class_rec->studentName, "\n")] = '\0'; // Remove newline character
    } else if (ch == 'R') {
        printf("Enter new roll number: ");
        class_rec->rollNo = scan();
    } else if (ch == 'S') {
        printf("Enter new subject: ");
        fgets(class_rec->subject, sizeof(class_rec->subject), stdin);
        class_rec->subject[strcspn(class_rec->subject, "\n")] = '\0'; // Remove newline character
    }
}
void insertStudent() {              // Insert Student Record in File
    CLS();
    Student obj, obj2;
    char ch;
    int v = 0;
    printf("Enter Details for new Student :\n");
    Student_printDetails_no_attr(&obj);
    FILE* fl1 = fopen(FLBSTUD, "rb");
    FILE* fl2;
    if (!fl1) {                   // If file does not exist, create new file
        fl2 = fopen(FLBSTUD, "wb");
        fwrite(&obj, sizeof(obj), 1, fl2);
        fclose(fl2);
        printf("Record successfully inserted !\n");
        return;
    }
    while (fread(&obj2, sizeof(obj), 1, fl1) == 1) {
        if (feof(fl1)) {
            break;
        }
        if (obj.rollNo == obj2.rollNo) {          // If record with same Roll No. exists, then abort insertion
            printf("Record with same Roll No. with following details already exists : \n");
            Student_printDetails_no_attr(&obj2);
            printf("Insertion Aborted !\n");
            fclose(fl1);
            return;
        } else if (strcmpi(obj.studentName, obj2.studentName) == 0) {
            if (!v)                             // Warns user that Record with same name exists
                printf("Warning : Record with same name exists with follwing details : \n");
            Student_printDetails_no_attr(&obj2);
            printf("\n");
            v = 1;
        }
    }
    if (v) {
        printf("Do you still wish to insert record (Y/N) ? ");
        do {                                    // Asks for user confirmation after warning
            ch = getchar();
            ch = toupper(ch);
        } while (ch != 'Y' && ch != 'N');
        if (ch == 'N') {
            printf("Insertion Aborted !\n");
            fclose(fl1);
            return;
        }
    }
    fl2 = fopen(FLBSTUD, "ab");
    fwrite(&obj, sizeof(obj), 1, fl2);
    fclose(fl1);
    fclose(fl2);
    printf("Record Inserted successfully !\n");
}

void insertClass() {                            // Insert Class Record in File
    CLS();
    Class obj, obj2;
    char ch;
    int v = 0;
    printf("Enter Class Details :\n");
    Class_printDetails_no_attr(&obj);
    FILE* fl1 = fopen(FLBCLAS, "rb");
    FILE* fl2;
    if (!fl1) {                              // Create new file if it does not exist
        fl2 = fopen(FLBCLAS, "wb");
        fwrite(&obj, sizeof(obj), 1, fl2);
        fclose(fl2);
        printf("Record Inserted successfully !\n");
        return;
    }
    while (fread(&obj2, sizeof(obj), 1, fl1) == 1) {
        if (feof(fl1)) {
            break;
        }
        if (obj.rollNo == obj2.rollNo) {          // Abort if same Roll No already exists
            printf("Record with same Roll No. with following details already exists : \n");
            Class_printDetails_no_attr(&obj2);
            printf("Insertion Aborted !\n");
            fclose(fl1);
            return;
        } else if (strcmpi(obj.studentName, obj2.studentName) == 0) {
            if (!v)                                 // Warns user if record with same Roll No. Already Exists
                printf("Warning : Record with same name exists with follwing details : \n");
            Class_printDetails_no_attr(&obj2);
            printf("\n");
            v = 1;
        }
    }
    if (v) {                                    // Asks for confirmation after warning
        printf("Do you still wish to insert record (Y/N) ? ");
        do {
            ch = getchar();
            ch = toupper(ch);
        } while (ch != 'Y' && ch != 'N');
        if (ch == 'N') {
            printf("Insertion Aborted !\n");
            fclose(fl1);
            return;
        }
    }
    fl2 = fopen(FLBCLAS, "ab");
    fwrite(&obj, sizeof(obj), 1, fl2);
    fclose(fl1);
    fclose(fl2);
    printf("Record Inserted successfully !\n");
}
int dispClassRecord() {             // Display all Class Records
    Class obj;
    int v = 0;
    FILE* fl = fopen(FLBCLAS, "rb");
    if (!fl) {                      // If file does not exist
        printf("Empty Records !\n");
        return 0;
    }
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        v = 1;
        Class_printDetails_no_attr(&obj);
        RULE('-');
    }
    fclose(fl);
    if (!v)
        printf("Empty Records !\n");
    return v;
}

int dispStudentRecord() {           // Display all Student Records
    CLS();
    Student obj;
    int v = 0;
    FILE* fl = fopen(FLBSTUD, "rb");
    if (!fl) {                      // If file does not exist
        printf("Empty Records !\n");
        return 0;
    }
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        v = 1;
        Student_printDetails_no_attr(&obj);
        RULE('-');
    }
    fclose(fl);
    if (!v)
        printf("Empty Records !\n");
    return v;
}
int searchClassID(const char* str) {        // Searching Class Record by different Attributes
    FILE* fl = fopen(FLBCLAS, "rb");
    if (!fl) {                              // If file does not exist
        printf("No Records Found !\n");
        return 0;
    }
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) == 0) {                   // If file is empty
        printf("No Records Found !\n");
        fclose(fl);
        return 0;
    }
    fseek(fl, 0, SEEK_SET);
    printf("Enter class to %s (0 to disable) : ", str); // 0 to search independent of class
    int cl;
    char ch;
    char query[30];
    Class obj;
    int found = 0;
    do {
        scanf("%d", &cl);
    } while (cl > 12 || cl < 0);
    printf("Enter Attribute to search :\n");
    printf("  (N)ame of Student.\n");
    printf("  (S)ubject.\n");
    printf("Enter your choice : ");
    do {
        scanf(" %c", &ch);
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'S');
    printf("Enter Query : ");
    scanf("%s", query);

    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        if (cl == 0 || cl == obj.classID) {       // Check class directly
            if ((strcmpi(query, ch == 'N' ? obj.studentName : obj.subject) == 0)) {
                if (!found)
                    printf("\nSearch Results : \n\n");
                Class_printDetails_no_attr(&obj);
                RULE('-');
                found = 1;
            }
        }
    }
    if (!found)
        printf("No Records Found !\n");
    fclose(fl);
    return found;
}

int searchStudentID(const char* str) {      // Search Student by Attributes
    CLS();
    FILE* fl = fopen(FLBSTUD, "rb");
    if (!fl) {                              // If file does not exist
        printf("No Records Found !\n");
        return 0;
    }
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) == 0) {                   // If file is empty
        printf("No Records Found !\n");
        fclose(fl);
        return 0;
    }
    fseek(fl, 0, SEEK_SET);
    char ch;
    char query[30];
    Student obj;
    int found = 0;
    printf("Enter Attribute to %s :\n", str);
    printf("  (T)itle.\n");
    printf("  (N)ame of Student.\n");
    printf("  (F)ather's Name.\n");
    printf("  (M)other's Name.\n");
    printf("  (A)ddress.\n");
    printf("  (B)lood Group.\n");
    printf("Enter your choice : ");
    do {
        scanf(" %c", &ch);
        ch = toupper(ch);
    } while (ch != 'T' && ch != 'N' && ch != 'F' && ch != 'M' && ch != 'A' && ch != 'B');
    printf("\nEnter Query : ");
    scanf("%s", query);
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        // Compare query with the appropriate attribute based on user's choice
        int match = 0;
        switch (ch) {
            case 'T':
                match = strcmpi(query, obj.title) == 0;
                break;
            case 'N':
                match = strcmpi(query, obj.studentName) == 0;
                break;
            case 'F':
                match = strcmpi(query, obj.fatherName) == 0;
                break;
            case 'M':
                match = strcmpi(query, obj.motherName) == 0;
                break;
            case 'A':
                match = strcmpi(query, obj.address) == 0;
                break;
            case 'B':
                match = strcmpi(query, obj.bloodGroup) == 0;
                break;
        }
        
        if (match) {
            if (!found)
                printf("\nSearch Results : \n\n");
            Student_printDetails_no_attr(&obj);
            RULE('-');
            found = 1;
        }
    }
    if (!found)
        printf("No Records Found !\n");
    fclose(fl);
    return found;
}
int searchByRollNo(int i) {            // Search Record by Roll No., 1 for Class, 2 for Student
    CLS();
    int r;
    if (i == 1) {
        Class obj;
        int found = 0;
        int cl;
        printf("Enter class to search in (0 to disable) : ");  // 0 to search independent of class
        do {
            scanf("%d", &cl);
        } while (cl > 12 || cl < 0);
        printf("Enter Roll No. to search for : ");
        scanf("%d", &r);
        FILE* fl = fopen(FLBCLAS, "rb");
        if (!fl) {                              // No file exists
            printf("No Records Found !\n");
            return 0;
        }
        while (fread(&obj, sizeof(obj), 1, fl) == 1) {
            if (CL(cl, obj.classID)) {           
                if (r == obj.rollNo) {                // Match attribute for each Record
                    if (!found)
                        printf("\nSearch Results : \n\n");
                    Class_printDetails_no_attr(&obj);
                    RULE('-');
                    found = 1;
                }
            }
        }
        if (!found)
            printf("No Records Found !\n");
        fclose(fl);
        return found;
    } else {
        int found = 0;
        Student obj;
        printf("Enter Roll No. to search for : ");
        scanf("%d", &r);
        FILE* fl = fopen(FLBSTUD, "rb");
        if (!fl) {                  // No file exists
            printf("No Records Found !\n");
            return 0;
        }
        while (fread(&obj, sizeof(obj), 1, fl) == 1) {
            if (r == obj.rollNo) {
                if (!found)
                    printf("\nSearch Results : \n\n");
                Student_printDetails_no_attr(&obj);
                RULE('-');
                found = 1;
            }
        }
        if (!found)
            printf("No Records Found !\n");
        fclose(fl);
        return found;
    }
}
typedef struct {
    char str[100]; // Định nghĩa mảng ký tự để lưu trữ chuỗi
    int rollNo;    // Số nguyên để lưu trữ số thứ tự lớp
} StringIntPair;

void sortByStudents(char ch) {
    StringIntPair *lst = NULL;
    int list_size = 0;
    int i;

    if (ch == 'C') {
        // Sort Class Records
        Class obj;
        int v = 0;
        FILE* fl = fopen(FLBCLAS, "rb");
        if (!fl) {
            printf("Empty Records !\n");
            return;
        }
        while (fread(&obj, sizeof(Class), 1, fl) == 1) {
            v = 1;
            lst = realloc(lst, (list_size + 1) * sizeof(StringIntPair));
            strcpy(lst[list_size].str, obj.studentName);
            lst[list_size].rollNo = obj.rollNo;
            list_size++;
        }
        fclose(fl);
        if (v == 0) {
            printf("Empty Records !\n");
            return;
        }
        qsort(lst, list_size, sizeof(StringIntPair), strcmpis);  // Sort using qsort and Custom Comparison
        FILE* tmp = fopen("temp.txt", "wb");
        fl = fopen(FLBCLAS, "rb");
        for (i = 0; i < list_size; i++) {
            fseek(fl, 0, SEEK_SET);
            while (fread(&obj, sizeof(Class), 1, fl) == 1) {
                if (obj.rollNo == lst[i].rollNo) {       // Check each Roll No. from each pair and write record to new file
                    fwrite(&obj, sizeof(Class), 1, tmp);
                }
            }
        }
        fclose(fl);
        fclose(tmp);
        remove(FLBCLAS);
        rename("temp.txt", FLBCLAS);
        printf("\nThe Records have been successfully sorted !\n\n");
        dispClassRecord();
    } else {
        // Sort Student Records
        Student obj;
        int v = 0;
        char c;
        FILE* fl = fopen(FLBSTUD, "rb");
        CLS();
        printf("Enter criteria to sort :\n");
        printf("  (N)ame of Student.\n");
        printf("  (T)itle.\n");
        printf("Enter your choice : \n");
        do {
            scanf(" %c", &c);
            c = toupper(c);
        } while (c != 'N' && c != 'T');
        if (!fl) {
            printf("Empty Records !\n");
            return;
        }
        while (fread(&obj, sizeof(Student), 1, fl) == 1) {
            v = 1;
            lst = realloc(lst, (list_size + 1) * sizeof(StringIntPair));
            if (c == 'N') {
                strcpy(lst[list_size].str, obj.studentName);
            } else if (c == 'T') {
                strcpy(lst[list_size].str, obj.title);
            }
            lst[list_size].rollNo = obj.rollNo;
            list_size++;
        }
        fclose(fl);
        if (v == 0) {
            printf("Empty Records !\n");
            return;
        }
        qsort(lst, list_size, sizeof(StringIntPair), strcmpis);  // Sort using qsort and Custom Comparison
        FILE* tmp = fopen("temp.txt", "wb");
        fl = fopen(FLBSTUD, "rb");
        for (i = 0; i < list_size; i++) {
            fseek(fl, 0, SEEK_SET);
            while (fread(&obj, sizeof(Student), 1, fl) == 1) {
                if (obj.rollNo == lst[i].rollNo) {       // Check each Roll No. from each pair and write record to new file
                    fwrite(&obj, sizeof(Student), 1, tmp);
                }
            }
        }
        fclose(fl);
        fclose(tmp);
        remove(FLBSTUD);
        rename("temp.txt", FLBSTUD);
        printf("\nThe Records have been successfully sorted !\n\n");
        dispStudentRecord();
    }

    free(lst);  // Free the allocated memory
}
void delClassRecord() {         // Delete Class Records
    CLS();
    Class obj;                  // Writes to new file except record to be deleted
    int f = 0;
    if (!searchClassID("delete from"))
        return;
    printf("\nEnter Roll No. to delete : ");
    int r;
    char ch;
    scanf("%d", &r);
    FILE* fl = fopen(FLBCLAS, "rb");
    FILE* fo = fopen("temp.dat", "wb");
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        if (r == obj.rollNo) {
            printf("Record with following info will be deleted :\n\n");
            Class_printDetails_no_attr(&obj);
            printf("Do you wish to continue ? (Y/N) : ");
            do {
                scanf(" %c", &ch);
                ch = toupper(ch);
            } while (ch != 'N' && ch != 'Y');
            if (ch == 'N') {
                printf("Deletion Aborted !\n");
                fclose(fl);
                fclose(fo);
                remove("temp.dat");
                return;
            }
            f = 1;
            continue;
        }
        fwrite(&obj, sizeof(obj), 1, fo);
    }
    fclose(fl);
    fclose(fo);
    remove(FLBCLAS);
    rename("temp.dat", FLBCLAS);
    if (f)
        printf("Record Successfully Deleted !\n");
    else
        printf("No Such Record Exists !\n");
}

void delStudentRecord() {           // Delete Student Records
    CLS();
    Student obj;                    // Writes to new file except record to be deleted
    int f = 0;
    if (!searchStudentID("delete using"))
        return;
    printf("\nEnter Roll No. to delete : ");
    int r;
    char ch;
    scanf("%d", &r);
    FILE* fl = fopen(FLBSTUD, "rb");
    FILE* fo = fopen("temp.dat", "wb");
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        if (r == obj.rollNo) {
            printf("Record with following info will be deleted :\n\n");
            Student_printDetails_no_attr(&obj);
            printf("Do you wish to continue ? (Y/N) : ");
            do {
                scanf(" %c", &ch);
                ch = toupper(ch);
            } while (ch != 'N' && ch != 'Y');
            if (ch == 'N') {
                printf("Deletion Aborted !\n");
                fclose(fl);
                fclose(fo);
                remove("temp.dat");
                return;
            }
            f = 1;
            continue;
        }
        fwrite(&obj, sizeof(obj), 1, fo);
    }
    fclose(fl);
    fclose(fo);
    remove(FLBSTUD);
    rename("temp.dat", FLBSTUD);
    if (f)
        printf("Record Successfully Deleted !\n");
    else
        printf("No Such Record Exists !\n");
}
int checkNoInClass() {             // Prints total number of students in each class
    CLS();
    int cl[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, i, found = 0;
    Class obj;
    int cnt = 0;
    FILE* fl = fopen(FLBCLAS, "rb");
    if (!fl) {
        printf("No Records Found !\n");
        return 0;
    }
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        found = 1;
        cl[obj.classID - 1]++;           // Gets each record from file and stores count of each class [c-p cp]
    }
    if (!found)
        printf("No Records Found !\n");
    fclose(fl);
    printf("\tNumber of Students in :\n");
    for (i = 0; i < 12; i++) {
        printf("\t\tClass %d%s    :\t%3d\n", i + 1, (i > 8) ? " " : "  ", cl[i]);
        cnt += cl[i];
    }
    printf("\t\t-------------------\n");
    printf("\t\tTotal Number :\t%3d\n", cnt);
    printf("\t\t-------------------\n");
    return found;
}

int dispByStandard() {             // Display each Class record by Standard
    Class obj;
    int v = 0, cl = 1, cnt;
    FILE* fl = fopen(FLBCLAS, "rb");
    if (!fl) {
        printf("No Records Found !\n");
        return 0;
    }
    for (cl = 1; cl <= 12; cl++) {
        cnt = 0;
        fseek(fl, 0, SEEK_SET);
        while (fread(&obj, sizeof(obj), 1, fl) == 1) {
            v = 1;
            if (obj.classID == cl) {
                if (cnt == 0) {
                    RULE('*');
                    printf("\t\t\t\t  Class %d\n", cl);
                    RULE('*');
                    cnt = 1;
                }
                Class_printDetails(&obj,0);
                RULE('-');
            }
        }
    }
    fclose(fl);
    if (!v)
        printf("No Records Found !\n");
    return v;
}
int totalRevenueGenerated() {            // Calculates total fee based on Total=Sum(Fee for Each class  * Total students in that class)
    CLS();
    int i, found = 0;
    Class obj;
    int total = 0;
    FILE* fl = fopen(FLBCLAS, "rb");
    if (!fl) {
        printf(" \n\n   Total Fee Revenue Generated  : \t%d.00\n", total);
        return 0;
    }
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        found = 1;
        total += fee[obj.classID - 1];
    }
    fclose(fl);
    printf(" \n\n   Total Fee Revenue Generated  : \t%d.00\n", total);
    return found;
}

void modEntry(char c) {                // Modify Record Entry
    CLS();
    if (c == 'C') {
        Class obj;
        if (!searchClassID("search for"))
            return;                     // Searches for Records and Modifies using Roll No. based on attribute
        FILE* fl = fopen(FLBCLAS, "rb+");
        int r, pos;
        char ch;
        int found = 0;
        printf("Enter Roll No. of Record to modify : ");
        do {
            scanf("%d", &r);
        } while (r < 1);
        while (fread(&obj, sizeof(obj), 1, fl) == 1) {
            pos = ftell(fl);
            if (r == obj.rollNo) {
                printf("\n");
                fseek(fl, pos - sizeof(obj), SEEK_SET);
                printf("Enter Attribute to modify :\n");
                printf("  (N)ame of Student.\n");
                printf("  (C)lass Standard.\n");
                printf("  (R)oll No.\n");
                printf("  (S)ubject.\n");
                printf("Enter your choice : ");
                do {
                    scanf(" %c", &ch);
                    ch = toupper(ch);
                } while (ch != 'N' && ch != 'C' && ch != 'R' && ch != 'S');
                Class_printDetails(&obj, ch);
                Class_printDetails_no_attr(&obj);
                fseek(fl, pos - sizeof(obj), SEEK_SET);
                fwrite(&obj, sizeof(obj), 1, fl);
                RULE('-');
                found = 1;
                break;
            }
        }
        fclose(fl);
        return;
    }
    Student obj;
    if (!searchStudentID("search for"))
        return;                 // Searches for Records and Modifies using Roll No. based on attribute
    FILE* fl = fopen(FLBSTUD, "rb+");
    int r, pos;
    char ch;
    int found = 0;
    printf("Enter Roll No. of Record to modify : ");
    do {
        scanf("%d", &r);
    } while (r < 1);
    while (fread(&obj, sizeof(obj), 1, fl) == 1) {
        pos = ftell(fl);
        if (r == obj.rollNo) {
            printf("\n");
            fseek(fl, pos - sizeof(obj), SEEK_SET);
            printf("Enter Attribute to modify :\n");
            printf("  (T)itle.\n");
            printf("  (N)ame of Student.\n");
            printf("  (R)oll No.\n");
            printf("  (F)ather's Name.\n");
            printf("  (M)other's Name.\n");
            printf("  (A)ddress.\n");
            printf("  (B)lood Group.\n");
            printf("Enter your choice : ");
            do {
                scanf(" %c", &ch);
                ch = toupper(ch);
            } while (ch != 'T' && ch != 'N' && ch != 'R' && ch != 'F' && ch != 'M' && ch != 'A' && ch != 'B');
            Student_printDetails(&obj, ch);
            Student_printDetails_no_attr(&obj);
            fseek(fl, pos - sizeof(obj), SEEK_SET);
            fwrite(&obj, sizeof(obj), 1, fl);
            RULE('-');
            found = 1;
            break;
        }
    }
    fclose(fl);
}

int main() {
    char ch;
    char ch1;
    int ch2;
    load();
    do {
        system("CLS");
        printf("****************************************************************\n");
        printf("\t\t\t    School Management System\n");
        printf("****************************************************************\n");
        printf("1. Student Database Management.\n");
        printf("2. Class Database Management.\n");
        printf("0. Exit.\n\n");
        printf("Enter your choice : ");
        fflush(stdin);
        ch1 = getchar();
        if (ch1 == '1') {
            fflush(stdin);
            load();
            do {
                system("CLS");
                printf("****************************************************************\n");
                printf("\t\t\t    School Management System\n");
                printf("****************************************************************\n");
                printf("\t\t\tStudent Database Management System\n");
                printf("---------------------------------------------------------------\n");
                printf("1.  Insert Records.\n");
                printf("2.  Display all Records.\n");
                printf("3.  Search for a Record using Roll No.\n");
                printf("4.  Search for a Record using other Attributes.\n");
                printf("5.  Sort all Records.\n");
                printf("6.  Modify a Record.\n");
                printf("7.  Delete a Record.\n");
                printf("0.  Exit.\n");
                printf("\nEnter your choice : ");
                ch2 = scan();
                switch (ch2) {
                    case 1:
                        insertStudent();
                        break;
                    case 2:
                        dispStudentRecord();
                        break;
                    case 3:
                        searchByRollNo(2);
                        break;
                    case 4:
                        {
                          char searchAttribute[] = {'S', '\0'}; // Tạo một mảng ký tự chứa ký tự 'S'
                          searchStudentID(searchAttribute); // Truyền con trỏ của mảng đó tới hàm
                        }
                        break;
                    case 5:
                        sortByStudents('S');
                        break;
                    case 6:
                        modEntry('S');
                        break;
                    case 7:
                        delStudentRecord();
                        break;
                }
                fflush(stdin);
                if (ch2)
                    ch = getchar();
                else
                    load();
            } while (ch2 != 0);
        }
        if (ch1 == '2') {
            fflush(stdin);
            load();
            do {
                system("CLS");
                printf("****************************************************************\n");
                printf("\t\t\t     Class Management System\n");
                printf("****************************************************************\n");
                printf("\t\t\tClass Database Management System\n");
                printf("---------------------------------------------------------------\n");
                printf("1.  Insert Records.\n");
                printf("2.  Display all Records.\n");
                printf("3.  Search for a Record using Roll No.\n");
                printf("4.  Search for a Record using other Attributes.\n");
                printf("5.  Sort all Records.\n");
                printf("6.  Modify a Record.\n");
                printf("7.  Delete a Record.\n");
                printf("8.  Display Total Number of Students in Each Class.\n");
                printf("9.  Display Students by Standard.\n");
                printf("10. Display Total Fee Revenue Generated.\n");
                printf("0.  Exit.\n");
                printf("\nEnter your choice : ");
                ch2 = scan();
                switch (ch2) {
                    case 1:
                        insertClass();
                        break;
                    case 2:
                        dispClassRecord();
                        break;
                    case 3:
                        searchByRollNo(1);
                        break;
                    case 4:
                        {
                          char searchAttribute[] = {'C', '\0'}; // Tạo một mảng ký tự chứa ký tự 'C'
                          searchClassID(searchAttribute); // Truyền con trỏ của mảng đó tới hàm
                        }
                        break;
                    case 5:
                        sortByStudents('C');
                        break;
                    case 6:
                        modEntry('C');
                        break;
                    case 7:
                        delClassRecord();
                        break;
                    case 8:
                        checkNoInClass();
                        break;
                    case 9:
                        dispByStandard();
                        break;
                    case 10:
                        totalRevenueGenerated();
                        break;
                }
                fflush(stdin);
                if (ch2)
                    ch = getchar();
                else
                    load();
            } while (ch2 != 0);
        }
    } while (ch1 != '0');
    system("CLS");
    return 0;
}
