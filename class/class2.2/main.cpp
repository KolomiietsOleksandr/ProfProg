#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>

using namespace std;

struct Pixel {
    int r, g, b;
};

const int pixel = 16;

class Image {
public:
    Image(int size) : image(size, vector<Pixel>(size)) {}

    void read(const string& filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            throw runtime_error("Unable to open input file.");
        }

        string line;
        for (int i = 0; i < pixel; ++i) {
            if (!getline(infile, line)) {
                throw runtime_error("Input file does not have 16 lines.");
            }
            stringstream ss(line);
            for (int j = 0; j < pixel; ++j) {
                image[i][j] = parsePixel(ss);
            }
        }
    }

    void process(const Pixel& favoriteColor) {
        for (int i = 0; i < pixel; ++i) {
            for (int j = 0; j < pixel; ++j) {
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

    void save(const string& filename) const {
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

private:
    vector<vector<Pixel>> image;

    Pixel parsePixel(stringstream& ss) {
        Pixel pixel;
        if (!(ss >> pixel.r)) throw runtime_error("Invalid input format.");
        if (ss.get() != ',') throw runtime_error("Invalid input format.");
        if (!(ss >> pixel.g)) throw runtime_error("Invalid input format.");
        if (ss.get() != ',') throw runtime_error("Invalid input format.");
        if (!(ss >> pixel.b)) throw runtime_error("Invalid input format.");
        if (ss.peek() == ' ') ss.get();
        return pixel;
    }
};

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
        Image image(pixel);
        image.read(inputFileName);
        image.process(favoriteColor);
        image.save(outputFileName);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
