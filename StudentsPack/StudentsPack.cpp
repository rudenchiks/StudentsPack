﻿//Students Pack

#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

    void evalSt(Student& student, int mark1, int mark2, int mark3) const {
        student.getMarks(mark1, mark2, mark3);
    }

};

class GradeBook {
public:
    vector<Student> students;
    vector<Teacher> teachers;

    void addStudent(const Student& student) {
        students.push_back(student); //в массив добавляем инфу о студентах
    }

    void SetMarks(Student& student, int m1, int m2, int m3) {
        student.getMarks(m1, m2, m3);
    }

    void addTeacher(const Teacher& teacher) {
        teachers.push_back(teacher);
    }

    int findTeacher(const string& teacherName) const {
        for (size_t i = 0; i < teachers.size(); ++i) {
            if (teachers[i].name == teacherName) {
                return int(i);
            }
        }
        return -1; // Возвращаем -1, если преподаватель не найден
    }

    int findStudent(const string& studentName) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].name == studentName) {
                return int(i);
            }
        }
        return -1; // Возвращаем -1, если студент не найден
    }

    void PrintInfo() const {
        for (const auto& student : students) {
            student.InfoStudent();
        }
    }
};


int main() {

    setlocale(0, "");

    GradeBook gradeBook;

    // Добавление студентов
    int numStudents;
    cout << "Enter the number of students: ";
    cin >> numStudents;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера

    for (int i = 0; i < numStudents; ++i) {
        Student student;
        cout << "Enter student name: ";
        getline(cin, student.name);
        gradeBook.addStudent(student);
    }

    // Добавление преподавателей
    int numTeachers;
    cout << "Enter the number of teachers: ";
    cin >> numTeachers;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очистка буфера

    for (int i = 0; i < numTeachers; ++i) {
        Teacher teacher;
        cout << "Enter teacher name: ";
        getline(cin, teacher.name);
        gradeBook.addTeacher(teacher);
    }

    // Выбор преподавателя для выставления оценок
    string teacherName;
    int teacherIndex;

    do {
        cout << "Enter teacher name to evaluate students: ";
        getline(cin, teacherName);
        teacherIndex = gradeBook.findTeacher(teacherName);

        if (teacherIndex == -1) {
            cout << "Teacher is not found. Please enter another teacher name." << endl;
        }
    } while (teacherIndex == -1);

    // Процесс выставления оценок студентам
    do {
        // Выбор студента для выставления оценок
        string studentName;
        int studentIndex;

        do {
            cout << "Enter student name to evaluate: ";
            getline(cin, studentName);
            studentIndex = gradeBook.findStudent(studentName);

            if (studentIndex == -1) {
                cout << "Student is not found. Please enter another student name." << endl;
            }
        } while (studentIndex == -1);

        // Преподаватель выставляет оценки студенту
        int mark1, mark2, mark3;
        cout << "Enter marks for " << gradeBook.students[studentIndex].name << ": ";
        cin >> mark1 >> mark2 >> mark3;
        gradeBook.teachers[teacherIndex].evalSt(gradeBook.students[studentIndex], mark1, mark2, mark3);

        // Выводим инфу о выбранном студенте
        gradeBook.students[studentIndex].InfoStudent();

        // поставить оценку другому студенту?
        char another;
        cout << "Do you want to evaluate another student? (y/n): ";
        cin >> another;

        // Очистка буфера и игнорирование лишних символов
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (tolower(another) != 'y') {
            break; // Выход из цикла, если пользователь не хочет оценивать еще студентов
        }
    } while (true);

    // Выводим общую информацию о студентах после завершения оценивания
    cout << "Final information about students:" << endl;
    gradeBook.PrintInfo();

    return 0;
}