#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants to define teacher and parent moods
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
            cout << name << " is an excellent student." << endl;
        }
        else {
            cout << name << " is not an excellent student." << endl;
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

class Parent {
public:
    string name;
    int mood;

    Parent() : mood(GOOD) {}

    Parent(string parentName, int parentMood) : name(parentName), mood(parentMood) {}

    void tellAboutAllChildren(const vector<Student>& children) const {
        cout << "Information about all children:" << endl;
        for (const auto& child : children) {
            tellAboutChild(child);
        }
    }

    void tellAboutChild(const Student& child) const {
        cout << "Information about " << child.name << ":" << endl;
        if (mood == GOOD) {
            cout << "I am a happy parent." << endl;
            if (child.isExcellentStudent()) {
                cout << child.name << " is an excellent student." << endl;
            }
            else {
                cout << child.name << " is not an excellent student." << endl;
            }
        }
        else {
            cout << "I am not in a good mood." << endl;
            cout << child.name << " is doing okay." << endl;
        }
    }

    void tellRandomChildInfo(const vector<Student>& children) const {
        if (!children.empty()) {
            int randomIndex = rand() % children.size();
            tellAboutChild(children[randomIndex]);
        }
        else {
            cout << "No children to talk about." << endl;
        }
    }

    void tellAboutSpecificChild(const vector<Student>& children, const string& childName) const {
        bool found = false;
        for (const auto& child : children) {
            if (child.name == childName) {
                tellAboutChild(child);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Error: Child with name " << childName << " not found." << endl;
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

    gradeBook.PrintInfo();

    Parent parent("ParentName", GOOD);
    


    // Add a menu for parents
    int choice;

    cout << "Parent menu:" << endl;
    cout << "1. To tell about a particular child" << endl;
    cout << "2. To tell about every child" << endl;
    cout << "3. To tell about all children in sum" << endl;
    cout << "0. Exti" << endl;
    cout << "Choose: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string childName, childInfo;
        cout << "Enter the child's name: ";
        getline(cin, childName);
        cout << "Enter the information about the children: ";
        getline(cin, childInfo);

        parent.tellAboutChild(Student{ childName, 0 });
        cout << "Information about the children " << childName << ": " << childInfo << endl;
        break;
    }
    case 2: {
        int numChildren;
        cout << "Enter the number of children: ";
        cin >> numChildren;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < numChildren; ++i) {
            string childName, childInfo;
            cout << "Enter the child's name " << (i + 1) << ": ";
            getline(cin, childName);
            cout << "Enter the information about the child " << childName << ": ";
            getline(cin, childInfo);

            parent.tellAboutChild(Student{ childName, 0 }); 
            cout << "Information about the child " << childName << ": " << childInfo << endl;
        }
        break;
    }
    case 3: {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter information about all children: ";
        string allChildrenInfo;
        getline(cin, allChildrenInfo);
        //parent.tellAboutAllChildren(gradeBook.classes[0].students);
        cout << "Information about all children: " << allChildrenInfo << endl;
        break;
    }
    case 0:
        cout << "Exit the code." << endl;
        break;
    default:
        cout << "Incorrect." << endl;
        break;
    }



    return 0;
}