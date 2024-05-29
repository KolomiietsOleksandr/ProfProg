#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

struct Pixel {
    int r, g, b;
};

vector<vector<Pixel>> readImage(const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        throw runtime_error("Unable to open input file.");
    }

    vector<vector<Pixel>> image(16, vector<Pixel>(16));
    string line;
    for (int i = 0; i < 16; ++i) {
        if (!getline(infile, line)) {
            throw runtime_error("Input file does not have 16 lines.");
        }
        stringstream ss(line);
        for (int j = 0; j < 16; ++j) {
            if (!(ss >> image[i][j].r)) throw runtime_error("Invalid input format.");
            if (ss.get() != ',') throw runtime_error("Invalid input format.");
            if (!(ss >> image[i][j].g)) throw runtime_error("Invalid input format.");
            if (ss.get() != ',') throw runtime_error("Invalid input format.");
            if (!(ss >> image[i][j].b)) throw runtime_error("Invalid input format.");
            if (ss.peek() == ' ') ss.get();
        }
    }

    return image;
}

void writeImage(const string& filename, const vector<vector<Pixel>>& image) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw runtime_error("Unable to open output file.");
    }

    for (const auto& row : image) {
        for (size_t j = 0; j < row.size(); ++j) {
            outfile << row[j].r << "," << row[j].g << "," << row[j].b;
            if (j < row.size() - 1) outfile << " ";
        }
        outfile << "\n";
    }
}

void processImage(vector<vector<Pixel>>& image, const Pixel& favoriteColor) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (image[i][j].r == favoriteColor.r && image[i][j].g == favoriteColor.g && image[i][j].b == favoriteColor.b) {
                if (i > 0) {
                    image[i-1][j] = favoriteColor;
                }
                if (j > 0) {
                    image[i][j-1] = favoriteColor;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <favorite_color> <output_file>\n";
        cerr << "Favorite color format: R,G,B (e.g., 255,0,0 for red)\n";
        return 1;
    }

    string inputFileName = argv[1];
    string outputFileName = argv[3];

    Pixel favoriteColor;
    stringstream ss(argv[2]);
    if (!(ss >> favoriteColor.r) || ss.get() != ',' || !(ss >> favoriteColor.g) || ss.get() != ',' || !(ss >> favoriteColor.b)) {
        cerr << "Invalid favorite color format.\n";
        return 1;
    }

    try {
        auto image = readImage(inputFileName);
        processImage(image, favoriteColor);
        writeImage(outputFileName, image);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
