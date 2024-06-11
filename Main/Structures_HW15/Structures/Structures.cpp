#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int marks[4];
};

double calculateAverage(const Student& student) {
    double sum = 0;
    for (int mark : student.marks) {
        sum += mark;
    }
    return sum / 4.0;
}

bool compareStudents(const Student& student1, const Student& student2) {
    return calculateAverage(student1) > calculateAverage(student2);
}

Student* findBestStudent(Student* students, unsigned size) {
    if (size == 0) return nullptr;
    Student* bestStudent = &students[0];
    for (unsigned i = 1; i < size; ++i) {
        if (calculateAverage(students[i]) > calculateAverage(*bestStudent)) {
            bestStudent = &students[i];
        }
    }
    return bestStudent;
}

unsigned countAboveAverage(Student* students, unsigned size, double threshold) {
    unsigned count = 0;
    for (unsigned i = 0; i < size; ++i) {
        if (calculateAverage(students[i]) > threshold) {
            count++;
        }
    }
    return count;
}

void getBestStudents(Student* inStudents, unsigned inSize, Student* outStudents, unsigned& outSize, unsigned percent) {
    unsigned count = (percent * inSize) / 100;
    outSize = std::min(count, inSize);
    std::sort(inStudents, inStudents + inSize, compareStudents);
    std::copy(inStudents, inStudents + outSize, outStudents);
}

int main() {
    const unsigned NUM_STUDENTS = 5;
    Student students[NUM_STUDENTS] = {
        {"1_Student", {90, 85, 95, 80}},
        {"2_Student", {80, 75, 45, 90}},
        {"3_Student", {95, 90, 85, 80}},
        {"4_Student", {75, 80, 70, 85}},
        {"5_Student", {35, 90, 80, 75}}
    };

    for (unsigned i = 0; i < NUM_STUDENTS; ++i) {
        std::cout << students[i].name << "'s average: " << calculateAverage(students[i]) << std::endl;
    }

    std::sort(students, students + NUM_STUDENTS, compareStudents);

    Student* bestStudent = findBestStudent(students, NUM_STUDENTS);
    if (bestStudent != nullptr) {
        std::cout << "Best student: " << bestStudent->name << std::endl;
    }

    double threshold = 80.0;
    unsigned aboveThreshold = countAboveAverage(students, NUM_STUDENTS, threshold);
    std::cout << "Number of students with average above " << threshold << ": " << aboveThreshold << std::endl;

    const unsigned N_PERCENT = 40;
    unsigned outSize;
    Student bestStudents[NUM_STUDENTS];
    getBestStudents(students, NUM_STUDENTS, bestStudents, outSize, N_PERCENT);
    std::cout << "Top " << N_PERCENT << "% students:" << std::endl;
    for (unsigned i = 0; i < outSize; ++i) {
        std::cout << bestStudents[i].name << std::endl;
    }

    return 0;
}
