#include <iostream>
#include <algorithm>
#include <numeric>
#include <array>

constexpr size_t NUM_STUDENTS = 5;
constexpr uint_fast8_t MARK_NUM = 4;

struct Student {
    std::string name;
    std::array<unsigned int, MARK_NUM> marks{};
};

double calculateAverage(const Student& student) {
    return std::accumulate(student.marks.begin(), student.marks.end(), 0.0) / MARK_NUM;
}

const Student* findBestStudent(const Student* const students, const size_t size) {
    return size ? std::max_element(students, students + size, [](const Student& a, const Student& b) {
        return calculateAverage(a) < calculateAverage(b);
        }) : nullptr;
}

unsigned int countAboveAverage(const Student* const students, const size_t size, const double threshold) {
    return std::count_if(students, students + size, [threshold](const Student& s) {
        return calculateAverage(s) > threshold;
        });
}

void getBestStudents(const Student* const inStudents, const size_t inSize, Student* const outStudents, size_t& outSize, const unsigned int percent) {
    outSize = std::min((percent * inSize) / 100, inSize);
    std::partial_sort_copy(inStudents, inStudents + inSize, outStudents, outStudents + outSize, [](const Student& s1, const Student& s2) {
        return calculateAverage(s1) > calculateAverage(s2);
        });
}
int main() {
    const std::array<Student, NUM_STUDENTS> students = { {
                                                                { "1_Student", { 90, 85, 95, 80 } },
                                                                { "2_Student", { 80, 75, 45, 90 } },
                                                                { "3_Student", { 95, 90, 85, 80 } },
                                                                { "4_Student", { 75, 80, 70, 85 } },
                                                                { "5_Student", { 35, 90, 80, 75 } }
                                                        } };

    for (const Student& student : students)
        std::cout << student.name << "'s average: " << calculateAverage(student) << '\n';

    const Student* const bestStudent = findBestStudent(students.data(), students.size());
    if (bestStudent) std::cout << "Best student: " << bestStudent->name << '\n';

    constexpr double threshold = 80.0;
    const unsigned int aboveThreshold = countAboveAverage(students.data(), students.size(), threshold);
    std::cout << "Number of students with average above " << threshold << ": " << aboveThreshold << '\n';

    constexpr unsigned int N_PERCENT = 40;
    size_t outSize;
    std::array<Student, NUM_STUDENTS> bestStudents;
    getBestStudents(students.data(), students.size(), bestStudents.data(), outSize, N_PERCENT);
    std::cout << "Top " << N_PERCENT << "% students:\n";
    for (size_t i = 0; i < outSize; ++i) std::cout << bestStudents[i].name << '\n';

    return 0;
}