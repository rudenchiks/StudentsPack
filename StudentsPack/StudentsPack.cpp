//Students Pack

#include <iostream>
#include <vector>

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

    void evaluateStudent() const {
        cout << "Средний балл " << name << " : " << mark_sum << endl;

        if (isExcellentStudent()) {
            cout << name << " Отличник/отличница." << endl;
        }
        else {
            cout << name << " не является отличником/отличницей." << endl;
        }
    }
};

class GradeBook {
public:
    vector<Student> students;

    void addStudent(const Student& student) { 
        students.push_back(student); //в массив добавляем инфу о студентах
    }

    void SetMarks(Student& student, int m1, int m2, int m3) {
        student.getMarks(m1, m2, m3);
    }
};

int main() {

    setlocale(0, "");

    GradeBook gradeBook;

    Student student1{"Шишкина Анастасия"};
    Student student2{"Новицкий Алексей"};

    gradeBook.addStudent(student1);
    gradeBook.addStudent(student2);

    gradeBook.SetMarks(student1, 5, 5, 5);
    gradeBook.SetMarks(student2, 3, 4, 5);

    student1.evaluateStudent();
    student2.evaluateStudent();

    return 0;
}