#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpef.h"
#include "ourDate.h"

const bool RUNCATCH = false;

int main( int argc, char **argv)
{
    Catch::Session session;
    int result;
    
    //TEST CASE RUNCATCH

    if( RUNCATCH )
    {
        result = session.run( argc, argv );
        if( result != 0 )
        {
            cout << "Test cases didn't pass." << endl;
            return 0;
        }
    }

    //ARGUMENT CHECK

    if( argc != 5 )
    {
        cout << "Usage: thpef.exe datafile template1 template2 template3" << endl;
        cout << "       datafile --name of input data file" << endl;
        cout << "       template1 --name of purchase template file" << endl;
        cout << "       template2 --name of payment template file" << endl;
        cout << "       template3 --name of overdue template file" << endl;
        exit(0);
    }

    //FILE_OPEN CHECK

    ifstream fin;
    CustomerRecord Record;
    double amount;
    bool status = true;
    string letter;
    string filename;

    fin.open( argv[1] );

    if( !fin.is_open() )
    {
        cout << "Unable to open the input file: " << argv[1] << endl;
        exit(0);
    }
    else
    {
        while( status == true )
        {
            status = getClient( fin, Record );
            amount = Record.transaction_amount;

            if( status == true && amount > 0 ) //Purchase
            {
                filename = argv[2];
                writeLetter( Record, filename, currDate );
            }

            else if( status == true && amount < 0 ) //Payment
            {
                filename = argv[3];
                writeLetter( Record, filename, currDate );
            }
            else if( status == true && amount == 0 ) //Overdue
            {
                filename = argv[4];
                writeLetter( Record, filename, currDate );
            }
            else //Do Nothing 
            {}
        }
    }

return 0;

}

//TEST CASE FOR GETCLIENT

TEST_CASE( "getClient - retrieve data from line 1 of datafile1.txt" )
{
    ifstream f;
    CustomerRecord X;
    f.open( "datafile1.txt" );

    bool status1 = getClient( f, X );
    SECTION( "#1" )
    {
        REQUIRE( status1 == true );
        REQUIRE( X.firstname == "James" );
        REQUIRE( X.lastname == "Smith" );
        REQUIRE( X.address == "123 Main St" );
        REQUIRE( X.city == "Rapid City" );
        REQUIRE( X.state == "SD" );
        REQUIRE( X.zipcode == "57701" );
        REQUIRE( X.transaction_amount == 89.55 );
        REQUIRE( X.current_balance == 12.5 );
    }

    bool status2 = getClient( f, X );
    SECTION( "#2" )
    {
        REQUIRE( status2 == true );
        REQUIRE( X.firstname == "Sally" );
        REQUIRE( X.lastname == "Struthers" );
        REQUIRE( X.address == "2345 Elk Dr" );
        REQUIRE( X.city == "Rapid City" );
        REQUIRE( X.state == "SD" );
        REQUIRE( X.zipcode == "57701" );
        REQUIRE( X.transaction_amount == -1004.50 );
        REQUIRE( X.current_balance == 2598.98 );
    }

    bool status3 = getClient( f, X );
    SECTION( "#3" )
    {
        REQUIRE( status3 == true );
        REQUIRE( X.firstname == "Kelly" );
        REQUIRE( X.lastname == "Bundy" );
        REQUIRE( X.address == "9801 5th St" );
        REQUIRE( X.city == "Rapid City" );
        REQUIRE( X.state == "SD" );
        REQUIRE( X.zipcode == "57702" );
        REQUIRE( X.transaction_amount == -901.55 );
        REQUIRE( X.current_balance == 901.55 );
    }

    f.close();
}

//TEST CASE FOR WRITELETTER

TEST_CASE( "writeLetter - to write a purchase statement from line 1 of datafile1.txt" )
{
    ifstream f, t;
    CustomerRecord X;
    f.open( "datafile1.txt" );

    bool status1 = getClient( f, X );
    SECTION( "#1" )
    {
        REQUIRE( status1 == true );
        writeLetter( X, "purchaseTemplate.txt", currDate );

        t.open( "James.Smith.txt" );
    
        string line1;
        std::getline( t, line1, '\n' );
        REQUIRE( line1 == "James Smith" );

        string line2;
        std::getline( t, line2, '\n' );
        REQUIRE( line2 == "123 Main St" );

        string line3;
        std::getline( t, line3, '\n' );
        REQUIRE( line3== "Rapid City, SD 57701" );

        t.close();
    }

    bool status2 = getClient( f, X );
    SECTION( "#2" )
    {
        REQUIRE( status2 == true );
        writeLetter( X, "paymentTemplate.txt", currDate );

        t.open( "Sally.Struthers.txt" );
    
        string line1;
        std::getline( t, line1, '\n' );
        REQUIRE( line1 == "Sally Struthers" );

        string line2;
        std::getline( t, line2, '\n' );
        REQUIRE( line2 == "2345 Elk Dr" );

        string line3;
        std::getline( t, line3, '\n' );
        REQUIRE( line3== "Rapid City, SD 57701" );

        t.close();
    }

    bool status3 = getClient( f, X );
    SECTION( "#3" )
    {
        REQUIRE( status3 == true );
        writeLetter( X, "paymentTemplate.txt", currDate );

        t.open( "Kelly.Bundy.txt" );
    
        string line1;
        std::getline( t, line1, '\n' );
        REQUIRE( line1 == "Kelly Bundy" );

        string line2;
        std::getline( t, line2, '\n' );
        REQUIRE( line2 == "9801 5th St" );

        string line3;
        std::getline( t, line3, '\n' );
        REQUIRE( line3== "Rapid City, SD 57702" );

        t.close();
    }

    f.close();
}