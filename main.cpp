#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h> //allows system pause
using namespace std;
//to compile in Dev-C++, TOOLS -> COMPILER OPTIONS -> ADD THE FOLLOWING OPTIONS WHEN CALLING THE COMPILER -> -std=c++11

//class to store all relevant calculation data
class projectile {
    private:
        int N;
        double const GRAV_CONSTANT = -9.81; 
        double const PI = acos(-1);
        double const HALF_GRAV = -9.81 * 0.5;
        double height, angle, initialVelocity, initialHorizontalVelocity, initialVerticalVelocity, totalTime, totalDistanceTravelled, maximumHeight;
        double distances[100], times[100], heights[100];
        vector<double> tableVector;
        string name;

        double convertDegreesToRadians(double inputAngle) {return  (PI/180) * inputAngle;}

        double calculateInitialHorizontalVelocity() {return initialVelocity * (cos(angle));}

        double calculateInitialVerticalVelocity() {return initialVelocity * (sin(angle));}

        double calculateDistanceTravelled() {return  initialHorizontalVelocity * totalTime;}

        double calculateMaximumHeight() {return height - ((pow(initialVerticalVelocity, 2))/(2 * GRAV_CONSTANT));}
        //instead of determine real roots function, this will use projectile data as coefficients to return positive root. Used in the constructor
        double calculateTotalTime() {return ((-1 * initialVerticalVelocity) - sqrt((pow(initialVerticalVelocity, 2))-(4 * HALF_GRAV * height))) / (2 * HALF_GRAV);}
        
