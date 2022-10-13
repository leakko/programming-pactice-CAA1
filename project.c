#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "project.h"

// Parse a tDate from string information
void date_parse(tDate* date, const char* text)
{
    // Check output data
    assert(date != NULL);
    
    // Check input date
    assert(text != NULL);
    assert(strlen(text) == 10);
    
    // Parse the input date
    sscanf(text, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Compare two tDate structures and return true if they contain the same value or false otherwise.
bool date_equals(tDate date1, tDate date2)
{
    return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year); 
}

// EX2: Implement your methods here....

// Initialize the projects data
void projectData_init(tProjectData* data)
{
    data->numProjects = 0;
}

// Get the number of projects
int projectData_len(tProjectData data)
{
    return data.numProjects;
}

// Get a project
void projectData_get(tProjectData data, int index, char* buffer)
{
    tProject selectedProject = data.projects[index];

    sprintf(buffer, "%d/%d/%d;%s;%s;%s;%s;%.2f;%d", 
    selectedProject.date.day, selectedProject.date.month, selectedProject.date.year, selectedProject.ong, 
    selectedProject.ongName, selectedProject.city, selectedProject.code, selectedProject.cost, selectedProject.numPeople);

    // printf("project ong info:\n%s\n",selectedProject.ong);
    // printf("projectData_get result:\n%s\n",buffer);

}

// Parse input from CSVEntry
void project_parse(tProject* proj, tCSVEntry entry)
{
    // printf("entry: %s\n", entry.fields[0]);
    // We parte entry data in order:

    // Date
    char stringDate[DATE_STRING_LENGTH];
    csv_getAsString(entry, 0, stringDate, DATE_STRING_LENGTH);
    tDate date;
    date_parse(&date, stringDate);

    proj->date.day = date.day;
    proj->date.month = date.month;
    proj->date.year = date.year;

    // Ong
    char ong[MAX_ONG_CODE + 1];
    csv_getAsString(entry, 1, ong, MAX_ONG_CODE + 1);
    // printf("Copying ong: %s\n", ong);
    strcpy(proj->ong, ong);

    // OngName
    char ongName[MAX_NAME + 1];
    csv_getAsString(entry, 2, ongName, MAX_NAME + 1);
    strcpy(proj->ongName, ongName);

    // City
    char city[MAX_NAME + 1];
    csv_getAsString(entry, 3, city, MAX_NAME + 1);
    strcpy(proj->city, city);

    // Code
    char code[MAX_PROJECT_CODE + 1];
    csv_getAsString(entry, 4, code, MAX_PROJECT_CODE + 1);
    strcpy(proj->code, code);

    // Cost
    float cost = csv_getAsReal(entry, 5);
    proj->cost = cost;

    // Number of people
    int numPeople = csv_getAsInteger(entry, 6);
    proj->numPeople = numPeople;
}


// Add project to project data
void projectData_add(tProjectData* data, tProject proj)
{
    int i;
    bool found;

    i = 0;
    found = false;
    while(i < data->numProjects && !found) {
        if(
            strcmp(data->projects[i].code, proj.code) == 0 && 
            strcmp(data->projects[i].city, proj.city) == 0 && 
            date_equals(data->projects[i].date, proj.date)
        ) {
            data->projects[i].cost = data->projects[i].cost + proj.cost;
            data->projects[i].numPeople = data->projects[i].numPeople + proj.numPeople;
            found = true;
        }
        i++;
    }

    if(!found) {
        data->projects[data->numProjects] = proj;
        data->numProjects++;
    }
}

void projectData_del(tProjectData* data, char* code, char* city, tDate date, float cost, int numPeople)
{
    int i;
    bool found;

    i = 0;
    found = false;
    while(i < data->numProjects && !found) {
        if(
            strcmp(data->projects[i].code, code) == 0 && 
            strcmp(data->projects[i].city, city) == 0 && 
            date_equals(data->projects[i].date, date)
        ) {
            if(data->projects[i].cost - cost <= 0 || data->projects[i].numPeople - numPeople <= 0) {
                data->numProjects--;
            } else {
                data->projects[i].cost = data->projects[i].cost - cost;
                data->projects[i].numPeople = data->projects[i].numPeople - numPeople;
            }
        }
        i++;
    }
}