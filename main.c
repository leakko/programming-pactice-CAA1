#include <stdio.h>
#include "csv.h"
#include "project.h"
#include <string.h>


void projectData_print_src(tProjectData data) {
    char buffer[1024];
    int i;
    if (projectData_len(data) > 0) {
        for(i = 0 ; i < projectData_len(data) ; i++) {
            projectData_get(data, i, buffer);
            printf("%d;%s\n", i, buffer);
        }
    }    
}

int main(int argc, char **argv)
{    
    tCSVData test_data;      
    tProjectData projectData;
    tProject project;
    tDate date;   
    int i;
 
    // Define test data
    const char* test_data_str = \
          "11/10/2022;ACN;ACNUR;Barcelona;ACN0001;12500.00;5\n" \
          "11/11/2022;MSF;Medecins Sans Frontieres;Mumbai;MSF1057;8300.50;8\n" \
          "11/12/2022;STM;SETEM;Malaga;STM0012;600.20;10\n";
    const char* test_data2_str = \
          "11/10/2022;ACN;ACNUR;Madrid;ACN0001;22500.00;7\n" \
          "11/12/2022;CRE;Cruz Roja España;Oviedo;CRE0333;3500.20;3\n" \
          "11/11/2022;MSF;Medecins Sans Frontieres;Mumbai;MSF1057;1699.50;2\n" ;
                                
    // Read the data in CSV format
    csv_init(&test_data);
    csv_parse(&test_data, test_data_str, "PROJECT");
    
    // Initialize the project data
    projectData_init(&projectData);
    // printf("Expected: %d - result: %d\n", 0, projectData.numProjects);
    
    // Add data
    for(i = 0; i < csv_numEntries(test_data); i++) {
        // Get the project from the entry
        project_parse(&project, csv_getEntry(test_data, i)[0]);
    
        
        // Add new project to the list of projects
        projectData_add(&projectData, project);
    }
    
    // List current projects
    printf("\n");
    projectData_print_src(projectData);
    printf("\n");
    
    // Remove old data
    csv_free(&test_data);
    
    // Load new data
    csv_init(&test_data);
    csv_parse(&test_data, test_data2_str, "PROJECT");
    
    // Add new data
    for(i = 0; i < csv_numEntries(test_data); i++) {
        // Get the project from the entry
        project_parse(&project, csv_getEntry(test_data, i)[0]);
        
        // Add new project to the list of projects
        projectData_add(&projectData, project);
    }
    
    // List current projects
    projectData_print_src(projectData);
    printf("\n");
    
    // Remove money and numPeople
    date_parse(&date, "11/10/2022");
    projectData_del(&projectData, "ACN0001", "Madrid", date, 2500.0, 1);
    
    date_parse(&date, "11/11/2022");
    projectData_del(&projectData, "MSF1057", "Mumbai", date, 5000.0, 5);

    // List current projects
    projectData_print_src(projectData);
    printf("\n");
    
    // Remove remaining money and numPeople   
    projectData_del(&projectData, "MSF1057", "Mumbai", date, 1000.0, 5);

    date_parse(&date, "11/10/2022");
    projectData_del(&projectData, "ACN0001", "Madrid", date, 25000.0, 1);
    
    // List current projects
    projectData_print_src(projectData);
    printf("\n");
    
    // Remove not existing registry (the same, as now it should not exist)
    projectData_del(&projectData, "MSF1057", "Mumbai", date, 5000.0, 5);

    // List current projects
    projectData_print_src(projectData);
    printf("\n");
    
    // Remove CSV data
    csv_free(&test_data);   
    
    printf("\nPress key to end...\n");
    getchar();
	return 0;
}
