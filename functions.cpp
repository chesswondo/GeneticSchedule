#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
#include <functional>
#include <array>

#include "constants.h"
#include "classes.h"

// Find max students by auditorium number
int findMaxStudents(const std::vector<Auditorium>& auditoriums, int auditoriumId) {
    auto it = std::find_if(auditoriums.begin(), auditoriums.end(),
        [auditoriumId](const Auditorium& a) {
            return a.auditoriumId == auditoriumId;
        });

    if (it != auditoriums.end()) {
        return it->maxStudents;
    }
    throw std::runtime_error("Auditorium ID not found");
}

// Find number of students in group by its id
int findGroupStudents(const std::vector<Group>& groups, int groupId) {
    auto it = std::find_if(groups.begin(), groups.end(),
        [groupId](const Group& g) {
            return g.id == groupId;
        });

    if (it != groups.end()) {
        return it->overallStudents;
    }
    throw std::runtime_error("Group ID not found");
}

// Find group Name by Id
std::string groupNameById(const std::vector<Group>& groups, int groupId) {
    auto it = std::find_if(groups.begin(), groups.end(),
        [groupId](const Group& g) {
            return g.id == groupId;
        });

    if (it != groups.end()) {
        return it->name;
    }
    throw std::runtime_error("Group ID not found");
}

// Find teacher Name by Id
std::string teacherNameById(const std::vector<Teacher>& teachers, int teacherId) {
    auto it = std::find_if(teachers.begin(), teachers.end(),
        [teacherId](const Teacher& t) {
            return t.id == teacherId;
        });

    if (it != teachers.end()) {
        return it->name;
    }
    throw std::runtime_error("Teacher ID not found");
}

// Find course Name by Id
std::string courseNameById(const std::vector<Course>& courses, int courseId) {
    auto it = std::find_if(courses.begin(), courses.end(),
        [courseId](const Course& c) {
            return c.id == courseId;
        });

    if (it != courses.end()) {
        return it->name;
    }
    throw std::runtime_error("Course ID not found");
}