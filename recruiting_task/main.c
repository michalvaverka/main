/**
    @filename:  main.c
    @author:    Michal Vaverka

    @description:
                Main file containing argument checks and calls other methods accordingly

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "network.h"
#include "utils.h"

int main(int argc, char *argv[]) 
{
    //Arguments check
    if (argc != 7             ||
        strcmp(argv[1], "-c") ||
        strcmp(argv[3], "-i") ||
        strcmp(argv[5], "-o")) 
    {
        fprintf(stdout, "Wrong parameters! \n\nProgram must be run with parameters as follows:\n \"./metel-cfg2etc -c <name_of_sections> -i <input_filename> -o <output_filename>\", where\n\n<name_of_sections> is the type of operation the program should execute,\n<input_filename> is path tothe  input file, and\n<output_filename> is path to the output file.\n");
        exit(PARAM_ERROR);
    }

    FILE *input_file = fopen(argv[4], "r"); 
    FILE *output_file = fopen(argv[6], "w");

    if (input_file == NULL || output_file == NULL) 
    {
        fprintf(stderr, "ERROR: File could not be opened!\n");
        exit(FILE_ERROR);
    }

    //Operation execution
    if (!strcmp(argv[2], "network")) 
    {
        network(input_file, output_file);
    } else if (!strcmp(argv[2], "some other operation")) 
    {
        //Space for other operation implementation
    }  else 
    {
        fprintf(stdout, "Non-existent operation!\n\nSo far, only operation \"network\" is implemented.\n");
    }

    fclose(input_file), fclose(output_file);

    return 0;
}
