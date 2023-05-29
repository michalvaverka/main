/**
    @filename:  network.h
    @author:    Michal Vaverka

    @description:
                Header file with functions designed to solve the given task; subapplication called network.

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
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>

//Enum-ed types of extracted data
enum 
{
    ADDRESS, NETMASK, GATEWAY, DNS_SERVER, DATA_COUNT
};

//Function for extracting contents of input_file and storing those which are needed to the data array, which it returns
char **extract_data(FILE *input_file);

//Function for printing out the data into output_file
void output_result(FILE *output_file, char **data);

//Function for executing the network operation
void network(FILE *input_file, FILE *output_file);

#endif
