/**
    @filename:  network.c
    @author:    Michal Vaverka

    @description:
                Implementations of functions defined in network.h.

    @projectdescription: 
                The task was to write a code, which would extract certain data from a file and write them in a specific
                format to another file.

                This task was given to me as a recruiting task when I was applying for a job in METEL s.r.o.

    @predisclaimer:
                Disclaimer and rules on usage are listed in order to avoid plagiarization in academic institutions.
    
    @disclaimer:
        !!! READ !!!
                Any part of this code can be used IF AND ONLY IF all of the following conditions hold:
                    1) The whole header of this file (from the @filename to the end of the @disclaimer section) must be pasted
                            directly above where the borrowed snippet/whole code is used,
                    2) The project bottowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "network.h"
#include "utils.h"

char **extract_data(FILE *input_file) 
{
    char *line_ptr = NULL;
    size_t number_read = 0;

    char **data = (char **) calloc(DATA_COUNT, sizeof(char *));
    if (data == NULL) 
    {
        fprintf(stderr, "ERROR: Memory allocation fault!\n");
        exit(MEM_ALLOC_ERROR);
    }

    while(getline(&line_ptr, &number_read, input_file) != EOF)
    {
        int i = 0;
        while(isblank(line_ptr[i])) i++; //Removing blanks in the beginning of lines

        if(line_ptr[i] == '#') continue; //Skipping comment lines

        while(line_ptr[i] != '=') i++; //Looking for the '=' symbol, after which the needed data is provided
        i++;                                               

        int data_type;

        //Checking which kind of data is presented within current line
        if (strstr((const char *)line_ptr, "net_ip")) data_type = ADDRESS;
        else if (strstr((const char *)line_ptr, "net_mask")) data_type = NETMASK;
        else if (strstr((const char *)line_ptr, "net_gw")) data_type = GATEWAY;
        else if (strstr((const char *)line_ptr, "net_dns")) data_type = DNS_SERVER;
        else data_type = NO_DATA;

        //Writing data values into data array
        if (data_type != NO_DATA) 
        {
            data[data_type] = (char *) malloc (strlen(line_ptr) - i + 1);                
            strcpy(data[data_type], &line_ptr[i]);
        }

    }

    free(line_ptr);

    return data;
}

void output_result(FILE *output_file, char **data) 
{
    fprintf(output_file, "auto eth0\niface eth0 inet static\n");    //Printing the static part of output into the output file

    //Printing the dynamic part of the output
        //Note that the NULL check is here just in case some of the data isnt provided in the input
    if (data[ADDRESS] != NULL) fprintf(output_file, "\taddress %s", data[ADDRESS]), free(data[ADDRESS]);    
    if (data[NETMASK] != NULL) fprintf(output_file, "\tnetmask %s", data[NETMASK]), free(data[NETMASK]);
    if (data[GATEWAY] != NULL) fprintf(output_file, "\tgateway %s", data[GATEWAY]), free(data[GATEWAY]);
    if (data[DNS_SERVER] != NULL) fprintf(output_file, "\tdns-server %s", data[DNS_SERVER]), free(data[DNS_SERVER]);
}

void network(FILE *input_file, FILE *output_file) 
{
    char **data = extract_data(input_file);
    output_result(output_file, data);

    free(data);
}
