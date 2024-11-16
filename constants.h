#pragma once

const int TEACHER_OVERWORKED_PENALTY = 1;
const int TEACHER_SPLIT_PENALTY = 1;
const int GROUP_SPLIT_PENALTY = 1;
const int AUDITORIUM_SPLIT_PENALTY = 1;
const int AUDITORIUM_OVERFLOW_PENALTY = 1;
const int NUM_GENERATION = 1000;
const int POPULATION = 200;
const int TIME_SLOTS = 4 * 5;
const double MUTATION_RATIO = 0.001;
const int ELITISM_NUM = 5;
const int REPORT_EVERY = 20;

const std::string weekDays[5] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };