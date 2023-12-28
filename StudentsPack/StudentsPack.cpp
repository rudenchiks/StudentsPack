#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants to define teacher moods
const int GOOD = 1;
const int BAD = 2;

class Student {
public:
    string name;
    int mark_sum;

    void getMarks(int m1, int m2, int m3) {
        mark_sum = (m1 + m2 + m3) / 3;
    }

    bool isExcellentStudent() const {
        return mark_sum >= 4.5;
    }

    void InfoStudent() const {
        cout << "An average rating of " << name << ": " << mark_sum << endl;

        if (isExcellentStudent()) {
            cout << name << " Is an excellent student." << endl;
        }
        else {
            cout << name << " Is not an excellent student." << endl;
        }
    }
};

class Teacher {
public:
    string name;
    int mood;

    Teacher() : mood(GOOD) {}

    Teacher(string teacherName, int teacherMood) : name(teacherName), mood(teacherMood) {}

    void evalSt(Student& student, int mark1, int mark2, int mark3) const {
        student.getMarks(mark1, mark2, mark3);
    }

    int calculateFinalMark(int mark1, int mark2, int mark3, bool isExcellent) const {
        int baseMark = (mark1 + mark2 + mark3) / 3;

        if (mood == GOOD) {
            if (isExcellent) {
                return 5;
            }
            else {
                return 4;
            }
        }
        else { // mood == BAD
            return (rand() % 2 == 0) ? 4 : 5;
        }
    }
};

class Class {
public:
    string className;
    Teacher teacher;
    vector<Student> students;

    Class(string name, const Teacher& teacher) : className(name), teacher(teacher) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }
};

class GradeBook {
public:
    vector<Class> classes;

    void addClass(const Class& newClass) {
        classes.push_back(newClass);
    }

    void addStudentToClass(const string& className, const Student& student) {
        for (auto& classObj : classes) {
            if (classObj.className == className) {
                classObj.addStudent(student);
                break;
            }
        }
    }

    void SetMarks(const string& className, const string& teacherName, const string& studentName,
        int m1, int m2, int m3) {
        for (auto& classObj : classes) {
            if (classObj.className == className && classObj.teacher.name == teacherName) {
                for (auto& student : classObj.students) {
                    if (student.name == studentName) {
                        classObj.teacher.evalSt(student, m1, m2, m3);
                        break;
                    }
                }
                break;
            }
        }
    }

    void PrintInfo() const {
        for (const auto& classObj : classes) {
            cout << "Class: " << classObj.className << endl;
            for (const auto& student : classObj.students) {
                student.InfoStudent();
            }
        }
    }
};

int main() {
    setlocale(0, "");

    GradeBook gradeBook;

    // Add classes
    int numClasses;
    cout << "Enter the number of classes: ";
    cin >> numClasses;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < numClasses; ++i) {
        string className, teacherName;
        Teacher teacher;

        cout << "Enter class name for class " << (i + 1) << ": ";
        getline(cin, className);

        cout << "Enter teacher name for class " << className << ": ";
        getline(cin, teacherName);

        teacher = Teacher(teacherName, GOOD);

        Class newClass(className, teacher);
        gradeBook.addClass(newClass);

        // Add students to the class
        int numStudents;
        cout << "Enter the number of students for class " << className << ": ";
        cin >> numStudents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int j = 0; j < numStudents; ++j) {
            Student student;
            cout << "Enter student name for class " << className << ": ";
            getline(cin, student.name);

            int mark1, mark2, mark3;
            cout << "Enter marks for " << student.name << " in class " << className << " (separated by spaces): ";
            cin >> mark1 >> mark2 >> mark3;

            // Set marks for the student
            student.getMarks(mark1, mark2, mark3);

            // Add the student to the class
            newClass.addStudent(student);

            // Print the average mark for the student
            cout << "Average mark for " << student.name << ": " << student.mark_sum << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline from the buffer
        }
    }

    // Print final information
    gradeBook.PrintInfo();

    return 0;
}