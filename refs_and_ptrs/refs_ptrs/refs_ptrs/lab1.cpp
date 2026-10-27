#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct DataPoint {
	double value;
	string label;
	int timeStamp;
};

// Function using reference for efficient parameter passing
void processDataPoint(DataPoint& data){
	data.value *= 1.1;													// Apply 10% scaling factor
	data.timeStamp += 10000;											// Update timestamp
	cout << "Processed: " << data.label << " = " << data.value << endl;
}

// Function using const reference for read-only access
void displayDataPoint(const DataPoint& data) {
	cout << "Data: " << data.label << " | Value: " << data.value << " | Time: " << data.timeStamp << endl;
}

// Function to create a new data point dynamically
DataPoint* createDataPoint(double val, const string& lab, int time){
	DataPoint* newData = new DataPoint;
	newData->value = val;
	newData->label = lab;
	newData->timeStamp = time;

	cout << "Created data point at address: " << newData << endl;
	return newData;
}
void deleteDataPoint(DataPoint*& dataPtr) {

}

int main() {

	// TASK 1
	/*DataPoint sensor1(25.5, "Temperature", 1000);
	cout << "=== Before Processing ===" << endl;
	displayDataPoint(sensor1);

	// Create reference to the data point
	DataPoint& sensorRef = sensor1;
	cout << "\nReference value: " << sensorRef.value << endl;
	cout << "Original and reference have same address: "
		<< (&sensor1 == &sensorRef ? "true" : "false") << endl;
	processDataPoint(sensorRef);

	cout << "\n=== After Processing ===" << endl;
	displayDataPoint(sensor1);										// Shows modified values
	cout << endl;
	// How do references avoid copying the entire DataPoint structure? By refering to the original value
	// What happens when you modify data through the reference ? It modifies the original as the reference is an alias

	// Add another DataPoint and create a reference to it
	DataPoint sensor2(35.5, "Pressure", 1500);
	DataPoint& anotherSensorRef = sensor2;
	cout << "=== Before Processing ===" << endl;
	displayDataPoint(sensor2);
	cout << "\nReference value: " << anotherSensorRef.value << endl;
	cout << "Original and reference have same address: "
		<< (&sensor2 == &anotherSensorRef ? "true" : "false") << endl;
	processDataPoint(anotherSensorRef);

	cout << "\n=== After Processing ===" << endl;
	displayDataPoint(sensor2);

	// Try to reassign the reference to point to the new DataPoint (this will show you a key limitation)
	cout << "\nReassigning reference" << endl;
	//displayDataPoint(anotherSensorRef);
	anotherSensorRef = sensor1;			// This copies data, doesn't reassign reference
	cout << "\nReference value: " << &anotherSensorRef.value << " | " << &sensor1.value << " | " << &sensor2.value << endl;
	//displayDataPoint(anotherSensorRef);
	*/

	// TASK 2
	
	// Create data points using pointers
	DataPoint* humidity = createDataPoint(65.2, "Humidity", 2000);
	DataPoint* pressure = createDataPoint(1013.25, "Pressure", 2000);


	return 0;
}