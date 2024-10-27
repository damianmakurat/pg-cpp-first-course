#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <complex>
#include <string>

using namespace std;

struct intData {
        int size = 0;
        vector<int> array;
};

struct pointCoords {
        int x = 0;
        int y = 0;
};

int* prepareIntData(int size) {
        int* intDataArray = new int[size];
        for (int i = 0; i < size; i++) {
                cin >> intDataArray[i];
        };
        return intDataArray;
}

double* prepareDoubleData(int size) {
        double* doubleDataArray = new double[size];
        for (int i = 0; i < size; i++) {
                cin >> doubleDataArray[i];
        };
        return doubleDataArray;
}

void displayAnswer(intData answer) {
        int i = 0;
        if (answer.size < 0) {
                cout << "Invalid answer size!" << endl;
        }
        else if (answer.size == 0) {
                cout << answer.array[0] << endl;
        }
        else {
                while (i < answer.size) {
                        cout << answer.array[i];
                        if (i == (answer.size - 1)) {
                                cout << endl;
                        }
                        else {
                                cout << " ";
                        }
                        i++;
                }
        }
}

intData f0(int size, int* data) {
        int min = 0;
        int new_size = 0;
        intData answer;
        int* min_pos = new int[size];
        for (int i = 0; i < size; i++) {
                if (i == 0) {
                        min = data[i];
                        min_pos[new_size++] = i;
                }
                else if (data[i] == min) {
                        min_pos[new_size++] = i;
                }
                else if (data[i] < min) {
                        min = data[i];
                        new_size = 0;
                        min_pos[new_size++] = i;
                }
        }
        answer.size = new_size;
        for (int i = 0; i < new_size; i++) {
                answer.array.push_back(min_pos[i] + 1);
        }
        delete[] min_pos;
        return answer;
}

intData f1(int size, int* data) {
        intData answer;
        intData temp_answer;
        answer.size = size;
        while (size) {
                temp_answer = f0((size), data);
                int k = 0;
                for (int i = 0; i < size; i++) {
                        bool found = false;
                        for (int j = 0; j < temp_answer.size; j++) {
                                if (i == temp_answer.array[j] - 1) {
                                        found = true;
                                        answer.array.insert(answer.array.begin(), data[i]);
                                        break;
                                }
                        }
                        if (!found) {
                                data[k] = data[i];
                                k++;
                        }
                }
                size = size - temp_answer.size;
        }
        return answer;
}

intData f2(int size, double* data) {
        intData answer;
        double fetch = 0;
        for (int i = 0; i < size; i++)
        {
                fetch = fetch + (data[i] * data[i]);
        }
        fetch = sqrt(fetch);
        answer.array.push_back(static_cast<int>(fetch));
        return answer;
}

intData f3(int size, double* data) {
        intData answer;
        intData temp_answer;
        double average = 0;
        double deviation = 0;
        for (int i = 0; i < size; i++) {
                average += data[i];
        }
        average = average / size;
        for (int i = 0; i < size; i++) {
                double temp_data[1];
                temp_data[0] = data[i];
                temp_answer = f2(1, temp_data);
                deviation += pow(temp_answer.array[0], 2) - pow(average, 2);
        }
        deviation = sqrt(deviation / size);
        answer.array.push_back(static_cast<int>(deviation));
        return answer;
}

intData f4(int size, int* data) {
        intData answer;
        answer.size = size;
        int new_size = size;
        if (size == 1) {
                answer.array.push_back(data[0]);
        }
        else {
                if (size % 2 == 0) {
                        new_size = size;
                }
                else {
                        new_size = size - 1;
                }
                for (int i = 0; i < new_size / 2; i++) {
                        data[i] = data[i] + data[size - i - 1];
                        data[size - i - 1] = data[i] - data[size - i - 1];
                        data[i] = data[i] - data[size - i - 1];
                }
                for (int i = 0; i < size; i++) {
                        answer.array.push_back(data[i]);
                }
        }
        delete[] data;
        return answer;
}

