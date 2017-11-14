#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <numeric>
#include <fstream>
#include <random>
#include <sstream>
#ifndef _COLORS_
#define _COLORS_
/* FOREGROUND */
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif  /* _COLORS_ */

int rnd_val(unsigned int a, unsigned int b) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(a, b);

    return dist6(rng);
}
class network {

public: unsigned int size = 0;
    double hamming_distance = 0;
    std::vector <int> neurons;
    std::vector <double> biases;
    std::vector < std::vector <double> > weights;

    void init_random(unsigned int a, bool verbose) {
        size = a;
        std::vector <int> neurons;
        std::vector <double> biases;
        std::vector < std::vector <double> > weights;
        init_random_neurons();
        init_random_biases();
        init_random_weights();
        if (verbose){
            cout_neurons();
            cout_weights();
        }
    }
    void init_input(unsigned int a, std::vector< std::vector <int> > &memory, std::vector<int> &input_binary) {
        size = a;
        std::vector <int> neurons;
        std::vector <double> biases;
        std::vector < std::vector <double> > weights;
        init_neurons(input_binary);
        init_random_biases();
        init_weights(memory);
    }
    void init_weights(std::vector< std::vector <int> > &mem) {
        auto img_size = static_cast<unsigned int> (mem[0].size());
        weights.resize(img_size);
        for (int i = 0; i < img_size; i++) {
            weights[i].resize(img_size);
        }
        for(std::vector<int> &a : mem) {
            std::vector<int> v;
            v.resize(img_size);

            for (int i = 0; i < img_size; i++) {
                v[i] = a[i];
            }
            for (int i = 0; i < img_size; i++) {
                for (int j = 0; j < img_size; j++) {
                    weights[i][j] += v[i] * v[j];
                }
                weights[i][i] = 0;
            }
        }
    }
    void init_neurons(std::vector<int> &a) {
        neurons.resize(a.size());
        for (int i = 0; i < a.size(); i++) {
            neurons[i] = a[i];
        }
    }
    double energy() {
        double energy = 0;
        for(int i = 0; i < weights.size(); i++) {
            for (int j = 0; j < weights.size(); j++) {
                energy += -0.5*weights[i][j]*neurons[i]*neurons[j];
            }
            energy += biases[i]*neurons[i];
        }
        return energy;
    }
    int state() {
        int sum = 0;
        for (int i = 0; i < neurons.size(); i++) {
            if (neurons[i] > 0) {
                sum += std::pow(2, i);
            }
        }
        return sum;
    }
    bool update() {
        int rand_n = rnd_val(0, size-1);
        double t_weight = 0.0;
        for (int i = 0; i < weights[rand_n].size(); i++) {
            t_weight += weights[rand_n][i]*neurons[i];
        }
        if (t_weight > biases[rand_n]) {
            neurons[rand_n] = 1;
            return true;
        }
        neurons[rand_n] = -1;
        return false;
    }
    bool update_neuron(int n) {
        double t_weight = 0.0;
        for (int i = 0; i < weights[n].size(); i++) {
            t_weight += weights[n][i]*neurons[i];
        }
        if (t_weight > biases[n]) {
            neurons[n] = 1;
            return true;
        }
        neurons[n] = -1;
        return false;
    }
    bool converged() {
        for (int n = 0; n < neurons.size(); n++) {
            double t_weight = 0.0;
            for (int i = 0; i < weights[n].size(); i++) {
                t_weight += weights[n][i]*neurons[i];
            }
            if (t_weight > biases[n] && neurons[n] != 1) {
                return false;
            }
            if (t_weight <= biases[n] && neurons[n] != -1) {
                return false;
            }
        }
        return true;
    }
private: void init_random_neurons() {
        neurons.resize(size);
        for (auto &neuron : neurons) {
            neuron = static_cast<int> (std::pow(-1, rnd_val(1,6)));
        }
    }
    void init_random_weights() {
        weights.resize(size);
        for(int i = 0; i < size; i++){
            weights[i].resize(size);
        }
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
                if (i == j) {
                    weights[i][j] = 0.0;
                }
                else {
                    auto rnd_weight = std::pow(-1.0, rnd_val(1,6))*(rnd_val(0, 1000))/1000.0;
                    weights[i][j] = rnd_weight;
                    weights[j][i] = rnd_weight;
                }
            }
        }
    }
    void init_random_biases() {
        biases.resize(size);
        for (auto &bias : biases) {
            bias = std::pow(-1.0, rnd_val(1, 6))*(rnd_val(0, 1000))/1000.0;
        }
    }

