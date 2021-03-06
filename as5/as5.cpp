// as5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//CODE (Skeleton Code by Jorge Fonseca)
//Created by Jorge Fonseca
//Contact at Jorge.Fonseca@UNLV.edu
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>



#include <array>
using namespace std;

//CHANGE THESE TO THE DATABSE YOU WANT //
//AND TO YOUR OWN AUTHENTICATION CODE  //
////////////////////////////////////////////////
#define DatabaseName "BCHARTS/COINBASEUSD"
#define Authentication "ENTER HERE AUTHENTICATION"
////////////////////////////////////////////////
class DatabaseEntries; //Forward Declaration of Class

//Based on Quandl.com C++ Implementation
// Class to Access Databases at https://www.quandl.com/data/BCHARTS-Bitcoin-Charts-Exchange-Rate-Data //
// In this case we will use: https://www.quandl.com/data/BCHARTS/COINBASEUSD-Bitcoin-Markets-coinbaseUSD
class quandl {
public:
	quandl() {};
	~quandl() {};
	void authenticate(string code) {
		AuthCode = code;
	}
	void downloadData(string FileName, string order) { //order can be asc or desc (ascending or descending)
		//Set optional variables by default
		string type = "csv"; //type, can be changed manually
		string curlCommand = ""; //stores curl command to execute
		string FileNameType = ""; //stores File name
		string website = "https://www.quandl.com/api/v3/datasets/" + FileName
			+ "." + type + "?sort_order=" + order; //URL of Database
		if (AuthCode.length() == 0) {
			cout << "Use authentication to not have limited usage\n";
		} //Check if logged in and warn if not
		else {
			website += "&api_key=" + AuthCode;
		}// add authentication token
		while (FileName.find("/") != std::string::npos) {
			FileName.replace(FileName.find("/"), 1, "_");
		} // Remove any slashes from output file name to avoid issues
		savedName = FileNameType = FileName + "." + type; //save the name of our file
		curlCommand = "curl " + website;
		cout << "Website: " << website << "\nFile: " << FileNameType << "\nCommand: " << curlCommand << endl;

		std::ofstream ofs(FileNameType.c_str(), std::ofstream::out);
		FILE *fp = popen(curlCommand.c_str(), "r"); //call command
		char buf[1024];

		while (fgets(buf, 1024, fp))
			ofs << buf;
		ofs.close();
		pclose(fp);
	}
	string getSavedName() { return savedName; }
private:
	string AuthCode; //Stores your secret Login Token
	string savedName; //Stores name of offline file saved name
};

int entryCount = 0; //Global Count of All Entries in this instance
class DatabaseEntries {
	//Column: Date,       Open,    High,    Low,    Close,   Volume (BTC),  Volume (Currency),  Weighted Price
	//Sample: 2017-11-17, 7838.54, 7849.98, 7836.3, 7849.98, 69.57252208,   545714.604366,      7843.82379782 
public:
	//Constructors
	DatabaseEntries() {
		entryNum = ++entryCount; date = "0000-00-00";
		open = high = low = close = volumeBTC = volumeCURRENCY = weightedPrice = 0.0;
	}
	DatabaseEntries(string d, double o, double h, double l,
		double c, double vB, double vC, double w) {
		date = d; entryNum = ++entryCount; open = o; high = h; low = l;
		close = c; volumeBTC = vB; volumeCURRENCY = vC; weightedPrice = w;
	}
	void EditEntry(string d, double o, double h, double l,
		double c, double vB, double vC, double w) {
		date = d; open = o; high = h; low = l; close = c;
		volumeBTC = vB; volumeCURRENCY = vC; weightedPrice = w;
	}
	//Accessors
	string getDate() const { return date; }
	int getEntryNum() const { return entryNum; }
	double getOpen() const { return open; }
	double getHigh() const { return high; }
	double getLow() const { return low; }
	double getClose() const { return close; }
	double getVolumeBTC() const { return volumeBTC; }
	double getVolumeCurrency() const { return volumeCURRENCY; }
	double getWeightedPrice() const { return weightedPrice; }
	//Modifiers
	void setDate(string d) { date = d; }
	void setEntryNum(int e) { entryNum = e; }
	void setOpen(double o) { open = o; }
	void setHigh(double h) { high = h; }
	void setLow(double l) { low = l; }
	void setClose(double c) { close = c; }
	void setVolumeBTC(double vB) { volumeBTC = vB; }
	void setVolumeCurrency(double vC) { volumeCURRENCY = vC; }
	void setWeightedPrice(double w) { weightedPrice = w; }
	//Printers
	void printEntry() const {
		if (getHigh() == 0.0) {
			cout << "DatabaseEntry #" << entryNum << " is empty.\n";
			return; //Empty Entry
		}
		cout << fixed;
		cout << "DatabaseEntry #" << entryNum << endl;
		cout << "Date: " << getDate() << endl;
		cout << std::setprecision(2);
		cout << "Open: " << getOpen() << endl;
		cout << "High: " << getHigh() << endl;
		cout << "Low: " << getLow() << endl;
		cout << "Close: " << getClose() << endl;
		cout << std::setprecision(8);
		cout << "Volume (BTC): " << getVolumeBTC() << endl;
		cout << fixed;
		cout << "Volume (Currency): " << getVolumeCurrency() << endl;
		cout << "Weighted Price: " << getWeightedPrice() << endl;
	}
private:
	string date;
	int entryNum;
	double open, high, low, close, volumeBTC, volumeCURRENCY, weightedPrice;
};

