#ifndef __PROJECT_H__
#define __PROJECT_H__
#include "csv.h"

typedef struct _tDate {    
    int day; 
    int month;
    int year;
} tDate;


// Parse a tDate from string information
void date_parse(tDate* date, const char* text);

// Compare two tDate structures and return true if they contain the same value or false otherwise.
bool date_equals(tDate date1, tDate date2);

// Ex 1: Define data types here...

///////////////////////////
// Maximum length of project code
#define MAX_PROJECT_CODE 7
// Maximum length of a ong code
#define MAX_ONG_CODE 3
// Maximum length of a ong name or a city
#define MAX_NAME 40
// Maximum number of projects
#define MAX_PROJECTS 150
// Number of characters of a date string including null value
#define DATE_STRING_LENGTH 10 + 1

// I will use static memory tuples for simplicity
typedef struct _tProject {
    tDate date;
    char ong[MAX_ONG_CODE + 1];
    char ongName[MAX_NAME + 1];
    char city[MAX_NAME + 1];
    char code[MAX_PROJECT_CODE + 1];
    float cost;
    int numPeople;
} tProject;

typedef struct _tProjectData {
    tProject projects[MAX_PROJECTS];
    int numProjects;
} tProjectData;


//////////////////////////////////

// Ex 2: Define your methods here ....

// Initialize the projects data
void projectData_init(tProjectData* data);

// Get the number of projects
int projectData_len(tProjectData data);

// Get a project
void projectData_get(tProjectData data, int index, char* buffer);

// Parse input from CSVEntry
void project_parse(tProject* proj, tCSVEntry entry);

// Add project to project data
void projectData_add(tProjectData* data, tProject proj);

// Delete project
void projectData_del(tProjectData* data, char* code, char* city, tDate date, float cost, int numPeople);

#endif
