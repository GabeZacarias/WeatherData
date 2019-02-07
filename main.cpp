#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>

using namespace std;


//Function declarations
void open_files(ifstream& in_stream, ofstream& out_stream);

void page_header(ofstream& out_stream);

double compute_wind_chill(double temperature, double windSpeed);

double compute_cloud_base(double temperature, double dewPoint);

void print_data(double temperature, double windSpeed, double dewPoint, double& windChill, double& cloudBase, ofstream& out_stream);

bool page_footer = false;

void error_message(bool page_footer, ofstream& out_stream);


//Function call
int main()
{
	ifstream in_stream;  //declares an input file stream called in_stream

	ofstream out_stream; // declares an output file stream called out_stream

    double temperature, windSpeed, dewPoint, windChill, cloudBase;

	open_files(in_stream, out_stream);

	page_header(out_stream);

	in_stream >> temperature >> windSpeed >> dewPoint;   //reads data

while (temperature != -99)
    {
        windChill = compute_wind_chill(temperature, windSpeed);

        cloudBase = compute_cloud_base(temperature, dewPoint);

        print_data(temperature, windSpeed, dewPoint, windChill, cloudBase, out_stream);

        in_stream >> temperature >> windSpeed >> dewPoint;
    }

    error_message(page_footer, out_stream);

    in_stream.close();                                                                                                     //close the file
    out_stream.close();                                                                                                    //close the file

	return 0;
}


//Function definitions
void open_files(ifstream& in_stream, ofstream& out_stream)
{
    in_stream.open("WeatherData.txt");
        if (in_stream.fail())
            {
                cout << "Input file opening failed." << endl;
                exit(1);  //ends the program
            }

    out_stream.open("GabrielZacarias.txt");
        if (out_stream.fail())
            {
                cout << "Output file opening failed." << endl;
                exit(1);  //ends the program
            }
}


void page_header(ofstream& out_stream)
{
    cout << endl;
    cout << "   Temperature    Wind Speed    Dew Point    Wind Chill    Cloud Base" << endl;
    cout << "  --------------------------------------------------------------------" << endl;

    out_stream << endl;
    out_stream << "   Temperature    Wind Speed    Dew Point    Wind Chill    Cloud Base" << endl;
    out_stream << "  --------------------------------------------------------------------" << endl;
}


double compute_wind_chill(double temperature, double windSpeed)
{
    double windChill;
    windChill = 35.74 + (0.621*temperature) - 35.75*(pow(windSpeed,0.16)) + (0.4275*temperature)*(pow(windSpeed,0.16));
    return (windChill);
}


double compute_cloud_base(double temperature, double dewPoint)
{
    double cloudBase;
    cloudBase = (((temperature)-(dewPoint))/4.4)*(1000);
    return (cloudBase);
}


void print_data(double temperature, double windSpeed, double dewPoint, double& windChill, double& cloudBase, ofstream& out_stream)
{
    cout.setf (ios:: fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);

    if (temperature >= 50 || windSpeed < 3.0)
        {
            cout << setw(9) << temperature << " dF" << setw(10) << windSpeed << " mph" << setw(11) << dewPoint << " dF" << setw(13) << "***" << setw(14) << cloudBase << " ft" <<endl;
            page_footer = true;
        }
    else
        {
            cout << setw(9) << temperature << " dF" << setw(10) << windSpeed << " mph" << setw(11) << dewPoint << " dF" << setw(12) << windChill << " dF" << setw(12) << cloudBase << " ft" <<endl;
        }


    out_stream.setf (ios:: fixed);
    out_stream.setf(ios::showpoint);
    out_stream.precision(1);

    if (temperature >= 50 || windSpeed < 3.0)
        {
            out_stream << setw(9) << temperature << " dF" << setw(10) << windSpeed << " mph" << setw(11) << dewPoint << " dF" << setw(13) << "***" << setw(14) << cloudBase << " ft" <<endl;
            page_footer = true;
        }
    else
        {
            out_stream << setw(9) << temperature << " dF" << setw(10) << windSpeed << " mph" << setw(11) << dewPoint << " dF" << setw(12) << windChill << " dF" << setw(12) << cloudBase << " ft" <<endl;
        }
}


void error_message(bool page_footer, ofstream& out_stream)
{
    if (page_footer == true)
        {
            cout << endl;
            cout << " *** There is no wind chill factor at this temperature or wind speed. ***" << endl;
            cout << endl << endl;
            cout << "    *** Temperature must be 50 degrees or less, and wind speed" << endl;
            cout << "        must be 3 mph or more to compute wind chill." << endl;
        }


    if (page_footer == true)
        {
            out_stream << endl;
            out_stream << " *** There is no wind chill factor at this temperature or wind speed. ***" << endl;
            out_stream << endl << endl;
            out_stream << "    *** Temperature must be 50 degrees or less, and wind speed" << endl;
            out_stream << "        must be 3 mph or more to compute wind chill." << endl;
        }
}
