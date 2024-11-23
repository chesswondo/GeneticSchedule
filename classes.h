#pragma once
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

// To use hash of tuple<int, int, bool> as a key in unordered_map
// Here FNV-1a hash is used
template <>
struct std::hash<std::tuple<int, int, bool>> {
    size_t operator()(const std::tuple<int, int, bool>& tup) const {
        int a = std::get<0>(tup);
        int b = std::get<1>(tup);
        bool c = std::get<2>(tup);

        // FNV-1a hash constants
        const size_t fnv_offset_basis = 14695981039346656037ULL;
        const size_t fnv_prime = 1099511628211ULL;

        // Start with offset basis for FNV-1a
        size_t hashVal = fnv_offset_basis;

        // Mix in the integer values and boolean as bytes
        hashVal ^= static_cast<size_t>(a);
        hashVal *= fnv_prime;
        hashVal ^= static_cast<size_t>(b);
        hashVal *= fnv_prime;
        hashVal ^= static_cast<size_t>(c);
        hashVal *= fnv_prime;

        return hashVal;
    }
};

class Teacher;
class Course;

// Class for groups
class Group {
public:
    int id;
    std::string name;
    int firstGroupStudents;
    int secondGroupStudents;
    int overallStudents;
    std::vector<Course> courses;

    // Constructor
    Group(int id, const std::string& name, int firstGroupStudents, int secondGroupStudents, const std::vector<Course>& courses) {
        this->id = id;
        this->firstGroupStudents = firstGroupStudents;
        this->secondGroupStudents = secondGroupStudents;
        this->overallStudents = firstGroupStudents + secondGroupStudents;
        this->name = name;
        this->courses = courses;
    }
};

// Class for courses
class Course {
public:
    int id;
    std::string name;
    int lectureHours;
    int labHours;
    std::vector<Teacher> teachers;

    // Constructor
    Course(int id, const std::string& name, int lectureHours, int labHours, const std::vector<Teacher>& teachers) {
        this->id = id;
        this->name = name;
        this->lectureHours = lectureHours;
        this->labHours = labHours;
        this->teachers = teachers;
    }
};

// Class for teachers
class Teacher {
public:
    int id;
    std::string name;
    int maxHours;

    Teacher(int id, std::string name, int maxHours) {
        this->id = id;
        this->name = name;
        this->maxHours = maxHours;
    }
};

// Class for auditorium
class Auditorium {
public:
    int auditoriumId;
    int maxStudents;

    Auditorium(int auditoriumId, int maxStudents) {
        this->auditoriumId = auditoriumId;
        this->maxStudents = maxStudents;
    }
};

// Class for classes (named Meeting because of the overload of the word "class")
class Meeting {
public:
    int teacherId;
    int groupId;
    bool isLecture;
    int meetingTime;
    int courseId;
    int auditoriumId;

    // Function to get time in readable way (day/class number)
    std::pair<int, int> getTime() const {
        return std::make_pair(meetingTime / 4, meetingTime % 4 + 1);
    }

    // Constructor
    Meeting(int teacherId, int groupId, int courseId, bool isLecture, int meetingTime, int auditoriumId) {
        this->teacherId = teacherId;
        this->groupId = groupId;
        this->courseId = courseId;
        this->isLecture = isLecture;
        this->meetingTime = meetingTime;
        this->auditoriumId = auditoriumId;
    }
};

// Class to store all the initial data we have
class Data {
public:
    std::vector<Teacher> teachers;
    std::vector<Group> groups;
    std::vector<Course> courses;
    std::vector<Auditorium> auditoriums;

