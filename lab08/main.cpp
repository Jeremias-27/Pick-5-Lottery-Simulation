// Name: Jeremias Conerly
// Lab: 08
// Due Date: 11/16/23
// Filename: main.cpp
// Description: pick 5 lottery game, if user guesses the 5 numbers correctly they win

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <list>
#include "time.h"

using namespace std;

// function declarations
void errorHandling(list<int>&, runtime_error, int&);
void generate(list<int>&); 
void inptNumbrs(list<int>&, int&);
void compare(const list<int>&, list<int>&, int&);
void decide(const list<int>&, const list<int>&, int);

// representation of how the game works
int main()
{
    //lists
    list<int> l1;
    list<int> l2;

    // variable declarations
    int random;
    int counter = 0;

    generate(l1); // generates 5 distinct random numbers in a list from 1 to 9

    try
    {
        inptNumbrs(l2, random); // prompts user for 5 distinct numbers from 1 to 9
    }
    catch(runtime_error inpt) // catching and handling possible exception
    {
        errorHandling(l2, inpt, random);       
    }
    
    compare(l1, l2, counter); // compares the contents of 2 lists 
                             // checking how many numbers they have in common

    decide(l1, l2, counter); // outputs if user won or loss
   
    return 0;
}

// function to handle possible user input error
void errorHandling(list<int>& l2, runtime_error inpt, int& random)
{
        // clearing input stream
        cin.clear();
        cin.ignore(100, '\n');
        cout << inpt.what() << endl; // outputting what went wrong

        // reprompting till user complies
        while(l2.size() != 5)
        {
            cin >> random;
            
            if(!cin)
            {
                cin.clear();
                cin.ignore(100, '\n');
            }
            
            l2.push_front(random); // inserting number
            l2.sort(); // sorting for unique function

        // remove if inputted number is not from 1 to 9
            if(random < 1 || random > 9)
            {
                l2.remove(random);
                cout << inpt.what() << endl; // outputting what went wrong
            }
        
            l2.unique(); // remove consecutive duplicate numbers
    }
}

// fills a list with 5 distinct random numbers from 1 to 9
void generate(list<int>& l1)
{
    srand(time(0)); // different random numbers each time

    // creating list of 5 distinct random numbers from 1 to 9
    while(l1.size() != 5)
    {
        int num = 1 + rand() % 9; // getting generated numbers
        l1.push_front(num); // inserting number in the list
        l1.sort(); // sorting for unique function
        l1.unique(); // removes duplicate consecutive numbers
    }
}

// prompts user for 5 distinct numbers from 1 to 9
void inptNumbrs(list<int>& l2, int& random)
{
    random = 0;
    try
    {
         cout << "Lets play a game! insert 5 numbers from 1 to 9 "
         << "and if they match the winning ticket you win!" << endl;

    // prompting user for 5 distinct numbers from 1 to 9
        while(l2.size() != 5)
        {
            cin >> random;
            
            // if users input is invalid throw exception
            if(!cin || random < 1 || random > 9)
            {
                throw runtime_error("invalid input");
            }
            
            l2.push_front(random); // inserting number
            l2.sort(); // sorting for unique function
            l2.unique(); // remove consecutive duplicate numbers
        }
    }
    catch(runtime_error inpt) // catching and rethrowing exception
    {
        throw inpt;
    }
}

// compares the contents of 2 lists, checking how many numbers they have in common
void compare(const list<int>& l1,  list<int>& l2, int& counter)
{
    counter = 0;
    
    // iterators to traverse through list
    list<int>::const_iterator v1 = l1.begin();
    list<int>::const_iterator v2 = l2.begin();

    // comparing the two lists
    while (v1 != l1.end())
     {
        if(*v1 == *v2) // found match
        {
            l2.remove(*v2); // removing matching number
            v2 = l2.begin(); // back to beginning of list
            ++v1; // next item in list
        }
        else // match not found
        {
            if(v2 == l2.end()) // reached end of list without finding a match
            {
                v2 = l2.begin(); // back to beginning of list
                ++v1; // next item
            }
            else // not at end of list
            {
                ++v2; // next item
            }
        }
     }  

     counter = (5 - l2.size()); // 5(original size) - new size = number of matching numbers
} 

// outputs if user won or loss; outputs real list vs unmatching digits in user list
void decide(const list<int>& l1, const list<int>& l2, int counter)
{
    if(counter == 5) // counter == 5, two lists are identical
    {
        cout << endl << "Congratulations, you won the game!" << endl << "winning ticket: ";
        
        for(auto k : l1)
        {
            cout << k << " ";
        }
    }
    else // lists are not the same
    {
        // how many numbers the lists had in common
        cout << "So close, you guessed " << counter << " out of 5 numbers right!" << endl;

        cout << "winning ticket: "; // contents of random generated number list

        for(auto i : l1)
        {
            cout << i << " ";
        }

        cout << endl << "unmatching numbers: "; // numbers that did not match in user list
        
        for(auto j : l2)
        {
            cout << j << " ";
        }
    }
}
