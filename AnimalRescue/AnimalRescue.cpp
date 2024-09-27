//
//  main.cpp
//  Animal Rescue v1
//
//  Created by Caden Finley on 10/11/23.
//

#include <iostream>
#include <fstream>
#include <string>
#include "p2queue2.h"
#include "p2sll.h"
using namespace std;

int main() {
    ifstream inputFile("actions.txt"); //open required files
    ofstream outputFile("adoptions.txt");

    Queue<string> catShelter; //create queues and list for storing animal information
    Queue<string> dogShelter;
    List<string> either;

    string action, type, name;//instanciate general variables
    
    while (inputFile >> action) { //loop through the action file and write to adoption file
        
        if (action == "rescue") { //if action is rescue push animal name and type into respective data
            inputFile >> type >> name;
            if (type == "cat") { //push cat name and type into repective fields
                catShelter.push(name);
                either.append(type);
            }
            else if (type == "dog") { //push dog name and type into repective fields
                dogShelter.push(name);
                either.append(type);
            }
        }
        
        else if (action == "request") { //if action is request input requested animals name into adoptions file in correct order
            inputFile >> type;
            if (type == "cat" && !catShelter.isEmpty()) { //output cat if requested
                int i = 1;
                while(!(either.getKth(i)=="cat")) { //loop through either list to find animal type
                    i++;
                }
                either.removeKth(i);
                outputFile << catShelter.pop() << endl; //ouput animal name to output file
            }
            
            else if (type == "dog" && !dogShelter.isEmpty()) { //output dog if requested
                int i = 1;
                while(!(either.getKth(i)=="dog")) { //loop through either list to find animal type
                    i++;
                }
                either.removeKth(i);
                outputFile << dogShelter.pop() << endl; //ouput animal name to output file
            }
            
            else if (type == "either"){ //either handling
                if(either.getKth(0) == "dog"&& !dogShelter.isEmpty()) {
                    outputFile<< dogShelter.pop() << endl; //ouput animal name to output file
                }
                else if (either.getKth(0) == "cat"&& !catShelter.isEmpty()) {
                    outputFile<< catShelter.pop() << endl; //ouput animal name to output file
                }
                either.decapitate();
            }
        }
    }
    inputFile.close(); //close the files
    outputFile.close();
}