void f5(int size) {
        vector<int> dataArray(size);
        vector<int> sweetAnswer(size, 1);
        for (int i = 0; i < size; i++) {
                cin >> dataArray[i];
                if (dataArray[i] < 2) {
                        sweetAnswer[i] = 0;
                }
        };
        int maxNumber = dataArray[0];
        for (int i = 0; i < size; i++) {
                if (dataArray[i] > maxNumber) {
                        maxNumber = dataArray[i];
                }
        };
        for (int i = 0; i < size; i++) {
                if (sweetAnswer[i] != 0) {
                        int j = 2;
                        while (j * j <= dataArray[i]) {
                                if (dataArray[i] % j == 0) {
                                        sweetAnswer[i] = 0;
                                        break;
                                }
                                j++;
                        }
                }
        }
        for (int i = 0; i < size; i++) {
                cout << sweetAnswer[i] << " ";
        }
        cout << endl;
}

void f6(int size, double* data) {
        int points = size / 2;
        pointCoords* points_array = new pointCoords[points];

        for (int i = 0; i < points; ++i) {
                points_array[i].x = static_cast<int>(data[i * 2]);
                points_array[i].y = static_cast<int>(data[i * 2 + 1]);
        }

        long double temp_answer = 0;
        long double first = 0;
        long double second = 0;

        for (int i = 0; i < (points - 1); i++) {
                first += (points_array[i].x * points_array[i + 1].y);
        }

        for (int i = 0; i < (points - 1); i++) {
                second += points_array[i + 1].x * points_array[i].y;
        }

        temp_answer = abs(first + (points_array[points - 1].x * points_array[0].y) - second - (points_array[0].x * points_array[points - 1].y)) / 2;

        delete[] points_array;
        delete[] data;

        cout << static_cast<long long>(floor(temp_answer)) << endl;
}

void f7(double* data) {
        intData answer;
        if (data[0] == 0) {
                double a = data[1];
                double b = data[2];
                double c = data[3];
                double delta = (b * b) - ((4 * a) * c);
                if (delta > 0) {
                        double x1 = (-b + sqrt(delta)) / (2 * a);
                        double x2 = (-b - sqrt(delta)) / (2 * a);
                        if (x1 > x2) {
                                answer.array.push_back(static_cast<int>(floor(x2)));
                                answer.array.push_back(static_cast<int>(floor(x1)));
                        }
                        else {
                                answer.array.push_back(static_cast<int>(floor(x1)));
                                answer.array.push_back(static_cast<int>(floor(x2)));
                        }
                        answer.size = 2;
                }
                else if (delta == 0) {
                        double x1 = (-b - sqrt(delta)) / (2 * a);
                        answer.array.push_back(static_cast<int>(floor(x1)));
                }
                else {
                        cout << "Error! Negative delta!" << endl;
                }
                delete[] data;
                displayAnswer(answer);
        }
        else {
                double a = data[1];
                double b = data[2];
                double c = data[3];
                double d = data[4];
                double delta3 = (18 * a * b * c * d) - (4 * a * (c * c * c)) - (4 * (b * b * b) * d) + ((b * b) * (c * c)) - (27 * (a * a) * (d * d));
                // double delta3b = delta3 / ((-27) * (a * a * a * a));
                // double p = ((3 * a * c) - (b * b)) / (3 * (a * a));
                // double q = ((2 * (b * b * b)) - (9 * a * b * c) + (27 * (a * a) * d)) / (27 * (a * a * a));
                if (delta3 > 0) { //RZECZYWISTY, ROZNE TRZY
                        double A = cbrt((delta3 + sqrt(delta3)) / 2);
                        double B = cbrt((delta3 - sqrt(delta3)) / 2);

                        complex<double> x1 = (-b) / ((3 * a) - (A + B));
                        complex<double> x2 = (-b) / ((3 * a) + 0.5 * (A + B));
                        complex<double> x3 = (-b) / ((3 * a) - 0.5 * (A + B));

                        cout << x1 << " " << x2 << " " << x3 << endl;
                }
                else if (delta3 == 0) { //RZECZYWISTY, WIELOKROTNOSC 2
                        complex<double> x1 = (-b) / ((3 * a) - cbrt((-delta3) / 2));
                        complex<double> x2 = (-b) / ((3 * a) + 2 * cbrt((-delta3) / 2));

                        cout << x1 << " " << x2 << " " << "0" << endl;
                }
                else { //TYLKO JEDEN RZECZYWISTY
                        complex<double> C = cbrt(sqrt((-delta3) + ((3 * a) * (3 * a) * (3 * a))) / 2);
                        complex<double> x1 = -b / (3 * a) + 2.0 * C;
                        complex<double> x2 = -b / (3 * a) - 0.5 * (C + sqrt(3.0) * complex<double>(0, 1) * C);
                        complex<double> x3 = -b / (3 * a) - 0.5 * (C - sqrt(3.0) * complex<double>(0, 1) * C);

                        cout << x1 << " " << x2 << " " << x3 << endl;
                }
                delete[] data;
                return ;
        }
}