    Data() {
        // ID, Name, Max Hours
        teachers.push_back(Teacher(0, "Teacher1", 20));
        teachers.push_back(Teacher(1, "Teacher2", 30));
        teachers.push_back(Teacher(2, "Teacher3", 20));
        teachers.push_back(Teacher(3, "Teacher4", 10));
        teachers.push_back(Teacher(4, "Teacher5", 20));

        // Id, Name, Lecture Hours, Lab Hours, Teachers
        Course course1(1, "Course1", 5, 2, {teachers[1], teachers[0], teachers[4]});
        Course course2(2, "Course2", 1, 0, {teachers[1]});
        Course course3(3, "Course3", 2, 2, {teachers[4], teachers[2]});
        Course course4(4, "Course4", 0, 1, {teachers[0], teachers[3], teachers[2]});
        Course course5(5, "Course5", 2, 1, {teachers[4], teachers[2]});
        Course course6(6, "Course6", 1, 2, {teachers[3]});
        Course course7(7, "Course7", 3, 1, {teachers[0], teachers[4]});

        // All Courses
        courses.push_back(course1);
        courses.push_back(course2);
        courses.push_back(course3);
        courses.push_back(course4);
        courses.push_back(course5);
        courses.push_back(course6);
        courses.push_back(course7);

        // Courses by Groups
        // Id, Name, Students in First Group, Students in Second Group, Courses
        std::vector<Course> group1Courses = { course2, course3, course5 };
        Group group1(1, "Group1", 12, 13, group1Courses);

        std::vector<Course> group2Courses = { course4, course6, course7, course2 };
        Group group2(2, "Group2", 11, 10, group2Courses);

        std::vector<Course> group3Courses = { course1, course6 };
        Group group3(3, "Group3", 7, 8, group3Courses);

        std::vector<Course> group4Courses = { course5, course6, course7, course1 };
        Group group4(4, "Group4", 14, 14, group4Courses);

        groups.push_back(group1);
        groups.push_back(group2);
        groups.push_back(group3);
        groups.push_back(group4);

        // Auditoriums
        // Number, Max Students
        auditoriums.push_back(Auditorium(1, 40));
        auditoriums.push_back(Auditorium(2, 20));
        auditoriums.push_back(Auditorium(3, 35));
        auditoriums.push_back(Auditorium(4, 80));
        auditoriums.push_back(Auditorium(5, 30));
        auditoriums.push_back(Auditorium(6, 50));
    }
};

// Helper functions
int findMaxStudents(const std::vector<Auditorium>& auditoriums, int auditoriumId);
int findGroupStudents(const std::vector<Group>& groups, int groupId);
std::string groupNameById(const std::vector<Group>& groups, int groupId);
std::string teacherNameById(const std::vector<Teacher>& teachers, int teacherId);
std::string courseNameById(const std::vector<Course>& courses, int courseId);

class Schedule {
public:
    std::vector<Meeting> meetings;
    double fitnessValue;
    int numClasses;
    double numConflicts;
    Data data;

    Schedule(const Data& data) {

        this->data = data;

        // Random seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::srand(seed);

        fitnessValue = 0;
        numClasses = 0;
        numConflicts = 0;

        // First random schedule initialization
        for (const auto& group : data.groups) {
            for (const auto& course : group.courses) {
                // Add lectures
                for (int i = 0; i < course.lectureHours; ++i) {
                    // Random teacher
                    int randomTeacherIndex = rand() % course.teachers.size();
                    Teacher selectedTeacher = course.teachers[randomTeacherIndex];

                    // Random auditorium
                    int randomAuditoriumIndex = rand() % data.auditoriums.size();
                    Auditorium selectedAuditorium = data.auditoriums[randomAuditoriumIndex];

                    // Random lecture with selected teacher, auditorium, course, group
                    int randomMeetingTime = rand() % TIME_SLOTS;
                    Meeting meeting(selectedTeacher.id, group.id, course.id, true, randomMeetingTime, selectedAuditorium.auditoriumId);
                    meetings.push_back(meeting);
                    numClasses++;
                }

                // Add labs
                for (int i = 0; i < course.labHours; ++i) {
                    // Random teacher
                    int randomTeacherIndex = rand() % course.teachers.size();
                    Teacher selectedTeacher = course.teachers[randomTeacherIndex];

                    // Random auditorium
                    int randomAuditoriumIndex = rand() % data.auditoriums.size();
                    Auditorium selectedAuditorium = data.auditoriums[randomAuditoriumIndex];

                    // Random laboratory with selected teacher, course, group
                    int randomMeetingTime = rand() % TIME_SLOTS;
                    Meeting meeting(selectedTeacher.id, group.id, course.id, false, randomMeetingTime, selectedAuditorium.auditoriumId);
                    meetings.push_back(meeting);
                    numClasses++;
                }
            }
        }
    }

    // Calculate overall fitness (the closer to 1, the better)
    double calculateFitness(Data& data) {
        double conflicts = static_cast<double>(calculateConflicts(data));
        fitnessValue = 1 / (1 + conflicts);
        return fitnessValue;
    }

