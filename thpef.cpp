/** **************************************************************************
 * @file 
 ****************************************************************************/
#include "thpef.h"

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * Reads information from the file provided and stores the data appropriately in
 * the structure for processing and returns true or false if information is read 
 * or not.
 * 
 * @param[in,out] fin - isftream that holds file information.
 * @param[in,out] Record - stores the file information in the CustomerRecord
 * structure
 * 
 * @returns true if information is read and false if end of file is reached and 
 * no information is read
 * 
 * @par Example
 * @verbatim
   ifstream f;
   CustomerRecord X;
   f.open( "datafile1.txt" );

   bool status1 = getClient( f, X );

   REQUIRE( status1 == true ); //Since file output will be read
   REQUIRE( X.firstname == "James" ); //First parameter inputted
   REQUIRE( X.lastname == "Smith" ); //Second parameter inputted
   REQUIRE( X.address == "123 Main St" ); //Third parameter inputted
   REQUIRE( X.city == "Rapid City" ); //Fourth parameter inputted
   REQUIRE( X.state == "SD" ); //Fifth parameter inputted
   REQUIRE( X.zipcode == "57701" ); //Sixth parameter inputted
   REQUIRE( X.transaction_amount == 89.55 ); //Seventh parameter inputted
   REQUIRE( X.current_balance == 12.5 ); //Eight parameter inputted

   f.close();
   @endverbatim
 *****************************************************************************/
bool getClient ( ifstream &fin, CustomerRecord &Record )
{
    if( fin.eof() )
    {
        return false;
    }

    else
    {
        std::getline( fin, Record.firstname, ',' );
        std::getline( fin, Record.lastname, ',' );
        std::getline( fin, Record.address, ',' );
        std::getline( fin, Record.city, ',' );
        std::getline( fin, Record.state, ',' );
        std::getline( fin, Record.zipcode, ',' );

        fin >> Record.transaction_amount;
        fin.ignore( 256, ',' );

        fin >> Record.current_balance;
        fin.ignore( 256, '\n' );

        return true;
    }
    
}

/** ***************************************************************************
 * @author Steve Nathan de Sa
 * 
 * @par Description 
 * According to information from the structure, the function automatically creates
 * an output file using file templates that accurately represents the data.
 * 
 * @param[in] Record - constains the file information in CustomerRecord structure
 * @param[in] filename - contains the name of the file to be outputted
 * @param[in] currDate - contains the date to be put into the file
 *
 * @par Example
 * @verbatim
   ifstream f, t;
   CustomerRecord X;
   f.open( "datafile1.txt" );

   bool status1 = getClient( f, X );

   REQUIRE( status1 == true );
   writeLetter( X, "purchaseTemplate.txt", currDate );

   t.open( "James.Smith.txt" );
   
   string line1;
   std::getline( t, line1, '\n' );
   REQUIRE( line1 == "James Smith" ); //First line of outputted file 

   string line2;
   std::getline( t, line2, '\n' );
   REQUIRE( line2 == "123 Main St" ); //Second line of outputted file

   string line3;
   std::getline( t, line3, '\n' );
   REQUIRE( line3== "Rapid City, SD 57701" ); //Third line of outputted file

   f.close();
   t.close();
   @endverbatim
 *****************************************************************************/
void writeLetter ( CustomerRecord Record, string filename, string currDate )
{
    //OPENING INPUT AND OUTPUT FILES

    ifstream input;
    ofstream output;

    string file = Record.firstname + "." + Record.lastname + ".txt" ;

    input.open( filename );
    output.open( file );

    if( !input.is_open() )
    {
        cout << "Unable to open the template file: " << filename << endl;
        exit(0);
    }
    else
    {
        if( !output.is_open() )
        {
            cout << "Unable to open the output file: " << file << endl;
            exit(0);
        }
        else
        {
            //CONVERTING TRANSACTION AND BALANCE TO STRINGS

            string transaction;
            string balance;
            ostringstream x, y;
            x << fixed << setprecision(2) << abs(Record.transaction_amount);
            y << fixed << setprecision(2) << Record.current_balance + Record.transaction_amount;
            transaction = x.str();
            balance = y.str();

            //READING THE LETTER TEMPLATE AND OUTPUTTING EDITED DATA TO OUTPUT FILE

            string line;
            string fullname = Record.firstname + " " + Record.lastname ;

            size_t full, address, city, state, zip, first, last, date, trans, bal;

            while( std::getline( input, line, '\n' ) )
            {
                full = line.find( "#FULLNAME" );
                if( full != string::npos )
                {
                    line.replace( full, 9, fullname );
                }

                address = line.find( "#ADDRESS" );
                if( address != string::npos )
                {
                    line.replace( address, 8, Record.address );
                }

                city = line.find( "#CITY" );
                if( city != string::npos )
                {
                    line.replace( city, 5, Record.city );
                }

                state = line.find( "#STATE" );
                if( state != string::npos )
                {
                    line.replace( state, 6, Record.state );
                }

                zip = line.find( "#ZIP" );
                if( zip != string::npos )
                {
                    line.replace( zip, 5, Record.zipcode );
                }

                first = line.find( "#FIRST" );
                if( first != string::npos )
                {
                    line.replace( first, 6, Record.firstname );
                }

                last = line.find( "#LAST" );
                if( last != string::npos )
                {
                    line.replace( last, 5, Record.lastname );
                }

                date = line.find( "#DATE" );
                if( date != string::npos )
                {
                    line.replace( date, 5, currDate );
                }
                
                trans = line.find( "#TRANSACTION" );
                if( trans != string::npos )
                {
                    line.replace( trans, 12, transaction );
                }

                bal = line.find( "#BALANCE" );
                if( bal != string::npos )
                {
                    line.replace( bal, 8, balance );
                }

                output << line << endl;
            }
            
            //CLOSING FILES

            input.close();
            output.close();
        }
    }
}