void readData(string fileName, DatabaseEntries data[]) {
	//Your Code Here

	FILE * pFile;
	
	pFile = fopen(fileName.c_str(), "r+");

	//fprintf (pFile, "%f %s", 3.1416, "PI");
	//rewind (pFile);

	//fscanf (pFile, "%f", &f);
	//fscanf (pFile, "%s", str);
	int i = 0;
	double a, b, c, d, e, f, g, h; //used for data read, per line 
	string date;

	while (true) {
		//read line 1, if its eof return 
		int eof = fscanf(pFile, "%[^,]s", &date);
		if (eof == EOF)
			break;
		fscanf(pFile, "%[^,]d", &b);
		fscanf(pFile, "%[^,]d", &c);
		fscanf(pFile, "%[^,]d", &d);
		fscanf(pFile, "%[^,]d", &e);
		fscanf(pFile, "%[^,]d", &f);
		fscanf(pFile, "%[^,]d", &g);
		fscanf(pFile, "%[^,]d", &h);
		//fscanf(pFile, "%[^,]d", &i);
		data[i].setDate(date);
		data[i].setEntryNum(i + 1);
		data[i].setOpen(b);
		data[i].setHigh(c);
		data[i].setLow(d);
		data[i].setClose(e);
		data[i].setVolumeBTC(f);
		data[i].setVolumeCurrency(g);
		data[i].setWeightedPrice(h);


		i++;

	}


	fclose(pFile);
}

void printFullDatabase(DatabaseEntries data[]) {
	cout << "\n-----------------------------------------\n";
	cout << "Printing Full Database with " << entryCount << " entries." << endl;
	for (int i = 0; i < entryCount; i++) {
		if (data[i].getHigh() != 0.0) {
			data[i].printEntry();
			cout << endl;
		}
	}
	cout << "\n-----------------------------------------\n";
	cout << endl;
}

//Simple Regression on 2 values Open and Close Values.
double regressionOpenClose(DatabaseEntries data[]) { //compute slope on close value based on opening value
	
	return 4.334;
}

double SimpleYintercept(double slope, double y, double x) {//compute y intercept
	//y=mx+b
	//b= y-mx
	return y - slope * x;
}

double computeY(double x, double m, double b) { return m * x + b; }  //y=mx+b

//Client Code
int main() {
	double slope, y_intercept;
	//Get our Data from Database and store it offline
	quandl ql;
	ql.authenticate(Authentication); // see Define for Selecting Password
	ql.downloadData(DatabaseName, "asc"); // see Define for selecting Database

//Read the offline copy and save it in the DatabaseEntries class to begin work
	DatabaseEntries *data = new DatabaseEntries[5000]; //Declare Dynamic Array to store Database Entries
	readData(ql.getSavedName(), data); //Read the offline data

	//Test our Database
	data[0].printEntry(); //Prints 3rd Entry in Database
	printFullDatabase(data); //Prints Full Database.

	//Simple Machine Learning Experiment
	slope = regressionOpenClose(data);
	y_intercept = SimpleYintercept(slope, data[0].getOpen(), data[0].getClose());
	cout << "Final Equation for What the Close value is dependng on the Open value:";
	cout << "Close = " << slope << "*Open + " << y_intercept << endl;
	cout << "Test: If our Open is 25,000 our close should be: ";
	cout << computeY(25000, slope, y_intercept) << endl;

	cout << "To the moon! The End. -Made by Jorge Fonseca" << endl << endl;
	return 0;
}