    // Calculate total number of conflicts based on given criteria
    int calculateConflicts(Data& data) {
        numConflicts = 0;

        std::unordered_map<int, std::unordered_set<int>> teacherLectureSlots;
        std::unordered_map<int, std::unordered_set<int>> teacherLabSlots;
        std::unordered_map<int, std::unordered_set<int>> groupSlots;
        std::unordered_map<int, std::unordered_set<int>> auditoriumSlots;
        std::unordered_map<int, int> teacherTeachingHours;

        for (const auto& meeting : meetings) {
            // Same group at the same time on different meetings
            if (!groupSlots[meeting.groupId].insert(meeting.meetingTime).second) {
                numConflicts += GROUP_SPLIT_PENALTY;
            }
            // Several meetings in the same auditorium
            if (!auditoriumSlots[meeting.auditoriumId].insert(meeting.meetingTime).second) {
                numConflicts += AUDITORIUM_SPLIT_PENALTY;
            }
            // Auditorium overflow
            int groupId = meeting.groupId;
            int auditoriumId = meeting.auditoriumId;
            int groupStudents = findGroupStudents(data.groups, groupId);
            int maxStudents = findMaxStudents(data.auditoriums, auditoriumId);

            if (maxStudents < groupStudents) {
                numConflicts += AUDITORIUM_OVERFLOW_PENALTY;
            }
        }

        using SlotTuple = std::tuple<int, int, bool>;
        using TeacherSlotSet = std::unordered_set<SlotTuple>;
        using TeacherSlotsMap = std::unordered_map<int, TeacherSlotSet>;
        TeacherSlotsMap teacherSlots;

        // Same teacher at the same time on different meetings (handle lectures and labs separately)
        for (const auto& meeting : meetings) {
            teacherTeachingHours[meeting.teacherId]++;
            auto& slotSet = teacherSlots[meeting.teacherId];

            if (meeting.isLecture) {
                bool isSameSubjectLecture = false;
                for (const auto& slot : slotSet) {

                    if (std::get<0>(slot) == meeting.courseId && std::get<1>(slot) == meeting.meetingTime) {
                        if (std::get<2>(slot) == meeting.isLecture) {
                            isSameSubjectLecture = true;
                            teacherTeachingHours[meeting.teacherId]--;
                        }
                        else {
                            numConflicts += TEACHER_SPLIT_PENALTY;
                            break;
                        }
                    }
                }
                if (!isSameSubjectLecture) {

                    slotSet.insert(std::make_tuple(meeting.courseId, meeting.meetingTime, meeting.isLecture));
                }
            }
            else {
                for (const auto& slot : slotSet) {

                    if (std::get<0>(slot) == meeting.courseId && std::get<1>(slot) == meeting.meetingTime) {
                        numConflicts += TEACHER_SPLIT_PENALTY;
                        break;
                    }
                }
                slotSet.insert(std::make_tuple(meeting.courseId, meeting.meetingTime, meeting.isLecture));
            }
        }

        // Teacher overworks
        for (const auto& kv : teacherTeachingHours) {
            int teacherId = kv.first;
            int teachingHours = kv.second;

            if (teachingHours > data.teachers[teacherId].maxHours) {
                numConflicts += (teachingHours - data.teachers[teacherId].maxHours) * TEACHER_OVERWORKED_PENALTY;
            }
        }

        return static_cast<int>(numConflicts);
    }

    // Print selected schedule
    void print() const {
        std::vector<Meeting> sortedMeetings = meetings; // Create a local copy
        std::sort(sortedMeetings.begin(), sortedMeetings.end(), [](const Meeting& a, const Meeting& b) {
            return a.meetingTime < b.meetingTime;  // Sort by time
            });
        int currentTime = 0;
        for (const auto& meeting : sortedMeetings) {
            if (meeting.meetingTime % 4 == 0 && meeting.meetingTime != currentTime) {
                std::cout << "\n";
                currentTime = meeting.meetingTime;
            }
            std::cout << "Day: " << weekDays[meeting.getTime().first] << ", Class number: " << meeting.getTime().second
                << ", Teacher: " << teacherNameById(data.teachers, meeting.teacherId)
                << ", Group: " << groupNameById(data.groups, meeting.groupId)
                << ", Course: " << courseNameById(data.courses, meeting.courseId)
                << ", Class Type: " << (meeting.isLecture ? "Lec" : "Lab")
                << ", Auditorium: " << meeting.auditoriumId << std::endl;
        }
    }
};