public: void cout_neurons() {
        std::cout << std::endl;
        for (auto &item : neurons) {
            std::cout << item << "\t";
        }
        std::cout << "\n";
    }
    void cout_weights() {
        std::cout << "\nWeights:" << std::endl;
        for (auto &weight : weights) {
            for (int j = 0; j < weights.size(); ++j) {
                std::cout << weight[j] << "\t\t";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";
    }
    void cout_state() {
        int sum = 0;
        for (int i = 0; i < neurons.size(); i++) {
            if (neurons[i] > 0) {
                sum += std::pow(2, i);
            }
        }
        std::cout << sum << std::endl;
    }
};
std::vector<int> random_binary (int size) {
    std::vector<int> bin;
    bin.reserve(size);
    for (int i = 0; i < size; i++) {
        bin.push_back(static_cast<int> (std::pow(-1, rnd_val(0, 100))));
    }
    return bin;
}
std::vector<std::vector<int>> convert_strings_to_2d_vector(std::vector<std::string> &a) {
    std::vector<std::vector<int>> bin_vec;
    bin_vec.resize(a.size());
    for (int i  = 0; i < a.size(); i++) {
        for (char &b : a[i]) {
            if (b == '0') {
                bin_vec[i].push_back(-1);
            } else {
                bin_vec[i].push_back(1);
            }
        }
    }
    return bin_vec;
}
std::vector<int> convert_string_to_vector(std::string &a) {
    std::vector<int> c;
    for (char &b : a) {
        if (b == '0') {
            c.push_back(-1*1);
        }
        else {
            c.push_back(1);
        }
    }
    return c;
}
int calculate_hamming_distance (std::vector <int> &target, std::vector <int> &state) {
    int hd = 0;
    for (int i = 0; i < target.size(); i++) {
        if (target[i] != state[i]) {
            hd++;
        }
    }
    return hd;
}
bool in_vector_int (int a, std::vector<int> &b) {
    for (int &c: b) {
        if (a == c){
            return true;
        }
    }
    return false;
}
void txtout_value(std::ofstream &txtout, double val) {
    txtout << val <<'\n';
}
void txtout_neuron_vector(std::ofstream &txtout, std::vector <int> a) {
    for (int &neuron : a) {
        if (neuron == -1) {
            txtout << 0;
        }
        else {
            txtout << 1;
        }
    }
    txtout << std::endl;
}
void txtout_vector(std::ofstream &txtout, std::vector <int> &a) {
    for (int i = 0; i < a.size(); i++) {
        txtout << a[i];
        if (i != a.size()-1) {txtout << ",";}
    }
    txtout << std::endl;
}
void cout_string_vector(std::vector<std::string> &a) {
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size()-1) {std::cout << ",";}
    }
    std::cout << std::endl;
}
void cout_int_vector(std::vector<int> &a) {
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i];
        if (i != a.size()-1) {std::cout << ",";}
    }
    std::cout << std::endl;
}
void cout_neuron_vector(std::vector<int> &a) {
    for (int &neuron : a) {
        if (neuron == -1) {
            std::cout << 0;
        }
        else {
            std::cout << 1;
        }
    }
    std::cout << std::endl;
}
void cout_differences_2_vectors(std::vector<int> a, std::vector<int> b) {
        //std::cout << "a" << a.size() << "b" << "\n";
        std::vector<int> diff_ind;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                diff_ind.push_back(i);
            }
        }
        for (int i = 0; i < a.size(); i++) {
            if (in_vector_int(i, diff_ind)) {
                if (a[i] == -1) {
                    std::cout << FRED("0");
                }
                else {
                    std::cout << FRED("1");
                }
            } else {
                if (a[i] == -1) {
                    std::cout << "0";
                }
                else {
                    std::cout << "1";
                }
            }
        }
        std::cout << "\n";
        for (int i = 0; i < b.size(); i++) {
            if (in_vector_int(i, diff_ind)) {
                if (b[i] == -1) {
                    std::cout << FRED("0");
                }
                else {
                    std::cout << FRED("1");
                }
            } else {
                if (b[i] == -1) {
                    std::cout << "0";
                }
                else {
                    std::cout << "1";
                }
            }
        }
        std::cout << "\n";
    }