void f8() {
        long long number;
        cin >> number;

        long long s1, s2, s3, answer;
        s1 = ((number * number) * ((number + 1) * (number + 1))) / 4;
        s2 = (number * (number + 1) * (2 * number + 1)) / 3;
        s3 = (number * (number + 1)) / 2;
        answer = s1 + s2 + s3;

        cout << answer << endl;
}

string getBinary(string decimal) {
        string binary = "";
        while (decimal != "0") {
                int last_digit = decimal.back() - '0';
                binary = binary + to_string(last_digit % 2);
                string result = "";
                int rest = 0;
                for (int i = 0; i < static_cast<int>(decimal.length()); i++) {
                        int digit = decimal[i] - '0';
                        int divide = (digit + rest * 10) / 2;
                        rest = (digit + rest * 10) % 2;
                        result = result + to_string(divide);
                }
                int i = 0;
                while (i < static_cast<int>(result.length())) {
                        if (result[i] == '0') {
                                i++;
                        }
                        else {
                                break;
                        }
                }
                if (i == static_cast<int>(result.length())) {
                        decimal = "0";
                }
                else {
                        decimal = result.substr(i);
                }
        }
        reverse(binary.begin(), binary.end());
        return binary;
}

void f9(int size) {
        vector<string> data(size);

        for (int i = 0; i < size; i++) {
                cin >> data[i];
        }

        for (int i = 0; i < size; i++) {
                int count = 0;
                string binary = getBinary(data[i]);
                for (int j = 0; j < static_cast<int>(binary.size()); j++) {
                        if (binary[j] == '1') {
                                count++;
                        }
                }
                cout << count << " ";
        }
        cout << endl;
}

int main() {
        int subprogram, size;

        while (cin >> subprogram >> size) {
                if (size > 0) {
                        intData answer;
                        int* intDataArray = new int[size];
                        double* doubleDataArray = new double[size];
                        switch (subprogram) {
                        case 0:
                                intDataArray = prepareIntData(size);
                                answer = f0(size, intDataArray);
                                displayAnswer(answer);
                                break;
                        case 1:
                                intDataArray = prepareIntData(size);
                                answer = f1(size, intDataArray);
                                displayAnswer(answer);
                                break;
                        case 2:
                                doubleDataArray = prepareDoubleData(size);
                                answer = f2(size, doubleDataArray);
                                displayAnswer(answer);
                                break;
                        case 3:
                                doubleDataArray = prepareDoubleData(size);
                                answer = f3(size, doubleDataArray);
                                displayAnswer(answer);
                                break;
                        case 4:
                                answer = f4(size, prepareIntData(size));
                                displayAnswer(answer);
                                break;
                        case 5:
                                f5(size);
                                break;
                        case 6:
                                f6(size, prepareDoubleData(size));
                                break;
                        case 7:
                                f7(prepareDoubleData(size));
                                break;
                        case 8:
                                f8();
                                break;
                        case 9:
                                f9(size);
                                break;
                        default:
                                cout << "Invalid input!" << endl;
                                break;
                        }
                        delete[] doubleDataArray;
                        delete[] intDataArray;
                }
                else {
                        cout << "Invalid size number!" << endl;
                }
        }
        return 0;
}
