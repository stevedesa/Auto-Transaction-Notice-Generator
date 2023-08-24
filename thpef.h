/** **************************************************************************
 * @file 
 ****************************************************************************/
/** **************************************************************************
 * @mainpage Take Home Programing Exam Final Exam - Transaction Processing
 * 
 * @section course_section Course Information 
 *
 * @author Steve Nathan de Sa
 * 
 * @par Professor: 
 *         Roger Schrader
 * 
 * @par Course: 
 *         CSC115 - M01 - Test-Driven Software Development
 * 
 * @par Location: 
 *         EP 202
 * 
 * @date Due December 9, 2022
 *
 * @section program_section Program Information 
 * 
 * @details 
 * Program that will read accounting transaction records, update the customer's 
 * balance, and write customized form letters to output files.
 * 
 * The program will receive data from the user, accordingly sort the data and 
 * based on the information stored a designation file will be outputted
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      none - a straight compile and link with no external libraries.
 *      [1. cl.exe /EHsc /W4 /WX thpe3.cpp thpe3Tests.cpp] Compiles + Links
 * 
 * @par Usage: 
   @verbatim  
   c:\> thpef.exe datafile template1 template2 template3
        datafile --name of input data file
        template1 --name of purchase template file
        template2 --name of payment template file
        template3 --name of overdue template file
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug At program start, if files arent given properly the program crashes.
 * 
 * @todo Clean up the file output. Need to format it in the file.
 * 
 * @par Modifications and Development Timeline: 
 * This is a link to my gitlab repository's commits. To view <a target="_blank" 
 * href="https://gitlab.cse.sdsmt.edu/101124071/csc115f22programs/-/commits/main/thpef">click here.</a>
 * 
 *****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

//CUSTOMER RECORD STRUCTURE

/** **********************************************************************
* @author Steve Nathan de Sa
*
* @par Description
* Structure that stores Customer Record data
************************************************************************/
struct CustomerRecord
{
    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains first name of Customer
    ************************************************************************/

    string firstname;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains last name of Customer
    ************************************************************************/
    string lastname;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains address of Customer
    ************************************************************************/
    string address;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains city of Customer
    ************************************************************************/
    string city;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains the state of Customer
    ************************************************************************/
    string state;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains zip code of Customer
    ************************************************************************/
    string zipcode;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains transaction amount of Customer
    ************************************************************************/
    double transaction_amount;

    /** **********************************************************************
    * @author Steve Nathan de Sa
    *
    * @par Description
    * String that contains current balance of Customer
    ************************************************************************/
    double current_balance;
};

//FUNCTIONS

bool getClient( ifstream &fin, CustomerRecord &Record );

void writeLetter ( CustomerRecord Record, string filename, string currDate );