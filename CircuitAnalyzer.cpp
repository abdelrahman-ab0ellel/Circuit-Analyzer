#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool error(const string& s1);//function to validate the input string

int main()
{
    string s;
    cout << "Enter the circuit description: ";
    getline(cin, s); //get the circuit description from the user

    //check if the input string has errors
    if (error(s))
    {
        cout << "Error: Invalid circuit description.\n";
        exit(0);
    }

    float result = 0 ;
    int connection_count=0;

    for(int i=0; i<s.length() ; i++) //calculate total number of connections
        {
            if(s[i] == 's' || s[i] == 'S' || s[i] == 'p' || s[i] == 'P')
            {
                connection_count++;
            }
        }

    //process the input string until the last connection
    for(int j=0; j<connection_count; j++)
    {
        int start_index, end_index, l = s.length(), countS=0, countP=0;

        //find the start index of the next connection type
        for (int i = 0; i < l; i++)
        {
            if (s[i] == 's' || s[i] == 'S' || s[i] == 'p' || s[i] == 'P')
            {
                start_index = i;
            }

            if (s[i] == 'e')
            {
                end_index = i;
                break;
            }
        }

        //extract the substring for the current connection
        string middle = s.substr(start_index, end_index - start_index + 1);

        string num; // To accumulate characters of resistor values

        // Process series connection
        if (middle[0] == 's' || middle[0] == 'S')
        {
            float series = 0; //Sum of resistors in series

            int dot=0;

            for (char ch : middle)
            {
                if (isdigit(ch)) //catch the number inside the string
                    num += ch;

                else if(ch == '.')
                {
                    dot++;
                    num += ch;
                    if (dot>1) //check the number has only one floating point
                    {
                        cout << "Error: Invalid input.\n";
                        exit(0);
                    }
                }
                else if ((ch == 's' || ch == 'S' || ch == ' ' || ch == ',' || ch == 'e') && !num.empty())
                {
                    dot=0;
                    countS++; //count the series resistors
                    series += stof(num); //convert to float and add to series
                    num.clear(); // Reset the number accumulator
                }
            }
            if (countS < 1 || countS>20) //check that the series resistors must be at least 1
            {
                cout << "Error: Invalid input.\n";
                exit(0);
            }
            result = series;
        }

        //process parallel connection
        if (middle[0] == 'p' || middle[0] == 'P')
        {
            float parallel = 0;

            int dot = 0;

            for (char b : middle)
            {
                if (isdigit(b)) //catch the number inside the string
                    num += b;

                else if(b == '.')
                {
                    dot++;
                    num += b;
                    if (dot>1) //check the number has only one floating point
                    {
                        cout << "Error: Invalid input.\n";
                        exit(0);
                    }
                }
                else if ((b == 'p' || b == 'P' || b == ' ' || b == ',' || b == 'e') && !num.empty())
                {
                    dot=0;
                    countP++; //count the parallel resistors
                    parallel += 1.0 / stof(num);
                    num.clear(); // Reset the number accumulator
                }
            }
            if (countP < 2 || countP>20) //check that the parallel resistors must be at least 2
            {
                cout << "Error: Invalid input.\n";
                exit(0);
            }

            if (parallel != 0) // Avoid division by zero (short circuit)
                parallel = 1.0 / parallel; //add to total parallel result

            result=parallel;
        }

        //replace the processed in the original string
        s.replace(start_index, end_index-start_index+1, to_string(result));

        middle.clear(); //clear the temporary string
    }

    // Output the total resistance
    cout << "The total resistance = " << result <<" ohm" << endl;
}

// Function to validate the input string
bool error(const string& s1)
{
    // Check if the first character is a valid connection type
    if (s1[0] != 'p' && s1[0] != 'P' && s1[0] != 's' && s1[0] != 'S')
        return true;

    // Check for invalid characters
    for (char a : s1)
    {
        if (!isdigit(a) && a != ' ' && a != 'P' && a != 'p' && a != 's' && a != 'S' && a != ',' && a != 'e' && a != '.')
            return true;
    }

    // Count the number of connection types and 'e' characters
    int count1 = 0, count2 = 0;
    for (int i = 0; i < s1.length(); i++)
    {
        if (s1[i] == 's' || s1[i] == 'S' || s1[i] == 'p' || s1[i] == 'P')
            count1++;
        if (s1[i] == 'e')
            count2++;
    }

    //check that the number of connection does not exceed the maximum number and every connection has its 'e'
    if (count1 > 20 || count1 != count2)
        return true;

    return false;
}