void cout_differences_3_vectors(std::vector<int> true_mem, std::vector<int> corr_mem, std::vector<int> result_mem) {
    std::vector<int> diff_ind;
    for (int i = 0; i < true_mem.size(); i++) {
        if (true_mem[i] != result_mem[i] || corr_mem[i] != true_mem[i]) {// || true_mem[i] != result_mem[i] || corr_mem[i] != result_mem[i]) {
            diff_ind.push_back(i);
        }
    }
    for (int i = 0; i < true_mem.size(); i++) {
        if (in_vector_int(i, diff_ind)) {
            if (true_mem[i] != corr_mem[i]) {
                if (true_mem[i] == -1) {
                    std::cout << FGRN("0");
                }
                else {
                    std::cout << FGRN("1");
                }
            }
            else {
                if (true_mem[i] == -1) {
                    std::cout << FRED("0");
                }
                else {
                    std::cout << FRED("1");
                }
            }
        } else {
            if (true_mem[i] == -1) {
                std::cout << "0";
            }
            else {
                std::cout << "1";
            }
        }
    }
    std::cout << "\n";
    for (int i = 0; i < corr_mem.size(); i++) {
        if (in_vector_int(i, diff_ind)) {
            if (true_mem[i] != corr_mem[i]) {
                if (corr_mem[i] == -1) {
                    std::cout << FGRN("0");
                }
                else {
                    std::cout << FGRN("1");
                }
            }
            else {
                if (corr_mem[i] == -1) {
                    std::cout << FRED("0");
                }
                else {
                    std::cout << FRED("1");
                }
            }
        } else {
            if (corr_mem[i] == -1) {
                std::cout << "0";
            }
            else {
                std::cout << "1";
            }
        }
    }
    std::cout << "\n";
    for (int i = 0; i < result_mem.size(); i++) {
        if (in_vector_int(i, diff_ind)) {
            if (result_mem[i] == -1) {
                std::cout << FRED("0");
            }
            else {
                std::cout << FRED("1");
            }
        } else {
            if (result_mem[i] == -1) {
                std::cout << "0";
            }
            else {
                std::cout << "1";
            }
        }
    }
    std::cout << "\n";
}
std::vector < std::vector <int> > gen_memory_vector(std::ifstream &in_stream) {
    std::vector <std::string> memory_str_vec;
    //std::string memory_face_str = "0000000000000100010000000000000000000000000010000000000000000001110000001000100001000001101000000001";
    //memory_str_vec.push_back(memory_face_str);
    //std::string memory_tree_str = "0001111000000111100000001100000000110000001111111000001100100000110000000011000000001100000000110000";
    //memory_str_vec.push_back(memory_tree_str);

    std::string line;
    while (std::getline(in_stream, line)) {
        memory_str_vec.push_back(line);
    }

    auto a = convert_strings_to_2d_vector(memory_str_vec);
    return a;
}
std::vector < std::string > gen_input_vector (std::ifstream &in_stream) {
    std::vector <std::string> memory_str_vec;
    std::string line;
    while (std::getline(in_stream, line)) {
        memory_str_vec.push_back(line);
    }
    return memory_str_vec;
}
std::vector <int> get_config (int a, unsigned int size) {
    std::vector < int > config;
    config.resize(size);
    std::fill(config.begin(), config.end(), 1);
    for(int change = 0; change <= a; ++change) {
        for (int &i : config) {
            if (i == 1) {
                i = -1;
            }
            else {
                i = 1;
                break;
            }
        }
    }
    return config;
}

int main() {
    //std::string line_break = "\n****************************************************************************************\n";
    std::ofstream txtoutput;
    txtoutput.open ("hamming_distances/hamming_distances_fracs_0-80_up1.txt");

//    std::vector <int> groups;
//    groups.reserve(80);
//    for (int i = 0; i < 80; i++) {
//        groups.push_back(i*(i+1)/2);
//    }

    unsigned int size = 100;
    int loop_count = 20;
    std::vector <int> indeces;
    indeces.reserve(size);
    for (int i = 0; i < size; i++) {
        indeces.push_back(i);
    }
    for (unsigned int group_size = 1; group_size < 80; group_size++) {
        std::cout << group_size << "\n";
        for (int corr_frac = 0; corr_frac <= 60; corr_frac = corr_frac + 5) {
            double avg_hd = 0;
            if (corr_frac == 0) {goto label;}
            for (int loop = 0; loop < loop_count; loop++) {

                // create random set of memories S of size group_size
                // train HN on S
                // corrupt pixel of the first memory of S, corr_frac times
                // run until converged
                // add to avg hamming distance
                network net;
                std::vector<std::vector<int> > group_mems;
                group_mems.reserve(group_size);
                for (int i = 0; i < group_size; i++) {
                    group_mems.push_back(random_binary(size));
                }
                std::shuffle(indeces.begin(), indeces.end(), std::mt19937(std::random_device()()));
                auto corr_input = group_mems[0];

                for (int spin = 0; spin < corr_frac; spin++) {
                    corr_input[indeces[spin]] = corr_input[indeces[spin]] * -1;
                }

                net.init_input(size, group_mems, corr_input);

                while (!net.converged()) {
                    net.update();
                }
                net.hamming_distance = calculate_hamming_distance(group_mems[0], net.neurons);
                if (net.hamming_distance > 10.0) {
                    std::cerr << "Large Difference:\t" << net.hamming_distance << std::endl;
                    cout_differences_3_vectors(group_mems[0], corr_input, net.neurons);
                    std::cout << "\n";
                }
                avg_hd += net.hamming_distance/loop_count;

            }
            label:
            //std::cout << line_break << "Number of Images: " << group_size << "\t|\tCorruption fraction: " << corr_frac
            //                        << "\t|\tAverage Hamming Distance: " << avg_hd << line_break << "\n";
            txtout_value(txtoutput, avg_hd);
        }
    }
    txtoutput.close();
    return 0;
}