    public:
        //constructor calculates all missing essential variables .
        projectile(double inputHeight, double inputAngle, double inputVelocity, string inputName, int inputN) {
            height = inputHeight;
            angle = convertDegreesToRadians(inputAngle);
            initialVelocity = inputVelocity;
            initialHorizontalVelocity = calculateInitialHorizontalVelocity();
            initialVerticalVelocity = calculateInitialVerticalVelocity();
            totalTime = calculateTotalTime();
            totalDistanceTravelled = calculateDistanceTravelled();
            maximumHeight = calculateMaximumHeight();
            name = inputName;
            N = inputN;

        }
        //populates array with table data 
        void fillArrays(int N) {

            for (int i = 0; i < N; i++) {
                distances[i] = (i / (1.0 * (N-1))) * totalDistanceTravelled;
                times[i] = distances[i] / (initialHorizontalVelocity);
                heights[i] = (initialVerticalVelocity * times[i]) + (HALF_GRAV * (pow(times[i], 2)));
            }
        }
        //this function uses stream as an argument to be used in both cout and writing a file
        void write(ostream &stream, string seperator, int i) {
            stream << fixed << setprecision(3) << setw(7) << times[i]  << seperator << setw(8) << distances[i] << seperator << setw(9) << heights[i] << endl;
        }
        //used to obtain projectile data for further calculations, outputs, and program manipulation
        double getAngle() {return angle;}
        double getInitialVelocity() {return initialVelocity;}
        double getHeight() {return height;}
        string getName() {return name;}
        double getTotalTime() {return totalTime;}
        double getTotalDistance() {return totalDistanceTravelled;}
        double getMaxHeight() {return maximumHeight;}
        int getN() {return N;}
        //fill vector of table data
        void fillTableVector(int N) {
            for (int i = 0; i < N; i++) {
                tableVector.push_back(times[i]);
                tableVector.push_back(distances[i]);
                tableVector.push_back(heights[i]);
            }
        }
        //used to convert back to degrees for GUI output
        double convertRadiansToDegrees(double angle) {
            return angle * (180/PI);
        }
};
//vector of projectile objects for storing different problem sets in memory
vector<projectile> projectileList;
//functions to take input strings and output a formatted, stylazied prompt or error
void createPrompt(string text) {
    string newString = "@    " + text + "    @";
    int promptWidth = newString.length();
    for (int i = 0; i < newString.length(); i++) {
        cout << "@";
    }
    cout << "\n";
    cout << "@";
    for (int i = 0; i < newString.length()-2; i++) {
        cout << " ";
    }
    cout << "@";
    cout << "\n";
    cout << newString;
    cout << "\n";
    cout << "@";
    for (int i = 0; i < newString.length()-2; i++) {
        cout << " ";
    }
    cout << "@";
    cout << "\n";
    for (int i = 0; i < newString.length(); i++) {
        cout << "@";
    }
    cout << "\n";
}
void createPrompt(string one, string two) { //overloads the function for multiple lines of output
    string newString;
    string oneString = "@    " + one + "    @";
    string twoString = "@    " + two + "    @";
    if (oneString.length() > twoString.length()) { //uses longest string to set width of formatted box
        newString = oneString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << "@    ";
        int extraSpaces = oneString.length() - twoString.length();
        cout << two;
        for (int i = 0; i < extraSpaces + 4; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
    }
    else if (twoString.length() > oneString.length()) {
        newString = twoString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        cout << "@    ";
        int extraSpaces = twoString.length() - oneString.length();
        cout << one;
        for (int i = 0; i < extraSpaces + 4; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
    }
    else if (oneString.length() == twoString.length()) {
        newString = oneString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << twoString;
        cout << "\n";
        cout << "@";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "@";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "@";
        }
    }
    cout << "\n";
}
void createError(string one, string two) {
    string newString;
    string oneString = "#    " + one + "    #";
    string twoString = "#    " + two + "    #";
    if (oneString.length() > twoString.length()) {
        newString = oneString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << "#    ";
        int extraSpaces = oneString.length() - twoString.length();
        cout << two;
        for (int i = 0; i < extraSpaces + 4; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
    }
    else if (twoString.length() > oneString.length()) {
        newString = twoString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        cout << "#    ";
        int extraSpaces = twoString.length() - oneString.length();
        cout << one;
        for (int i = 0; i < extraSpaces + 4; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
    }
    else if (oneString.length() == twoString.length()) {
        newString = oneString;
        int promptWidth = newString.length();
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        cout << newString;
        cout << "\n";
        cout << twoString;
        cout << "\n";
        cout << "#";
        for (int i = 0; i < newString.length()-2; i++) {
            cout << " ";
        }
        cout << "#";
        cout << "\n";
        for (int i = 0; i < newString.length(); i++) {
            cout << "#";
        }
    }
    cout << "\n";
}
void createError(string text) {
    string newString = "#    " + text + "    #";
    int promptWidth = newString.length();
    for (int i = 0; i < newString.length(); i++) {
        cout << "#";
    }
    cout << "\n";
    cout << "#";
    for (int i = 0; i < newString.length()-2; i++) {
        cout << " ";
    }
    cout << "#";
    cout << "\n";
    cout << newString;
    cout << "\n";
    cout << "#";
    for (int i = 0; i < newString.length()-2; i++) {
        cout << " ";
    }
    cout << "#";
    cout << "\n";
    for (int i = 0; i < newString.length(); i++) {
        cout << "#";
    }
    cout << "\n";
}
//functions with built-in error checks to get out constructior data from user
string getFileNameFromUser() {
    bool failed;
    string inputFileName, tempFileName;
    ofstream writeToFile;
    do {
        createPrompt("Save as:");
        cout << "--> ";
        cin >> inputFileName;
        string tempFileName = inputFileName + ".csv";
    
        ofstream writeToFile(tempFileName);
        failed = writeToFile.fail();
    
        if (failed) {
            createError("Invalid character");
        }
        cout << "\n";
    } while (failed);

    writeToFile.close();
    
    return inputFileName + ".csv";
}
double getAngleFromUser() {
    double inputAngle;
    createPrompt("Input angle in degrees:");
    cout << "-->";
    cin >> inputAngle;
    while (inputAngle <= 0 || inputAngle >= 90) {
        createError("Invalid angle. Must be greater than zero and less than 90", "Input angle in degrees:");
        cout << "-->";
        cin >> inputAngle;
    }
    cin.ignore();
    return inputAngle;
}
double getInitialVelocityFromUser() {
    double inputVelocity;
    createPrompt("Input initial velocity in m/s:");
    cout << "-->";
    cin >> inputVelocity;
    while (inputVelocity <= 0) {
        createError("Invalid Velocity. Must be greater than zero", "Input initial velocity in m/s:");
        cout << "-->";
        cin >> inputVelocity;
    }
    cin.ignore();
    return inputVelocity;
}
double getHeightFromUser() {
    double inputHeight;
    createPrompt("Input Height in meters: ");
    cout << "-->";
    cin >> inputHeight;
    while (inputHeight <= 0) {
        createError("Invalid height. Must be greater than zero", "Input Height in meters:");
        cout << "-->";
        cin >> inputHeight;
    }
    cin.ignore();
    
    return inputHeight;
}
int getNfromUser() {
    int inputN; 
    createPrompt("How many increments of distance?");
    cout << "-->";
    cin >> inputN;
    while (inputN <= 5 || inputN > 100) {
        createError("Invalid increment. Must be greater than five and less than 101", "How many increments of distance?(How many rows to be output):");
        cout << "-->";
        cin >> inputN;
    }
    cin.ignore();
    return inputN;
}
string getNameFromUser() {
    string name;
    createPrompt("Input Projectile Name:", "(No more than 16 characters)");
    cout << "-->";
    getline(cin, name);
    while (name.length() > 16) {
        createError("Invalid Name:", "Input Name of 16 characters or less");
        cout << "-->";
        getline(cin, name);
    }
    return name;
}
//adds a projectile object to a vector
void addProjectileToVector(projectile newProjectile) {
    projectileList.push_back(newProjectile);
}
//function to output a table of projectiles stored with their corresponding data
void viewProjectiles() {
    cout << left << setw(1) << "_" << "|" << setw(16) << "______Name______" << "|" << setw(10) << "___h(m)___" << "|" << setw(12) << "___A(deg)___" << "|" << setw(11) << "__Vo(m/s)__" << endl;
    for (int i = 0; i < projectileList.size(); i++) {
        projectile temp = projectileList[i];
        cout << left << setw(1) << i+1 << "|" << setw(16) << temp.getName() << "|" << setw(10) << temp.getHeight() << "|" << setw(12) << temp.convertRadiansToDegrees(temp.getAngle()) << "|" << setw(11) << temp.getInitialVelocity() << endl;
    }
}
//creates projectile object based on user input data
projectile createNewProjectile() {
    double height = getHeightFromUser();
    double angle = getAngleFromUser();
    double velocity = getInitialVelocityFromUser();
    string name = getNameFromUser();
    int N = getNfromUser();
    projectile temp = projectile(height, angle, velocity, name, N);
    return temp;
}
projectile createNewProjectile(double height, double angle, double velocity, string name, int N) { //overloaded for flexibility
    projectile temp = projectile(height, angle, velocity, name, N);
    return temp;
}
//pauses system for 1.5s and clear screen
void systemPause() {
    Sleep(1500);
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
//populates "view Projectile" identifier column
string getStringFromInt(int length) {
    if (length == 0) {
        return "0";
    }
    else if (length == 1) {
        return "1";
    }
    else if (length == 2) {
        return "2";
    }
    else if (length == 3) {
        return "3";
    }
    else if (length == 4) {
        return "4";
    }
    else if (length == 5) {
        return "5";
    }
    else if (length == 6) {
        return "6";
    }
    else return "0";
}




int main () {
    
    createPrompt("Projectile Calculator", "Press ENTER to begin:");
    cout << "--> ";
    cin.get();
    //create first projectile
    projectile newProjectile = createNewProjectile();
    addProjectileToVector(newProjectile);
    newProjectile.fillArrays(newProjectile.getN());
    createPrompt(newProjectile.getName() + " added");
    systemPause();
    
    //stay within home screen and its functions until exit is selected
    while (projectileList.size() <= 6) {
        string vectorCounter = getStringFromInt(projectileList.size()); //used to display a how many projectiles are in memory
        createPrompt("HOME SCREEN: (" + vectorCounter + "/6)", "1)Add Projectile    2)View Projectile    3)Save All    4)Exit");
        int handleHomeScreen;
        cout << "--> ";
        cin >> handleHomeScreen;
        //cases are home screen options
        switch (handleHomeScreen) {
            case 1: {
                if(projectileList.size() == 6) {
                    createError("Calculator Full");
                    break;
                }
                projectile projectile2 = createNewProjectile();
                addProjectileToVector(projectile2);
                projectile2.fillArrays(projectile2.getN());
                createPrompt(projectile2.getName() + " added");
                systemPause();
                break;
            }
            case 2: {
                viewProjectiles();
                int handleViewScreen;
                createPrompt("Select a projectile by inputting its number from the table");
                cout << "--> ";
                cin >> handleViewScreen;
                //switch for user selected position in the projectile table
                switch (handleViewScreen) {
                    case 1: {
                        viewProjectiles();
                        createPrompt(projectileList[0].getName());
                        //outputs various object data in the selection screen
                        cout << "h = " << projectileList[0].getHeight();
                        cout << "    A = " << projectileList[0].convertRadiansToDegrees(projectileList[0].getAngle());
                        cout << "    Vo = " << projectileList[0].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[0].getTotalTime();
                        cout << "    total distance = " << projectileList[0].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[0].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        //user chooses to print table or save it as a csv
                        if (printOrSave == 1) {
                            projectile temp = projectileList[0];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[0];
                            temp.fillArrays(temp.getN());
                            //writes a formatted .csv with titles and other various data
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";

                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();
                            createPrompt("Save Successful");
                            systemPause();
                            
                        }
                        break;
                    }
                    case 2: {
                        //see above case for comments
                        viewProjectiles();
                        createPrompt(projectileList[1].getName());
                        cout << "h = " << projectileList[1].getHeight();
                        cout << "    A = " << projectileList[1].convertRadiansToDegrees(projectileList[1].getAngle());
                        cout << "    Vo =" << projectileList[1].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[1].getTotalTime();
                        cout << "    total distance = " << projectileList[1].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[1].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        if (printOrSave == 1) {
                            projectile temp = projectileList[1];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[1];
                            temp.fillArrays(temp.getN());
                            
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";

                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();
                            
                            createPrompt("Save Successful");
                            systemPause();
                        }
                        break;
                    }
                    case 3: {
                        viewProjectiles();
                        createPrompt(projectileList[2].getName());
                        cout << "h = " << projectileList[2].getHeight();
                        cout << "    A = " << projectileList[2].convertRadiansToDegrees(projectileList[2].getAngle());
                        cout << "    Vo = " << projectileList[2].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[2].getTotalTime();
                        cout << "    total distance = " << projectileList[2].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[2].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        if (printOrSave == 1) {
                            projectile temp = projectileList[2];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[2];
                            temp.fillArrays(temp.getN());
                            
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";
                            
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();

                            createPrompt("Save Successful");
                            systemPause();
                        }
                        break;
                    }
                    case 4: {
                        viewProjectiles();
                        createPrompt(projectileList[3].getName());
                        cout << "h = " << projectileList[3].getHeight();
                        cout << "    A = " << projectileList[3].convertRadiansToDegrees(projectileList[3].getAngle());
                        cout << "    Vo =" << projectileList[3].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[3].getTotalTime();
                        cout << "     total distance = " << projectileList[3].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[3].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        if (printOrSave == 1) {
                            projectile temp = projectileList[3];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[3];
                            temp.fillArrays(temp.getN());
                            
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";
                            
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();

                            createPrompt("Save Successful");
                            systemPause();
                        }
                        break;
                    }
                    case 5: {
                        viewProjectiles();
                        createPrompt(projectileList[4].getName());
                        cout << "h = " << projectileList[4].getHeight();
                        cout << "    A = " << projectileList[4].convertRadiansToDegrees(projectileList[4].getAngle());
                        cout << "    Vo =" << projectileList[4].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[4].getTotalTime();
                        cout << "    total distance = " << projectileList[4].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[4].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        if (printOrSave == 1) {
                            projectile temp = projectileList[4];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[4];
                            temp.fillArrays(temp.getN());
                            
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";
                            
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();

                            createPrompt("Save Successful");
                            systemPause();
                        }
                        break;
                    }
                    case 6: {
                        viewProjectiles();
                        createPrompt(projectileList[5].getName());
                        cout << "h = " << projectileList[5].getHeight();
                        cout << "    A = " << projectileList[5].convertRadiansToDegrees(projectileList[5].getAngle());
                        cout << "    Vo =" << projectileList[5].getInitialVelocity() << "\n";
                        cout << "total time = " << projectileList[5].getTotalTime();
                        cout << "     total distance = " << projectileList[5].getTotalDistance() << "\n";
                        cout << "maximum height = " << projectileList[5].getMaxHeight() << "\n";

                        createPrompt("Select an option:", "1)Print Trajectory   2)Save as .csv");
                        int printOrSave;
                        cout << "--> ";
                        cin >> printOrSave;
                        if (printOrSave == 1) {
                            projectile temp = projectileList[5];
                            temp.fillArrays(temp.getN());
                            cout << left << setw(7) << "TIME(s)" << " | " << setw(8) << "DIST (m)" << " | " << setw(9) << "HEIGHT(m)\n";
                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(cout, " | ", i);
                            }
                        }
                        else if (printOrSave == 2) {
                            string fileName = getFileNameFromUser();
                            ofstream newWrite(fileName);
                            projectile temp = projectileList[5];
                            temp.fillArrays(temp.getN());
                            
                            newWrite << temp.getName() << "\n";
                            newWrite << "Angle =" << "," << "=" << temp.convertRadiansToDegrees(temp.getAngle()) << "," << "deg" << "\n";
                            newWrite << "V_o =" << "," << temp.getInitialVelocity() << "," << "m/s" << "\n";
                            newWrite << "Height =" << "," << temp.getHeight() << "," << "m";
                            newWrite << "\n";
                            newWrite << "time(s),dist(m),height(m)\n";

                            for (int i = 0; i < temp.getN(); i++) {
                                temp.write(newWrite, ",", i);
                            }
                            
                            newWrite.close();
                            
                            createPrompt("Save Successful");
                            systemPause();
                        }
                        break;
                    }
                }   
                break;
            }
            //case 3 allows user to save all projectile tables in memory to one single .csv file
            case 3: {
                int count = 0;
                string fileName = getFileNameFromUser();
                ofstream newWrite(fileName);
                projectile temp = projectileList[count];
                temp.fillArrays(temp.getN());
                //loops through vector of projectiles to save the data in formatted form
                while (count < projectileList.size()) {
                    newWrite << projectileList[count].getName() << "\n";
                    newWrite << "Angle =" << "," << "=" << projectileList[count].convertRadiansToDegrees(projectileList[count].getAngle()) << "," << "deg" << "\n";
                    newWrite << "V_o =" << "," << projectileList[count].getInitialVelocity() << "," << "m/s" << "\n";
                    newWrite << "Height =" << "," << projectileList[count].getHeight() << "," << "m";
                    newWrite << "\n";
                    newWrite << "time(s),dist(m),height(m)\n";
                    
                    projectile temp = projectileList[count];
                    temp.fillArrays(temp.getN());
                        
                    for (int i = 0; i < temp.getN(); i++) {
                        temp.write(newWrite, ",", i);
                    }
                    
                    newWrite << "\n\n\n";
                    count++;
                }
                createPrompt("Save Successful");
                systemPause();

                break;
            }
            //case 4 allows the user to exit the program
            case 4: {
                createPrompt("See You Soon!");
                systemPause();
                return 0;
            }

        }
    }
}
