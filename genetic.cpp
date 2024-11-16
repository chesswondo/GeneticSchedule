#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <unordered_set>
#include <functional>

#include "classes.h"

#pragma once

// Class for population
class Population {
public:
    int size;
    std::vector<Schedule> schedules;

    Population() {
        this->size = POPULATION;
    }

    // Constructor
    Population(int size, Data& data) {
        this->size = size;
        for (int i = 0; i < size; ++i) {
            Schedule schedule(data);
            schedules.push_back(schedule);
        }
    }
};

class GeneticAlgorithm {
public:
    // Implementation of crossover between two "parents" to get "child". Meetings divided 50/50.
    Schedule crossover_schedule(const Schedule& schedule1, const Schedule& schedule2) {
        Schedule newSchedule(schedule1);

        for (size_t i = 0; i < schedule1.meetings.size(); ++i) {

            if (rand() % 2 == 0) newSchedule.meetings[i] = schedule1.meetings[i];
            else newSchedule.meetings[i] = schedule2.meetings[i];
        }

        return newSchedule;
    }

    // Random mutations with probability MUTATION_RATIO
    Schedule mutate_schedule(const Schedule& schedule, const Data& data) {
        Schedule resultSchedule(data); 
        Schedule tempSchedule(data);

        for (size_t i = 0; i < schedule.meetings.size(); ++i) {
            if ((static_cast<double>(rand()) / RAND_MAX) < MUTATION_RATIO)
                resultSchedule.meetings[i] = tempSchedule.meetings[i];
            else
                resultSchedule.meetings[i] = schedule.meetings[i];
        }

        return resultSchedule;
    }

    // Apply mutations to all schedules
    void mutate_population(Population& population, const Data& data) {
        for (auto& schedule : population.schedules) {
            schedule = mutate_schedule(schedule, data);
        }
    }

    // Create new population
    Population crossover_population(const Population& population) {
        Population newPopulation;

        std::vector<Schedule> sortedSchedules = population.schedules;

        // Sort by best accordances
        std::sort(sortedSchedules.begin(), sortedSchedules.end(),
                  [](const Schedule& a, const Schedule& b) {
                      return a.accordanceValue > b.accordanceValue;
                  });

        // Select ELITISM_NUM best schedules
        for (int i = 0; i < ELITISM_NUM; ++i) {
            newPopulation.schedules.push_back(sortedSchedules[i]);
        }

        // Crossover to create the rest of the population
        while (newPopulation.schedules.size() < POPULATION) {

            // Select two schedules randomly from sortedSchedules for crossover
            int index1 = rand() % sortedSchedules.size();
            int index2 = rand() % sortedSchedules.size();

            Schedule childSchedule = crossover_schedule(sortedSchedules[index1], sortedSchedules[index2]);
            newPopulation.schedules.push_back(childSchedule);
        }

        return newPopulation;
    }

};

int main() {

    Data data; 
    Population population(POPULATION, data);
    GeneticAlgorithm geneticAlgo;

    // Main loop
    for (int generation = 0; generation < NUM_GENERATION; ++generation) {
        for (auto& schedule : population.schedules) {
            schedule.calculateAccordance(data);
        }

        // Best Schedule from the population by accordance value
        Schedule bestSchedule = *std::max_element(population.schedules.begin(),
                                                    population.schedules.end(),
                                                      [](const Schedule& a, const Schedule& b) {
                                                          return a.accordanceValue < b.accordanceValue;
                                                      });

        // Worst Schedule from the population by accordance value
        Schedule worstSchedule = *std::max_element(population.schedules.begin(),
                                                    population.schedules.end(),
                                                      [](const Schedule& a, const Schedule& b) {
                                                          return a.accordanceValue > b.accordanceValue;
                                                      });

        // Print final results
        if (bestSchedule.accordanceValue == 1 || generation==NUM_GENERATION-1){
            std::cout << "Generation: " << generation << std::endl;
            std::cout << "Best Accordance: " << bestSchedule.accordanceValue << std::endl;
            std::cout << "Worst Accordance: " << worstSchedule.accordanceValue << std::endl;
            std::cout << "Number of Classes: " << bestSchedule.numClasses << std::endl;
            std::cout << "Number of Conflicts: " << bestSchedule.numConflicts << std::endl;           

            // Print some meetings from the best schedule
            std::cout << "The Best Schedule:\n\n";
            bestSchedule.print(); 

            return 0;
        }
        
        // Report every REPORT_EVERY generations
        if (generation % REPORT_EVERY == 0) {
            std::cout << "Generation: " << generation << std::endl;

            std::cout << "Best Accordance: " << bestSchedule.accordanceValue << std::endl;
            std::cout << "Worst Accordance: " << worstSchedule.accordanceValue << std::endl;
            std::cout << "Number of Conflicts: " << bestSchedule.numConflicts << std::endl;

            std::cout << "--------------------------------------" << std::endl;
        }

        // Perform crossover on the population
        Population newPopulation = geneticAlgo.crossover_population(population);

        // Mutate the new population
        geneticAlgo.mutate_population(newPopulation, data);

        // Replace the old population with the new one
        population = newPopulation;
        
    }

    return 0;
}
